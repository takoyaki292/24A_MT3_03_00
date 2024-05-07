#include <Novice.h>
#include "Vector3.h"
#define _USE_MATH_DEFINES
#include<math.h>
#include <stdio.h>
#include<assert.h>
const char kWindowTitle[] = "GC2B_08_シミズ_タクミ";

struct Matrix4x4
{
	float m[4][4];
};


//平行移動行列
Matrix4x4 MakeTranslateMatrix(const Vector3& transform)
{
	Matrix4x4 m = {};


	m.m[0][0] = 1;
	m.m[0][1] = 0;
	m.m[0][2] = 0;
	m.m[0][3] = 0;

	m.m[1][0] = 0;
	m.m[1][1] = 1;
	m.m[1][2] = 0;
	m.m[1][3] = 0;

	m.m[2][0] = 0;
	m.m[2][1] = 0;
	m.m[2][2] = 1;
	m.m[2][3] = 0;

	m.m[3][0] = transform.x;
	m.m[3][1] = transform.y;
	m.m[3][2] = transform.z;
	m.m[3][3] = 1;

	return m;
}
//拡大縮小行列
Matrix4x4 MakeScaleMatrix(const Vector3& scale)
{
	Matrix4x4 m = {};

	m.m[0][0] = scale.x;
	m.m[0][1] = 0;
	m.m[0][2] = 0;
	m.m[0][3] = 0;

	m.m[1][0] = 0;
	m.m[1][1] = scale.y;
	m.m[1][2] = 0;
	m.m[1][3] = 0;

	m.m[2][0] = 0;
	m.m[2][1] = 0;
	m.m[2][2] = scale.z;
	m.m[2][3] = 0;

	m.m[3][0] = 0;
	m.m[3][1] = 0;
	m.m[3][2] = 0;
	m.m[3][3] = 1;


	return m;
}

//座標変換
Vector3 Transform(Vector3 transform, Matrix4x4 matrix)
{
	Vector3 m = {};

	m.x = transform.x * matrix.m[0][0] + transform.y * matrix.m[1][0] + transform.z * matrix.m[2][0] + 1.0f * matrix.m[3][0];
	m.y = transform.x * matrix.m[0][1] + transform.y * matrix.m[1][1] + transform.z * matrix.m[2][1] + 1.0f * matrix.m[3][1];
	m.z = transform.x * matrix.m[0][2] + transform.y * matrix.m[1][2] + transform.z * matrix.m[2][2] + 1.0f * matrix.m[3][2];

	float w = transform.x * matrix.m[0][3] + transform.y * matrix.m[1][3] +transform.z*matrix.m[2][3]+1.0f * matrix.m[3][3];
	assert(w != 0.0f);
	m.x /= w;
	m.y /= w;
	m.z /= w;

	return m;
}

//printfの関数
static const int kRowHeight = 20;
static const int kColmnWidht = 100;
void MatrixScreenPrintf(int x, int y, Matrix4x4 matrix)
{
	for (int row = 0; row < 4; ++row)
	{
		for (int column = 0; column < 4; ++column)
		{
			Novice::ScreenPrintf(x + column * kColmnWidht, y + row * kRowHeight, "%.02f", matrix.m[row][column]);
		}
	}
	printf("\n");
}
void VectorScreenPrintf(int x, int y, Vector3 vector)
{
	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kColmnWidht, y, "%.02f", vector.y);
	Novice::ScreenPrintf(x + kColmnWidht*2, y, "%.02f", vector.z);

}
// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	Vector3 translate = { 4.1f,2.6f,0.8f };
	Vector3 scale = { 1.5f,5.2f,7.3f };
	Vector3 point = { 2.3f,3.8f,1.4f };
	Matrix4x4 transformMatrix =
	{
		1.0f,2.0f,3.0f,4.0f,
		3.0f,1.0f,1.0f,2.0f,
		1.0f,4.0f,2.0f,3.0f,
		2.0f,2.0f,1.0f,3.0f,
	};
	
	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		Matrix4x4 translateMatrix = MakeTranslateMatrix(translate);
		Matrix4x4 scaleMatrix = MakeScaleMatrix(scale);
		Vector3 transformed = Transform(point, transformMatrix);
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		VectorScreenPrintf(0, 0, transformed);
		MatrixScreenPrintf(0, kRowHeight * 2, translateMatrix);
		MatrixScreenPrintf(0, kRowHeight * 7, scaleMatrix);
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}

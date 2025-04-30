//#include<stdio.h>
//#include<string.h>
//#define MAXSIZE 30//串的最大长度
//typedef struct Chunk
//{
//	struct Chunk* next;
//	char data[MAXSIZE];
//}chunk;
//typedef struct
//{
//	chunk* head, * tail;//当前串的头指针和尾指针
//	int length;//串的实际长度
//}Lstring;
////Brute-force算法查找子串在主串中的位置
//void search(char* sq1, char* sq2)
//{
//	int i, j,t1,t2,count=0;
//	t1 = strlen(sq1);
//	t2 = strlen(sq2);//求串的长度
//	/*for (i = 0; i < t1 - t2 ; i++)
//	{
//		for (j = 0; j < t2; j++)
//		{
//			if (sq2[j] == sq1[i + j])
//			{
//				;
//			}
//			else
//				break;
//		}
//		if (j == t2)
//			printf("子串在主串中的位置为：%d", i);
//	}*/
//	i = 0; j = 0;
//	while (i < t1 - t2 && j < t2)
//	{
//		if (sq2[j] == sq1[i])
//		{
//			i++; j++;
//		}
//		else
//		{
//			i = i - j + 1; j = 0;
//			//若不相同则重置子串位置，从0开始，主串从下一元素开始查找
//		}
//		if (j == t2)
//			printf("子串在主串中的位置为：%d", i-t2);
//	}
//}
//int next(char* T)
//{
//	int i, j;
//
//}
//int main()
//{
//	char s[6] = { "sdert" };
//	char t[3] = { "de" };
//	search(s, t);
//}

#include <stdio.h>
#include <stdlib.h>

// 定义三元组结构体
typedef struct {
    int row; // 行索引
    int col; // 列索引
    int value; // 元素值
} Triplet;

// 函数声明
Triplet* transposeMatrix(Triplet* matrix, int matrixSize, int rows, int cols);
//int findMaxColIndex(Triplet* matrix, int size);

int main() {
    int rows = 5, cols = 4; // 矩阵的行数和列数
    int matrixSize = 8; // 原矩阵中的非零元素个数

    // 原始矩阵的三元组表示
    Triplet matrix[8] = {
        {0, 2, 5},
        {1, 1, 7},
        {1, 3, 9},
        {2, 0, 3},
        {2, 2, 2},
        {3, 1, 4},
        {3, 3, 6},
        {4, 0, 1}
    };

    // 转置矩阵
    int transposedRows = cols; // 转置后矩阵的行数
    int transposedCols = rows; // 转置后矩阵的列数
    Triplet* transposedMatrix = transposeMatrix(matrix, matrixSize, rows, cols);

    // 打印转置矩阵
    for (int i = 0; i < matrixSize; i++) {
        printf("Row: %d, Col: %d, Value: %d\n", transposedMatrix[i].row, transposedMatrix[i].col, transposedMatrix[i].value);
    }

    free(transposedMatrix); // 释放内存
    return 0;
}

// 转置矩阵
Triplet* transposeMatrix(Triplet* matrix, int matrixSize, int rows, int cols) {
    // 使用行数和列数来分配内存，而不是最大列索引
    Triplet* transposed = (Triplet*)malloc(cols * sizeof(Triplet));
    int* count = (int*)calloc(cols, sizeof(int)); // 用于记录每列的非零元素数量

    // 初始化转置矩阵
    for (int i = 0; i < cols; i++) {
        transposed[i].row = -1;
        transposed[i].col = i;
        transposed[i].value = 0;
        count[i] = 0;
    }

    // 构建转置矩阵
    for (int i = 0; i < matrixSize; i++) {
        int newRow = matrix[i].col;
        int newCol = matrix[i].row;
        count[newCol]++;
    }

    // 计算每个非零元素在转置矩阵中的位置
    int pos = 0;
    for (int i = 0; i < cols; i++) {
        transposed[i].row = pos;
        pos += count[i];
    }

    // 填充转置矩阵的值
    for (int i = matrixSize - 1; i >= 0; i--) {
        int newRow = matrix[i].col;
        int newCol = matrix[i].row;
        pos = transposed[newCol].row + count[newCol] - 1;
        transposed[pos].row = newRow;
        transposed[pos].col = newCol;
        transposed[pos].value = matrix[i].value;
        count[newCol]--;
    }

    free(count);
    return transposed;
}
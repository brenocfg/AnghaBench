#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ov7670_info {TYPE_1__* fmt; } ;
struct TYPE_2__ {int* cmatrix; } ;

/* Variables and functions */
 int CMATRIX_LEN ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int ov7670_cosine (int) ; 
 int ov7670_sine (int) ; 

__attribute__((used)) static void ov7670_calc_cmatrix(struct ov7670_info *info,
		int matrix[CMATRIX_LEN], int sat, int hue)
{
	int i;
	/*
	 * Apply the current saturation setting first.
	 */
	for (i = 0; i < CMATRIX_LEN; i++)
		matrix[i] = (info->fmt->cmatrix[i] * sat) >> 7;
	/*
	 * Then, if need be, rotate the hue value.
	 */
	if (hue != 0) {
		int sinth, costh, tmpmatrix[CMATRIX_LEN];

		memcpy(tmpmatrix, matrix, CMATRIX_LEN*sizeof(int));
		sinth = ov7670_sine(hue);
		costh = ov7670_cosine(hue);

		matrix[0] = (matrix[3]*sinth + matrix[0]*costh)/1000;
		matrix[1] = (matrix[4]*sinth + matrix[1]*costh)/1000;
		matrix[2] = (matrix[5]*sinth + matrix[2]*costh)/1000;
		matrix[3] = (matrix[3]*costh - matrix[0]*sinth)/1000;
		matrix[4] = (matrix[4]*costh - matrix[1]*sinth)/1000;
		matrix[5] = (matrix[5]*costh - matrix[2]*sinth)/1000;
	}
}
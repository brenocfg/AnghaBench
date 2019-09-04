#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */

__attribute__((used)) static void rgb2ycbcr(const int m[3][3], int r, int g, int b,
			int y_offset, int *y, int *cb, int *cr)
{
	*y  = ((m[0][0] * r + m[0][1] * g + m[0][2] * b) >> 16) + (y_offset << 4);
	*cb = ((m[1][0] * r + m[1][1] * g + m[1][2] * b) >> 16) + (128 << 4);
	*cr = ((m[2][0] * r + m[2][1] * g + m[2][2] * b) >> 16) + (128 << 4);
}
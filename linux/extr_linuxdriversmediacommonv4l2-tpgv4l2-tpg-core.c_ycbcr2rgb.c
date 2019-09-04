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
 int clamp (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ycbcr2rgb(const int m[3][3], int y, int cb, int cr,
			int y_offset, int *r, int *g, int *b)
{
	y -= y_offset << 4;
	cb -= 128 << 4;
	cr -= 128 << 4;
	*r = m[0][0] * y + m[0][1] * cb + m[0][2] * cr;
	*g = m[1][0] * y + m[1][1] * cb + m[1][2] * cr;
	*b = m[2][0] * y + m[2][1] * cb + m[2][2] * cr;
	*r = clamp(*r >> 12, 0, 0xff0);
	*g = clamp(*g >> 12, 0, 0xff0);
	*b = clamp(*b >> 12, 0, 0xff0);
}
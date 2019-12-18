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
typedef  scalar_t__ s32 ;

/* Variables and functions */

__attribute__((used)) static s32 carl9170_interpolate_s32(s32 x, s32 x1, s32 y1, s32 x2, s32 y2)
{
	/* nothing to interpolate, it's horizontal */
	if (y2 == y1)
		return y1;

	/* check if we hit one of the edges */
	if (x == x1)
		return y1;
	if (x == x2)
		return y2;

	/* x1 == x2 is bad, hopefully == x */
	if (x2 == x1)
		return y1;

	return y1 + (((y2 - y1) * (x - x1)) / (x2 - x1));
}
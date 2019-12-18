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
typedef  scalar_t__ s16 ;

/* Variables and functions */

__attribute__((used)) static s16
ath5k_get_interpolated_value(s16 target, s16 x_left, s16 x_right,
					s16 y_left, s16 y_right)
{
	s16 ratio, result;

	/* Avoid divide by zero and skip interpolation
	 * if we have the same point */
	if ((x_left == x_right) || (y_left == y_right))
		return y_left;

	/*
	 * Since we use ints and not fps, we need to scale up in
	 * order to get a sane ratio value (or else we 'll eg. get
	 * always 1 instead of 1.25, 1.75 etc). We scale up by 100
	 * to have some accuracy both for 0.5 and 0.25 steps.
	 */
	ratio = ((100 * y_right - 100 * y_left) / (x_right - x_left));

	/* Now scale down to be in range */
	result = y_left + (ratio * (target - x_left) / 100);

	return result;
}
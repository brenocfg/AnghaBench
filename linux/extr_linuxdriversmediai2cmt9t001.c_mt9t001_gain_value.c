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
typedef  int u16 ;
typedef  int s32 ;

/* Variables and functions */

__attribute__((used)) static u16 mt9t001_gain_value(s32 *gain)
{
	/* Gain is controlled by 2 analog stages and a digital stage. Valid
	 * values for the 3 stages are
	 *
	 * Stage		Min	Max	Step
	 * ------------------------------------------
	 * First analog stage	x1	x2	1
	 * Second analog stage	x1	x4	0.125
	 * Digital stage	x1	x16	0.125
	 *
	 * To minimize noise, the gain stages should be used in the second
	 * analog stage, first analog stage, digital stage order. Gain from a
	 * previous stage should be pushed to its maximum value before the next
	 * stage is used.
	 */
	if (*gain <= 32)
		return *gain;

	if (*gain <= 64) {
		*gain &= ~1;
		return (1 << 6) | (*gain >> 1);
	}

	*gain &= ~7;
	return ((*gain - 64) << 5) | (1 << 6) | 32;
}
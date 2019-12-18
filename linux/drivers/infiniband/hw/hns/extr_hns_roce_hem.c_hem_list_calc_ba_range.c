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
typedef  int u32 ;

/* Variables and functions */

__attribute__((used)) static u32 hem_list_calc_ba_range(int hopnum, int bt_level, int unit)
{
	u32 step;
	int max;
	int i;

	if (hopnum <= bt_level)
		return 0;
	/*
	 * hopnum  bt_level   range
	 * 1	      0       unit
	 * ------------
	 * 2	      0       unit * unit
	 * 2	      1       unit
	 * ------------
	 * 3	      0       unit * unit * unit
	 * 3	      1       unit * unit
	 * 3	      2       unit
	 */
	step = 1;
	max = hopnum - bt_level;
	for (i = 0; i < max; i++)
		step = step * unit;

	return step;
}
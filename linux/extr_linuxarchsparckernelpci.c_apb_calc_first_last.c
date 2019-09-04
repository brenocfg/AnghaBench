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
typedef  int u8 ;
typedef  int u32 ;

/* Variables and functions */

__attribute__((used)) static void apb_calc_first_last(u8 map, u32 *first_p, u32 *last_p)
{
	u32 idx, first, last;

	first = 8;
	last = 0;
	for (idx = 0; idx < 8; idx++) {
		if ((map & (1 << idx)) != 0) {
			if (first > idx)
				first = idx;
			if (last < idx)
				last = idx;
		}
	}

	*first_p = first;
	*last_p = last;
}
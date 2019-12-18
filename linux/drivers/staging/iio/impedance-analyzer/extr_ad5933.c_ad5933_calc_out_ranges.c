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
struct ad5933_state {unsigned int* range_avail; unsigned int vref_mv; } ;

/* Variables and functions */

__attribute__((used)) static void ad5933_calc_out_ranges(struct ad5933_state *st)
{
	int i;
	unsigned int normalized_3v3[4] = {1980, 198, 383, 970};

	for (i = 0; i < 4; i++)
		st->range_avail[i] = normalized_3v3[i] * st->vref_mv / 3300;
}
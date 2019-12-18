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
struct dm_pp_clock_levels_with_voltage {int num_levels; TYPE_1__* data; } ;
struct TYPE_2__ {scalar_t__ clocks_in_khz; } ;

/* Variables and functions */

__attribute__((used)) static bool verify_clock_values(struct dm_pp_clock_levels_with_voltage *clks)
{
	int i;

	if (clks->num_levels == 0)
		return false;

	for (i = 0; i < clks->num_levels; i++)
		/* Ensure that the result is sane */
		if (clks->data[i].clocks_in_khz == 0)
			return false;

	return true;
}
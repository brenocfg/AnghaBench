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
typedef  unsigned int uint32_t ;
struct pp_atomctrl_voltage_table {unsigned int count; int /*<<< orphan*/ * entries; } ;

/* Variables and functions */

void phm_trim_voltage_table_to_fit_state_table(uint32_t max_vol_steps,
				struct pp_atomctrl_voltage_table *vol_table)
{
	unsigned int i, diff;

	if (vol_table->count <= max_vol_steps)
		return;

	diff = vol_table->count - max_vol_steps;

	for (i = 0; i < max_vol_steps; i++)
		vol_table->entries[i] = vol_table->entries[i + diff];

	vol_table->count = max_vol_steps;

	return;
}
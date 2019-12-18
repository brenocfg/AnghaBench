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
typedef  size_t uint32_t ;
struct vega10_single_dpm_table {size_t count; TYPE_1__* dpm_levels; } ;
struct pp_hwmgr {int dummy; } ;
struct TYPE_2__ {size_t value; int enabled; } ;

/* Variables and functions */

__attribute__((used)) static int vega10_trim_single_dpm_states_with_mask(struct pp_hwmgr *hwmgr,
		struct vega10_single_dpm_table *dpm_table,
		uint32_t low_limit, uint32_t high_limit,
		uint32_t disable_dpm_mask)
{
	uint32_t i;

	for (i = 0; i < dpm_table->count; i++) {
		if ((dpm_table->dpm_levels[i].value < low_limit) ||
		    (dpm_table->dpm_levels[i].value > high_limit))
			dpm_table->dpm_levels[i].enabled = false;
		else if (!((1 << i) & disable_dpm_mask))
			dpm_table->dpm_levels[i].enabled = false;
		else
			dpm_table->dpm_levels[i].enabled = true;
	}
	return 0;
}
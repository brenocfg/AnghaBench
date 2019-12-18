#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct vega10_single_dpm_table {size_t count; TYPE_3__* dpm_levels; } ;
struct vega10_power_state {int performance_level_count; TYPE_2__* performance_levels; } ;
struct TYPE_9__ {scalar_t__ num_existing_displays; } ;
struct TYPE_6__ {struct vega10_single_dpm_table mem_table; struct vega10_single_dpm_table gfx_table; } ;
struct vega10_hwmgr {int /*<<< orphan*/  need_update_dpm_table; TYPE_4__ display_timing; TYPE_1__ dpm_table; } ;
struct pp_hwmgr {TYPE_5__* display_config; struct vega10_hwmgr* backend; } ;
struct phm_set_power_state_input {int /*<<< orphan*/  pnew_state; } ;
struct TYPE_10__ {scalar_t__ num_display; } ;
struct TYPE_8__ {size_t value; } ;
struct TYPE_7__ {size_t gfx_clock; size_t mem_clock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPMTABLE_OD_UPDATE_MCLK ; 
 int /*<<< orphan*/  DPMTABLE_OD_UPDATE_SCLK ; 
 int /*<<< orphan*/  DPMTABLE_UPDATE_MCLK ; 
 struct vega10_power_state* cast_const_phw_vega10_power_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vega10_find_dpm_states_clocks_in_dpm_table(struct pp_hwmgr *hwmgr, const void *input)
{
	struct vega10_hwmgr *data = hwmgr->backend;
	const struct phm_set_power_state_input *states =
			(const struct phm_set_power_state_input *)input;
	const struct vega10_power_state *vega10_ps =
			cast_const_phw_vega10_power_state(states->pnew_state);
	struct vega10_single_dpm_table *sclk_table = &(data->dpm_table.gfx_table);
	uint32_t sclk = vega10_ps->performance_levels
			[vega10_ps->performance_level_count - 1].gfx_clock;
	struct vega10_single_dpm_table *mclk_table = &(data->dpm_table.mem_table);
	uint32_t mclk = vega10_ps->performance_levels
			[vega10_ps->performance_level_count - 1].mem_clock;
	uint32_t i;

	for (i = 0; i < sclk_table->count; i++) {
		if (sclk == sclk_table->dpm_levels[i].value)
			break;
	}

	if (i >= sclk_table->count) {
		if (sclk > sclk_table->dpm_levels[i-1].value) {
			data->need_update_dpm_table |= DPMTABLE_OD_UPDATE_SCLK;
			sclk_table->dpm_levels[i-1].value = sclk;
		}
	}

	for (i = 0; i < mclk_table->count; i++) {
		if (mclk == mclk_table->dpm_levels[i].value)
			break;
	}

	if (i >= mclk_table->count) {
		if (mclk > mclk_table->dpm_levels[i-1].value) {
			data->need_update_dpm_table |= DPMTABLE_OD_UPDATE_MCLK;
			mclk_table->dpm_levels[i-1].value = mclk;
		}
	}

	if (data->display_timing.num_existing_displays != hwmgr->display_config->num_display)
		data->need_update_dpm_table |= DPMTABLE_UPDATE_MCLK;

	return 0;
}
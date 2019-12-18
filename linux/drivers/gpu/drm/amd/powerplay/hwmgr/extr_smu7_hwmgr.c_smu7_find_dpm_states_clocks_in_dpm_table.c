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
struct smu7_single_dpm_table {size_t count; TYPE_3__* dpm_levels; } ;
struct smu7_power_state {int performance_level_count; TYPE_2__* performance_levels; } ;
struct TYPE_9__ {scalar_t__ min_clock_in_sr; scalar_t__ num_existing_displays; } ;
struct TYPE_6__ {struct smu7_single_dpm_table mclk_table; struct smu7_single_dpm_table sclk_table; } ;
struct smu7_hwmgr {int /*<<< orphan*/  need_update_smu7_dpm_table; TYPE_4__ display_timing; TYPE_1__ dpm_table; } ;
struct pp_hwmgr {TYPE_5__* display_config; scalar_t__ backend; } ;
struct phm_set_power_state_input {int /*<<< orphan*/  pnew_state; } ;
struct PP_Clocks {scalar_t__ engineClockInSR; int /*<<< orphan*/  member_0; } ;
struct TYPE_10__ {scalar_t__ num_display; } ;
struct TYPE_8__ {size_t value; } ;
struct TYPE_7__ {size_t engine_clock; size_t memory_clock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPMTABLE_OD_UPDATE_MCLK ; 
 int /*<<< orphan*/  DPMTABLE_OD_UPDATE_SCLK ; 
 int /*<<< orphan*/  DPMTABLE_UPDATE_MCLK ; 
 int /*<<< orphan*/  DPMTABLE_UPDATE_SCLK ; 
 scalar_t__ SMU7_MINIMUM_ENGINE_CLOCK ; 
 struct smu7_power_state* cast_const_phw_smu7_power_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smu7_find_dpm_states_clocks_in_dpm_table(struct pp_hwmgr *hwmgr, const void *input)
{
	const struct phm_set_power_state_input *states =
			(const struct phm_set_power_state_input *)input;
	const struct smu7_power_state *smu7_ps =
			cast_const_phw_smu7_power_state(states->pnew_state);
	struct smu7_hwmgr *data = (struct smu7_hwmgr *)(hwmgr->backend);
	struct smu7_single_dpm_table *sclk_table = &(data->dpm_table.sclk_table);
	uint32_t sclk = smu7_ps->performance_levels
			[smu7_ps->performance_level_count - 1].engine_clock;
	struct smu7_single_dpm_table *mclk_table = &(data->dpm_table.mclk_table);
	uint32_t mclk = smu7_ps->performance_levels
			[smu7_ps->performance_level_count - 1].memory_clock;
	struct PP_Clocks min_clocks = {0};
	uint32_t i;

	for (i = 0; i < sclk_table->count; i++) {
		if (sclk == sclk_table->dpm_levels[i].value)
			break;
	}

	if (i >= sclk_table->count) {
		if (sclk > sclk_table->dpm_levels[i-1].value) {
			data->need_update_smu7_dpm_table |= DPMTABLE_OD_UPDATE_SCLK;
			sclk_table->dpm_levels[i-1].value = sclk;
		}
	} else {
	/* TODO: Check SCLK in DAL's minimum clocks
	 * in case DeepSleep divider update is required.
	 */
		if (data->display_timing.min_clock_in_sr != min_clocks.engineClockInSR &&
			(min_clocks.engineClockInSR >= SMU7_MINIMUM_ENGINE_CLOCK ||
				data->display_timing.min_clock_in_sr >= SMU7_MINIMUM_ENGINE_CLOCK))
			data->need_update_smu7_dpm_table |= DPMTABLE_UPDATE_SCLK;
	}

	for (i = 0; i < mclk_table->count; i++) {
		if (mclk == mclk_table->dpm_levels[i].value)
			break;
	}

	if (i >= mclk_table->count) {
		if (mclk > mclk_table->dpm_levels[i-1].value) {
			data->need_update_smu7_dpm_table |= DPMTABLE_OD_UPDATE_MCLK;
			mclk_table->dpm_levels[i-1].value = mclk;
		}
	}

	if (data->display_timing.num_existing_displays != hwmgr->display_config->num_display)
		data->need_update_smu7_dpm_table |= DPMTABLE_UPDATE_MCLK;

	return 0;
}
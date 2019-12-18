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
struct vega10_single_dpm_table {size_t count; TYPE_2__* dpm_levels; } ;
struct TYPE_8__ {size_t soft_min_level; } ;
struct TYPE_9__ {TYPE_3__ dpm_state; } ;
struct TYPE_10__ {TYPE_4__ mem_table; struct vega10_single_dpm_table dcef_table; } ;
struct vega10_hwmgr {TYPE_5__ dpm_table; } ;
struct pp_hwmgr {TYPE_1__* display_config; scalar_t__ pptable; struct vega10_hwmgr* backend; } ;
struct pp_display_clock_request {int clock_freq_in_khz; int /*<<< orphan*/  clock_type; } ;
struct phm_ppt_v2_information {struct phm_ppt_v1_clock_voltage_dependency_table* vdd_dep_on_mclk; } ;
struct phm_ppt_v1_clock_voltage_dependency_table {int dummy; } ;
struct PP_Clocks {int dcefClock; int dcefClockInSR; scalar_t__ memoryClock; int /*<<< orphan*/  member_0; } ;
struct TYPE_7__ {int value; } ;
struct TYPE_6__ {int num_display; int min_dcef_set_clk; int min_dcef_deep_sleep_set_clk; scalar_t__ min_mem_set_clock; int /*<<< orphan*/  nb_pstate_switch_disable; int /*<<< orphan*/  multi_monitor_in_sync; } ;

/* Variables and functions */
 int /*<<< orphan*/  PPSMC_MSG_SetMinDeepSleepDcefclk ; 
 int /*<<< orphan*/  PPSMC_MSG_SetSoftMinUclkByIndex ; 
 int /*<<< orphan*/  amd_pp_dcef_clock ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  smum_send_msg_to_smc_with_parameter (struct pp_hwmgr*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  vega10_display_clock_voltage_request (struct pp_hwmgr*,struct pp_display_clock_request*) ; 
 size_t vega10_get_uclk_index (struct pp_hwmgr*,struct phm_ppt_v1_clock_voltage_dependency_table*,scalar_t__) ; 
 int /*<<< orphan*/  vega10_notify_smc_display_change (struct pp_hwmgr*,int) ; 

__attribute__((used)) static int vega10_notify_smc_display_config_after_ps_adjustment(
		struct pp_hwmgr *hwmgr)
{
	struct vega10_hwmgr *data = hwmgr->backend;
	struct vega10_single_dpm_table *dpm_table =
			&data->dpm_table.dcef_table;
	struct phm_ppt_v2_information *table_info =
			(struct phm_ppt_v2_information *)hwmgr->pptable;
	struct phm_ppt_v1_clock_voltage_dependency_table *mclk_table = table_info->vdd_dep_on_mclk;
	uint32_t idx;
	struct PP_Clocks min_clocks = {0};
	uint32_t i;
	struct pp_display_clock_request clock_req;

	if ((hwmgr->display_config->num_display > 1) &&
	     !hwmgr->display_config->multi_monitor_in_sync &&
	     !hwmgr->display_config->nb_pstate_switch_disable)
		vega10_notify_smc_display_change(hwmgr, false);
	else
		vega10_notify_smc_display_change(hwmgr, true);

	min_clocks.dcefClock = hwmgr->display_config->min_dcef_set_clk;
	min_clocks.dcefClockInSR = hwmgr->display_config->min_dcef_deep_sleep_set_clk;
	min_clocks.memoryClock = hwmgr->display_config->min_mem_set_clock;

	for (i = 0; i < dpm_table->count; i++) {
		if (dpm_table->dpm_levels[i].value == min_clocks.dcefClock)
			break;
	}

	if (i < dpm_table->count) {
		clock_req.clock_type = amd_pp_dcef_clock;
		clock_req.clock_freq_in_khz = dpm_table->dpm_levels[i].value * 10;
		if (!vega10_display_clock_voltage_request(hwmgr, &clock_req)) {
			smum_send_msg_to_smc_with_parameter(
					hwmgr, PPSMC_MSG_SetMinDeepSleepDcefclk,
					min_clocks.dcefClockInSR / 100);
		} else {
			pr_info("Attempt to set Hard Min for DCEFCLK Failed!");
		}
	} else {
		pr_debug("Cannot find requested DCEFCLK!");
	}

	if (min_clocks.memoryClock != 0) {
		idx = vega10_get_uclk_index(hwmgr, mclk_table, min_clocks.memoryClock);
		smum_send_msg_to_smc_with_parameter(hwmgr, PPSMC_MSG_SetSoftMinUclkByIndex, idx);
		data->dpm_table.mem_table.dpm_state.soft_min_level= idx;
	}

	return 0;
}
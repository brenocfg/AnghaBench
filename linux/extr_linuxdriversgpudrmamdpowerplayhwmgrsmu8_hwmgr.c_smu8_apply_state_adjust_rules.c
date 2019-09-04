#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct smu8_power_state {int need_dfs_bypass; scalar_t__ action; } ;
struct TYPE_11__ {scalar_t__* nbp_memory_clock; } ;
struct smu8_hwmgr {int battery_state; TYPE_5__ sys_info; } ;
struct TYPE_7__ {scalar_t__ ui_label; } ;
struct pp_power_state {TYPE_1__ classification; int /*<<< orphan*/  hardware; } ;
struct TYPE_9__ {scalar_t__ mclk; } ;
struct TYPE_10__ {TYPE_3__ max_clock_voltage_on_ac; } ;
struct TYPE_8__ {int /*<<< orphan*/  platformCaps; } ;
struct pp_hwmgr {scalar_t__ request_dpm_level; TYPE_6__* display_config; TYPE_4__ dyn_state; TYPE_2__ platform_descriptor; struct smu8_hwmgr* backend; } ;
struct PP_Clocks {scalar_t__ memoryClock; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_12__ {scalar_t__ min_mem_set_clock; int num_display; } ;

/* Variables and functions */
 scalar_t__ AMD_DPM_FORCED_LEVEL_PROFILE_PEAK ; 
 scalar_t__ AMD_DPM_FORCED_LEVEL_PROFILE_STANDARD ; 
 scalar_t__ CANCEL_FORCE_HIGH ; 
 scalar_t__ DO_NOTHING ; 
 scalar_t__ FORCE_HIGH ; 
 int /*<<< orphan*/  PHM_PlatformCaps_StablePState ; 
 scalar_t__ PP_StateUILabel_Battery ; 
 int SMU8_NUM_NBPMEMORYCLOCK ; 
 struct smu8_power_state* cast_const_smu8_power_state (int /*<<< orphan*/ *) ; 
 struct smu8_power_state* cast_smu8_power_state (int /*<<< orphan*/ *) ; 
 scalar_t__ phm_cap_enabled (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smu8_nbdpm_pstate_enable_disable (struct pp_hwmgr*,int,int) ; 

__attribute__((used)) static int smu8_apply_state_adjust_rules(struct pp_hwmgr *hwmgr,
				struct pp_power_state  *prequest_ps,
			const struct pp_power_state *pcurrent_ps)
{
	struct smu8_power_state *smu8_ps =
				cast_smu8_power_state(&prequest_ps->hardware);

	const struct smu8_power_state *smu8_current_ps =
				cast_const_smu8_power_state(&pcurrent_ps->hardware);

	struct smu8_hwmgr *data = hwmgr->backend;
	struct PP_Clocks clocks = {0, 0, 0, 0};
	bool force_high;

	smu8_ps->need_dfs_bypass = true;

	data->battery_state = (PP_StateUILabel_Battery == prequest_ps->classification.ui_label);

	clocks.memoryClock = hwmgr->display_config->min_mem_set_clock != 0 ?
				hwmgr->display_config->min_mem_set_clock :
				data->sys_info.nbp_memory_clock[1];


	if (phm_cap_enabled(hwmgr->platform_descriptor.platformCaps, PHM_PlatformCaps_StablePState))
		clocks.memoryClock = hwmgr->dyn_state.max_clock_voltage_on_ac.mclk;

	force_high = (clocks.memoryClock > data->sys_info.nbp_memory_clock[SMU8_NUM_NBPMEMORYCLOCK - 1])
			|| (hwmgr->display_config->num_display >= 3);

	smu8_ps->action = smu8_current_ps->action;

	if (hwmgr->request_dpm_level == AMD_DPM_FORCED_LEVEL_PROFILE_PEAK)
		smu8_nbdpm_pstate_enable_disable(hwmgr, false, false);
	else if (hwmgr->request_dpm_level == AMD_DPM_FORCED_LEVEL_PROFILE_STANDARD)
		smu8_nbdpm_pstate_enable_disable(hwmgr, false, true);
	else if (!force_high && (smu8_ps->action == FORCE_HIGH))
		smu8_ps->action = CANCEL_FORCE_HIGH;
	else if (force_high && (smu8_ps->action != FORCE_HIGH))
		smu8_ps->action = FORCE_HIGH;
	else
		smu8_ps->action = DO_NOTHING;

	return 0;
}
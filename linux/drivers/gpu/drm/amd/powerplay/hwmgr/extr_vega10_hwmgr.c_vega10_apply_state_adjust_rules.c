#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct vega10_power_state {int performance_level_count; TYPE_5__* performance_levels; } ;
struct TYPE_13__ {size_t count; TYPE_1__* entries; } ;
struct TYPE_18__ {size_t stable_pstate_sclk_dpm_percentage; } ;
struct vega10_hwmgr {int battery_state; TYPE_2__ mclk_latency_table; TYPE_7__ registry_data; } ;
struct TYPE_14__ {scalar_t__ ui_label; } ;
struct pp_power_state {TYPE_3__ classification; int /*<<< orphan*/  hardware; } ;
struct phm_clock_and_voltage_limits {scalar_t__ mclk; size_t sclk; } ;
struct TYPE_19__ {struct phm_clock_and_voltage_limits max_clock_voltage_on_ac; struct phm_clock_and_voltage_limits max_clock_voltage_on_dc; } ;
struct pp_hwmgr {TYPE_6__* display_config; TYPE_8__ dyn_state; scalar_t__ pptable; struct vega10_hwmgr* backend; struct amdgpu_device* adev; } ;
struct phm_ppt_v2_information {TYPE_9__* vdd_dep_on_sclk; } ;
struct TYPE_15__ {scalar_t__ ac_power; } ;
struct amdgpu_device {TYPE_4__ pm; } ;
struct PP_Clocks {size_t engineClock; size_t memoryClock; int /*<<< orphan*/  member_0; } ;
typedef  size_t int32_t ;
struct TYPE_20__ {size_t count; TYPE_10__* entries; } ;
struct TYPE_17__ {size_t min_core_set_clock; size_t min_mem_set_clock; int num_display; size_t dce_tolerable_mclk_in_active_latency; int /*<<< orphan*/  multi_monitor_in_sync; } ;
struct TYPE_16__ {scalar_t__ mem_clock; size_t gfx_clock; } ;
struct TYPE_12__ {size_t latency; scalar_t__ frequency; } ;
struct TYPE_11__ {size_t clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHM_PlatformCaps_DisableMclkSwitchForVR ; 
 int /*<<< orphan*/  PHM_PlatformCaps_DisableMclkSwitchingForFrameLock ; 
 int /*<<< orphan*/  PHM_PlatformCaps_ForceMclkHigh ; 
 int /*<<< orphan*/  PHM_PlatformCaps_StablePState ; 
 int /*<<< orphan*/  PP_ASSERT_WITH_CODE (int,char*,size_t) ; 
 int PP_CAP (int /*<<< orphan*/ ) ; 
 scalar_t__ PP_StateUILabel_Battery ; 
 struct vega10_power_state* cast_phw_vega10_power_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*) ; 

__attribute__((used)) static int vega10_apply_state_adjust_rules(struct pp_hwmgr *hwmgr,
				struct pp_power_state  *request_ps,
			const struct pp_power_state *current_ps)
{
	struct amdgpu_device *adev = hwmgr->adev;
	struct vega10_power_state *vega10_ps =
				cast_phw_vega10_power_state(&request_ps->hardware);
	uint32_t sclk;
	uint32_t mclk;
	struct PP_Clocks minimum_clocks = {0};
	bool disable_mclk_switching;
	bool disable_mclk_switching_for_frame_lock;
	bool disable_mclk_switching_for_vr;
	bool force_mclk_high;
	const struct phm_clock_and_voltage_limits *max_limits;
	uint32_t i;
	struct vega10_hwmgr *data = hwmgr->backend;
	struct phm_ppt_v2_information *table_info =
			(struct phm_ppt_v2_information *)(hwmgr->pptable);
	int32_t count;
	uint32_t stable_pstate_sclk_dpm_percentage;
	uint32_t stable_pstate_sclk = 0, stable_pstate_mclk = 0;
	uint32_t latency;

	data->battery_state = (PP_StateUILabel_Battery ==
			request_ps->classification.ui_label);

	if (vega10_ps->performance_level_count != 2)
		pr_info("VI should always have 2 performance levels");

	max_limits = adev->pm.ac_power ?
			&(hwmgr->dyn_state.max_clock_voltage_on_ac) :
			&(hwmgr->dyn_state.max_clock_voltage_on_dc);

	/* Cap clock DPM tables at DC MAX if it is in DC. */
	if (!adev->pm.ac_power) {
		for (i = 0; i < vega10_ps->performance_level_count; i++) {
			if (vega10_ps->performance_levels[i].mem_clock >
				max_limits->mclk)
				vega10_ps->performance_levels[i].mem_clock =
						max_limits->mclk;
			if (vega10_ps->performance_levels[i].gfx_clock >
				max_limits->sclk)
				vega10_ps->performance_levels[i].gfx_clock =
						max_limits->sclk;
		}
	}

	/* result = PHM_CheckVBlankTime(hwmgr, &vblankTooShort);*/
	minimum_clocks.engineClock = hwmgr->display_config->min_core_set_clock;
	minimum_clocks.memoryClock = hwmgr->display_config->min_mem_set_clock;

	if (PP_CAP(PHM_PlatformCaps_StablePState)) {
		stable_pstate_sclk_dpm_percentage =
			data->registry_data.stable_pstate_sclk_dpm_percentage;
		PP_ASSERT_WITH_CODE(
			data->registry_data.stable_pstate_sclk_dpm_percentage >= 1 &&
			data->registry_data.stable_pstate_sclk_dpm_percentage <= 100,
			"percent sclk value must range from 1% to 100%, setting default value",
			stable_pstate_sclk_dpm_percentage = 75);

		max_limits = &(hwmgr->dyn_state.max_clock_voltage_on_ac);
		stable_pstate_sclk = (max_limits->sclk *
				stable_pstate_sclk_dpm_percentage) / 100;

		for (count = table_info->vdd_dep_on_sclk->count - 1;
				count >= 0; count--) {
			if (stable_pstate_sclk >=
					table_info->vdd_dep_on_sclk->entries[count].clk) {
				stable_pstate_sclk =
						table_info->vdd_dep_on_sclk->entries[count].clk;
				break;
			}
		}

		if (count < 0)
			stable_pstate_sclk = table_info->vdd_dep_on_sclk->entries[0].clk;

		stable_pstate_mclk = max_limits->mclk;

		minimum_clocks.engineClock = stable_pstate_sclk;
		minimum_clocks.memoryClock = stable_pstate_mclk;
	}

	disable_mclk_switching_for_frame_lock =
		PP_CAP(PHM_PlatformCaps_DisableMclkSwitchingForFrameLock);
	disable_mclk_switching_for_vr =
		PP_CAP(PHM_PlatformCaps_DisableMclkSwitchForVR);
	force_mclk_high = PP_CAP(PHM_PlatformCaps_ForceMclkHigh);

	if (hwmgr->display_config->num_display == 0)
		disable_mclk_switching = false;
	else
		disable_mclk_switching = ((1 < hwmgr->display_config->num_display) &&
					  !hwmgr->display_config->multi_monitor_in_sync) ||
			disable_mclk_switching_for_frame_lock ||
			disable_mclk_switching_for_vr ||
			force_mclk_high;

	sclk = vega10_ps->performance_levels[0].gfx_clock;
	mclk = vega10_ps->performance_levels[0].mem_clock;

	if (sclk < minimum_clocks.engineClock)
		sclk = (minimum_clocks.engineClock > max_limits->sclk) ?
				max_limits->sclk : minimum_clocks.engineClock;

	if (mclk < minimum_clocks.memoryClock)
		mclk = (minimum_clocks.memoryClock > max_limits->mclk) ?
				max_limits->mclk : minimum_clocks.memoryClock;

	vega10_ps->performance_levels[0].gfx_clock = sclk;
	vega10_ps->performance_levels[0].mem_clock = mclk;

	if (vega10_ps->performance_levels[1].gfx_clock <
			vega10_ps->performance_levels[0].gfx_clock)
		vega10_ps->performance_levels[0].gfx_clock =
				vega10_ps->performance_levels[1].gfx_clock;

	if (disable_mclk_switching) {
		/* Set Mclk the max of level 0 and level 1 */
		if (mclk < vega10_ps->performance_levels[1].mem_clock)
			mclk = vega10_ps->performance_levels[1].mem_clock;

		/* Find the lowest MCLK frequency that is within
		 * the tolerable latency defined in DAL
		 */
		latency = hwmgr->display_config->dce_tolerable_mclk_in_active_latency;
		for (i = 0; i < data->mclk_latency_table.count; i++) {
			if ((data->mclk_latency_table.entries[i].latency <= latency) &&
				(data->mclk_latency_table.entries[i].frequency >=
						vega10_ps->performance_levels[0].mem_clock) &&
				(data->mclk_latency_table.entries[i].frequency <=
						vega10_ps->performance_levels[1].mem_clock))
				mclk = data->mclk_latency_table.entries[i].frequency;
		}
		vega10_ps->performance_levels[0].mem_clock = mclk;
	} else {
		if (vega10_ps->performance_levels[1].mem_clock <
				vega10_ps->performance_levels[0].mem_clock)
			vega10_ps->performance_levels[0].mem_clock =
					vega10_ps->performance_levels[1].mem_clock;
	}

	if (PP_CAP(PHM_PlatformCaps_StablePState)) {
		for (i = 0; i < vega10_ps->performance_level_count; i++) {
			vega10_ps->performance_levels[i].gfx_clock = stable_pstate_sclk;
			vega10_ps->performance_levels[i].mem_clock = stable_pstate_mclk;
		}
	}

	return 0;
}
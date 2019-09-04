#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_5__ {int /*<<< orphan*/  sclk_down_hyst; int /*<<< orphan*/  sclk_up_hyst; int /*<<< orphan*/  sclk_activity; } ;
struct smu7_hwmgr {TYPE_2__ current_profile_setting; scalar_t__ vddc_phase_shed_control; } ;
struct TYPE_6__ {int /*<<< orphan*/  platformCaps; } ;
struct TYPE_4__ {int /*<<< orphan*/  vddc_phase_shed_limits_table; int /*<<< orphan*/  vddc_dependency_on_sclk; } ;
struct pp_hwmgr {TYPE_3__ platform_descriptor; TYPE_1__ dyn_state; scalar_t__ backend; } ;
struct SMU7_Discrete_GraphicsLevel {int MinVddc; int SclkFrequency; int MinVddcPhases; int CcPwrDynRm; int CcPwrDynRm1; int EnabledForThrottle; int CgSpllFuncCntl3; int CgSpllFuncCntl4; int SpllSpreadSpectrum; int SpllSpreadSpectrum2; int /*<<< orphan*/  ActivityLevel; int /*<<< orphan*/  DisplayWatermark; int /*<<< orphan*/  DeepSleepDivId; scalar_t__ PowerThrottle; scalar_t__ VoltageDownH; int /*<<< orphan*/  DownH; int /*<<< orphan*/  UpH; scalar_t__ EnabledForActivity; } ;

/* Variables and functions */
 int /*<<< orphan*/  CISLAND_MINIMUM_ENGINE_CLOCK ; 
 int /*<<< orphan*/  CONVERT_FROM_HOST_TO_SMC_UL (int) ; 
 int /*<<< orphan*/  CONVERT_FROM_HOST_TO_SMC_US (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHM_PlatformCaps_SclkDeepSleep ; 
 int /*<<< orphan*/  PPSMC_DISPLAY_WATERMARK_LOW ; 
 int PP_HOST_TO_SMC_UL (int) ; 
 int VOLTAGE_SCALE ; 
 int ci_calculate_sclk_params (struct pp_hwmgr*,int,struct SMU7_Discrete_GraphicsLevel*) ; 
 int ci_get_dependency_volt_by_clk (struct pp_hwmgr*,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  ci_get_sleep_divider_id_from_clock (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ci_populate_phase_value_based_on_sclk (struct pp_hwmgr*,int /*<<< orphan*/ ,int,int*) ; 
 scalar_t__ phm_cap_enabled (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int ci_populate_single_graphic_level(struct pp_hwmgr *hwmgr,
		uint32_t clock, struct SMU7_Discrete_GraphicsLevel *level)
{
	int result;
	struct smu7_hwmgr *data = (struct smu7_hwmgr *)(hwmgr->backend);


	result = ci_calculate_sclk_params(hwmgr, clock, level);

	/* populate graphics levels */
	result = ci_get_dependency_volt_by_clk(hwmgr,
			hwmgr->dyn_state.vddc_dependency_on_sclk, clock,
			(uint32_t *)(&level->MinVddc));
	if (result) {
		pr_err("vdd_dep_on_sclk table is NULL\n");
		return result;
	}

	level->SclkFrequency = clock;
	level->MinVddcPhases = 1;

	if (data->vddc_phase_shed_control)
		ci_populate_phase_value_based_on_sclk(hwmgr,
				hwmgr->dyn_state.vddc_phase_shed_limits_table,
				clock,
				&level->MinVddcPhases);

	level->ActivityLevel = data->current_profile_setting.sclk_activity;
	level->CcPwrDynRm = 0;
	level->CcPwrDynRm1 = 0;
	level->EnabledForActivity = 0;
	/* this level can be used for throttling.*/
	level->EnabledForThrottle = 1;
	level->UpH = data->current_profile_setting.sclk_up_hyst;
	level->DownH = data->current_profile_setting.sclk_down_hyst;
	level->VoltageDownH = 0;
	level->PowerThrottle = 0;


	if (phm_cap_enabled(hwmgr->platform_descriptor.platformCaps,
			PHM_PlatformCaps_SclkDeepSleep))
		level->DeepSleepDivId =
				ci_get_sleep_divider_id_from_clock(clock,
						CISLAND_MINIMUM_ENGINE_CLOCK);

	/* Default to slow, highest DPM level will be set to PPSMC_DISPLAY_WATERMARK_LOW later.*/
	level->DisplayWatermark = PPSMC_DISPLAY_WATERMARK_LOW;

	if (0 == result) {
		level->MinVddc = PP_HOST_TO_SMC_UL(level->MinVddc * VOLTAGE_SCALE);
		CONVERT_FROM_HOST_TO_SMC_UL(level->MinVddcPhases);
		CONVERT_FROM_HOST_TO_SMC_UL(level->SclkFrequency);
		CONVERT_FROM_HOST_TO_SMC_US(level->ActivityLevel);
		CONVERT_FROM_HOST_TO_SMC_UL(level->CgSpllFuncCntl3);
		CONVERT_FROM_HOST_TO_SMC_UL(level->CgSpllFuncCntl4);
		CONVERT_FROM_HOST_TO_SMC_UL(level->SpllSpreadSpectrum);
		CONVERT_FROM_HOST_TO_SMC_UL(level->SpllSpreadSpectrum2);
		CONVERT_FROM_HOST_TO_SMC_UL(level->CcPwrDynRm);
		CONVERT_FROM_HOST_TO_SMC_UL(level->CcPwrDynRm1);
	}

	return result;
}
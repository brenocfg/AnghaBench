#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_7__ {int /*<<< orphan*/  phase_shedding_limits_table; int /*<<< orphan*/  vddc_dependency_on_sclk; } ;
struct TYPE_8__ {TYPE_1__ dyn_state; } ;
struct TYPE_9__ {TYPE_2__ dpm; } ;
struct radeon_device {TYPE_3__ pm; } ;
struct ci_power_info {scalar_t__ caps_sclk_ds; scalar_t__ vddc_phase_shed_control; } ;
struct TYPE_10__ {int MinVddc; int SclkFrequency; int Flags; int MinVddcPhases; int CcPwrDynRm; int CcPwrDynRm1; int EnabledForThrottle; int CgSpllFuncCntl3; int CgSpllFuncCntl4; int SpllSpreadSpectrum; int SpllSpreadSpectrum2; int /*<<< orphan*/  ActivityLevel; int /*<<< orphan*/  DisplayWatermark; int /*<<< orphan*/  DeepSleepDivId; scalar_t__ PowerThrottle; scalar_t__ VoltageDownH; scalar_t__ DownH; scalar_t__ UpH; } ;
typedef  TYPE_4__ SMU7_Discrete_GraphicsLevel ;

/* Variables and functions */
 int /*<<< orphan*/  CISLAND_MINIMUM_ENGINE_CLOCK ; 
 int /*<<< orphan*/  PPSMC_DISPLAY_WATERMARK_LOW ; 
 int VOLTAGE_SCALE ; 
 int ci_calculate_sclk_params (struct radeon_device*,int,TYPE_4__*) ; 
 int ci_get_dependency_volt_by_clk (struct radeon_device*,int /*<<< orphan*/ *,int,int*) ; 
 struct ci_power_info* ci_get_pi (struct radeon_device*) ; 
 int /*<<< orphan*/  ci_get_sleep_divider_id_from_clock (struct radeon_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ci_populate_phase_value_based_on_sclk (struct radeon_device*,int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (int) ; 

__attribute__((used)) static int ci_populate_single_graphic_level(struct radeon_device *rdev,
					    u32 engine_clock,
					    u16 sclk_activity_level_t,
					    SMU7_Discrete_GraphicsLevel *graphic_level)
{
	struct ci_power_info *pi = ci_get_pi(rdev);
	int ret;

	ret = ci_calculate_sclk_params(rdev, engine_clock, graphic_level);
	if (ret)
		return ret;

	ret = ci_get_dependency_volt_by_clk(rdev,
					    &rdev->pm.dpm.dyn_state.vddc_dependency_on_sclk,
					    engine_clock, &graphic_level->MinVddc);
	if (ret)
		return ret;

	graphic_level->SclkFrequency = engine_clock;

	graphic_level->Flags =  0;
	graphic_level->MinVddcPhases = 1;

	if (pi->vddc_phase_shed_control)
		ci_populate_phase_value_based_on_sclk(rdev,
						      &rdev->pm.dpm.dyn_state.phase_shedding_limits_table,
						      engine_clock,
						      &graphic_level->MinVddcPhases);

	graphic_level->ActivityLevel = sclk_activity_level_t;

	graphic_level->CcPwrDynRm = 0;
	graphic_level->CcPwrDynRm1 = 0;
	graphic_level->EnabledForThrottle = 1;
	graphic_level->UpH = 0;
	graphic_level->DownH = 0;
	graphic_level->VoltageDownH = 0;
	graphic_level->PowerThrottle = 0;

	if (pi->caps_sclk_ds)
		graphic_level->DeepSleepDivId = ci_get_sleep_divider_id_from_clock(rdev,
										   engine_clock,
										   CISLAND_MINIMUM_ENGINE_CLOCK);

	graphic_level->DisplayWatermark = PPSMC_DISPLAY_WATERMARK_LOW;

	graphic_level->Flags = cpu_to_be32(graphic_level->Flags);
	graphic_level->MinVddc = cpu_to_be32(graphic_level->MinVddc * VOLTAGE_SCALE);
	graphic_level->MinVddcPhases = cpu_to_be32(graphic_level->MinVddcPhases);
	graphic_level->SclkFrequency = cpu_to_be32(graphic_level->SclkFrequency);
	graphic_level->ActivityLevel = cpu_to_be16(graphic_level->ActivityLevel);
	graphic_level->CgSpllFuncCntl3 = cpu_to_be32(graphic_level->CgSpllFuncCntl3);
	graphic_level->CgSpllFuncCntl4 = cpu_to_be32(graphic_level->CgSpllFuncCntl4);
	graphic_level->SpllSpreadSpectrum = cpu_to_be32(graphic_level->SpllSpreadSpectrum);
	graphic_level->SpllSpreadSpectrum2 = cpu_to_be32(graphic_level->SpllSpreadSpectrum2);
	graphic_level->CcPwrDynRm = cpu_to_be32(graphic_level->CcPwrDynRm);
	graphic_level->CcPwrDynRm1 = cpu_to_be32(graphic_level->CcPwrDynRm1);

	return 0;
}
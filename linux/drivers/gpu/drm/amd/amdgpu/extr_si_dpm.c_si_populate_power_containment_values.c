#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct si_ps {int performance_level_count; TYPE_1__* performance_levels; } ;
struct ni_power_info {int enable_power_containment; } ;
struct evergreen_power_info {int /*<<< orphan*/  vddc_voltage_table; } ;
struct amdgpu_ps {int dummy; } ;
struct amdgpu_device {int dummy; } ;
struct TYPE_9__ {int levelCount; TYPE_3__* levels; } ;
struct TYPE_7__ {int /*<<< orphan*/  PwrEfficiencyRatio; int /*<<< orphan*/  BelowSafeInc; int /*<<< orphan*/  AboveSafeInc; int /*<<< orphan*/  NearTDPDec; scalar_t__ MaxPS; } ;
struct TYPE_8__ {TYPE_2__ dpm2; } ;
struct TYPE_6__ {int sclk; int /*<<< orphan*/  vddc; } ;
typedef  int /*<<< orphan*/  SISLANDS_SMC_VOLTAGE_VALUE ;
typedef  TYPE_4__ SISLANDS_SMC_SWSTATE ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SISLANDS_DPM2_ABOVE_SAFE_INC ; 
 int /*<<< orphan*/  SISLANDS_DPM2_BELOW_SAFE_INC ; 
 scalar_t__ SISLANDS_DPM2_MAXPS_PERCENT_H ; 
 scalar_t__ SISLANDS_DPM2_MAXPS_PERCENT_M ; 
 int SISLANDS_DPM2_MAX_PULSE_SKIP ; 
 int /*<<< orphan*/  SISLANDS_DPM2_NEAR_TDP_DEC ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 struct evergreen_power_info* evergreen_get_pi (struct amdgpu_device*) ; 
 struct ni_power_info* ni_get_pi (struct amdgpu_device*) ; 
 int /*<<< orphan*/  si_calculate_power_efficiency_ratio (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct si_ps* si_get_ps (struct amdgpu_ps*) ; 
 int si_get_std_voltage_value (struct amdgpu_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int si_populate_voltage_value (struct amdgpu_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int si_should_disable_uvd_powertune (struct amdgpu_device*,struct amdgpu_ps*) ; 

__attribute__((used)) static int si_populate_power_containment_values(struct amdgpu_device *adev,
						struct amdgpu_ps *amdgpu_state,
						SISLANDS_SMC_SWSTATE *smc_state)
{
	struct evergreen_power_info *eg_pi = evergreen_get_pi(adev);
	struct ni_power_info *ni_pi = ni_get_pi(adev);
	struct  si_ps *state = si_get_ps(amdgpu_state);
	SISLANDS_SMC_VOLTAGE_VALUE vddc;
	u32 prev_sclk;
	u32 max_sclk;
	u32 min_sclk;
	u16 prev_std_vddc;
	u16 curr_std_vddc;
	int i;
	u16 pwr_efficiency_ratio;
	u8 max_ps_percent;
	bool disable_uvd_power_tune;
	int ret;

	if (ni_pi->enable_power_containment == false)
		return 0;

	if (state->performance_level_count == 0)
		return -EINVAL;

	if (smc_state->levelCount != state->performance_level_count)
		return -EINVAL;

	disable_uvd_power_tune = si_should_disable_uvd_powertune(adev, amdgpu_state);

	smc_state->levels[0].dpm2.MaxPS = 0;
	smc_state->levels[0].dpm2.NearTDPDec = 0;
	smc_state->levels[0].dpm2.AboveSafeInc = 0;
	smc_state->levels[0].dpm2.BelowSafeInc = 0;
	smc_state->levels[0].dpm2.PwrEfficiencyRatio = 0;

	for (i = 1; i < state->performance_level_count; i++) {
		prev_sclk = state->performance_levels[i-1].sclk;
		max_sclk  = state->performance_levels[i].sclk;
		if (i == 1)
			max_ps_percent = SISLANDS_DPM2_MAXPS_PERCENT_M;
		else
			max_ps_percent = SISLANDS_DPM2_MAXPS_PERCENT_H;

		if (prev_sclk > max_sclk)
			return -EINVAL;

		if ((max_ps_percent == 0) ||
		    (prev_sclk == max_sclk) ||
		    disable_uvd_power_tune)
			min_sclk = max_sclk;
		else if (i == 1)
			min_sclk = prev_sclk;
		else
			min_sclk = (prev_sclk * (u32)max_ps_percent) / 100;

		if (min_sclk < state->performance_levels[0].sclk)
			min_sclk = state->performance_levels[0].sclk;

		if (min_sclk == 0)
			return -EINVAL;

		ret = si_populate_voltage_value(adev, &eg_pi->vddc_voltage_table,
						state->performance_levels[i-1].vddc, &vddc);
		if (ret)
			return ret;

		ret = si_get_std_voltage_value(adev, &vddc, &prev_std_vddc);
		if (ret)
			return ret;

		ret = si_populate_voltage_value(adev, &eg_pi->vddc_voltage_table,
						state->performance_levels[i].vddc, &vddc);
		if (ret)
			return ret;

		ret = si_get_std_voltage_value(adev, &vddc, &curr_std_vddc);
		if (ret)
			return ret;

		pwr_efficiency_ratio = si_calculate_power_efficiency_ratio(adev,
									   prev_std_vddc, curr_std_vddc);

		smc_state->levels[i].dpm2.MaxPS = (u8)((SISLANDS_DPM2_MAX_PULSE_SKIP * (max_sclk - min_sclk)) / max_sclk);
		smc_state->levels[i].dpm2.NearTDPDec = SISLANDS_DPM2_NEAR_TDP_DEC;
		smc_state->levels[i].dpm2.AboveSafeInc = SISLANDS_DPM2_ABOVE_SAFE_INC;
		smc_state->levels[i].dpm2.BelowSafeInc = SISLANDS_DPM2_BELOW_SAFE_INC;
		smc_state->levels[i].dpm2.PwrEfficiencyRatio = cpu_to_be16(pwr_efficiency_ratio);
	}

	return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct rv7xx_power_info {int /*<<< orphan*/  sram_end; scalar_t__ state_table_start; } ;
struct radeon_ps {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  tdp_adjustment; } ;
struct TYPE_9__ {TYPE_1__ dpm; } ;
struct radeon_device {TYPE_2__ pm; } ;
struct ni_ps {int performance_level_count; TYPE_3__* performance_levels; } ;
struct ni_power_info {int enable_power_containment; } ;
struct evergreen_power_info {scalar_t__ uvd_enabled; } ;
struct TYPE_13__ {int levelCount; TYPE_5__* levels; } ;
struct TYPE_11__ {int /*<<< orphan*/  BelowSafeInc; int /*<<< orphan*/  AboveSafeInc; int /*<<< orphan*/  NearTDPDec; scalar_t__ MaxPS; } ;
struct TYPE_12__ {int /*<<< orphan*/  stateFlags; TYPE_4__ dpm2; } ;
struct TYPE_10__ {int sclk; } ;
typedef  TYPE_6__ NISLANDS_SMC_SWSTATE ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NISLANDS_DPM2_ABOVE_SAFE_INC ; 
 int /*<<< orphan*/  NISLANDS_DPM2_BELOW_SAFE_INC ; 
 scalar_t__ NISLANDS_DPM2_MAXPS_PERCENT_H ; 
 scalar_t__ NISLANDS_DPM2_MAXPS_PERCENT_M ; 
 int NISLANDS_DPM2_MAX_PULSE_SKIP ; 
 int /*<<< orphan*/  NISLANDS_DPM2_NEAR_TDP_DEC ; 
 int /*<<< orphan*/  NISLANDS_SMC_STATETABLE ; 
 int /*<<< orphan*/  PPSMC_STATEFLAG_POWERBOOST ; 
 int /*<<< orphan*/  PP_NIslands_DPM2Parameters ; 
 int /*<<< orphan*/  PowerBoostLimit ; 
 int /*<<< orphan*/  dpm2Params ; 
 struct evergreen_power_info* evergreen_get_pi (struct radeon_device*) ; 
 int ni_calculate_adjusted_tdp_limits (struct radeon_device*,int,int /*<<< orphan*/ ,int*,int*) ; 
 int ni_calculate_power_boost_limit (struct radeon_device*,struct radeon_ps*,int) ; 
 struct ni_power_info* ni_get_pi (struct radeon_device*) ; 
 struct ni_ps* ni_get_ps (struct radeon_ps*) ; 
 int /*<<< orphan*/  ni_get_smc_power_scaling_factor (struct radeon_device*) ; 
 int /*<<< orphan*/  ni_scale_power_for_smc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rv7xx_power_info* rv770_get_pi (struct radeon_device*) ; 
 int rv770_write_smc_sram_dword (struct radeon_device*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ni_populate_power_containment_values(struct radeon_device *rdev,
						struct radeon_ps *radeon_state,
						NISLANDS_SMC_SWSTATE *smc_state)
{
	struct rv7xx_power_info *pi = rv770_get_pi(rdev);
	struct evergreen_power_info *eg_pi = evergreen_get_pi(rdev);
	struct ni_power_info *ni_pi = ni_get_pi(rdev);
	struct ni_ps *state = ni_get_ps(radeon_state);
	u32 prev_sclk;
	u32 max_sclk;
	u32 min_sclk;
	int i, ret;
	u32 tdp_limit;
	u32 near_tdp_limit;
	u32 power_boost_limit;
	u8 max_ps_percent;

	if (ni_pi->enable_power_containment == false)
		return 0;

	if (state->performance_level_count == 0)
		return -EINVAL;

	if (smc_state->levelCount != state->performance_level_count)
		return -EINVAL;

	ret = ni_calculate_adjusted_tdp_limits(rdev,
					       false, /* ??? */
					       rdev->pm.dpm.tdp_adjustment,
					       &tdp_limit,
					       &near_tdp_limit);
	if (ret)
		return ret;

	power_boost_limit = ni_calculate_power_boost_limit(rdev, radeon_state, near_tdp_limit);

	ret = rv770_write_smc_sram_dword(rdev,
					 pi->state_table_start +
					 offsetof(NISLANDS_SMC_STATETABLE, dpm2Params) +
					 offsetof(PP_NIslands_DPM2Parameters, PowerBoostLimit),
					 ni_scale_power_for_smc(power_boost_limit, ni_get_smc_power_scaling_factor(rdev)),
					 pi->sram_end);
	if (ret)
		power_boost_limit = 0;

	smc_state->levels[0].dpm2.MaxPS = 0;
	smc_state->levels[0].dpm2.NearTDPDec = 0;
	smc_state->levels[0].dpm2.AboveSafeInc = 0;
	smc_state->levels[0].dpm2.BelowSafeInc = 0;
	smc_state->levels[0].stateFlags |= power_boost_limit ? PPSMC_STATEFLAG_POWERBOOST : 0;

	for (i = 1; i < state->performance_level_count; i++) {
		prev_sclk = state->performance_levels[i-1].sclk;
		max_sclk  = state->performance_levels[i].sclk;
		max_ps_percent = (i != (state->performance_level_count - 1)) ?
			NISLANDS_DPM2_MAXPS_PERCENT_M : NISLANDS_DPM2_MAXPS_PERCENT_H;

		if (max_sclk < prev_sclk)
			return -EINVAL;

		if ((max_ps_percent == 0) || (prev_sclk == max_sclk) || eg_pi->uvd_enabled)
			min_sclk = max_sclk;
		else if (1 == i)
			min_sclk = prev_sclk;
		else
			min_sclk = (prev_sclk * (u32)max_ps_percent) / 100;

		if (min_sclk < state->performance_levels[0].sclk)
			min_sclk = state->performance_levels[0].sclk;

		if (min_sclk == 0)
			return -EINVAL;

		smc_state->levels[i].dpm2.MaxPS =
			(u8)((NISLANDS_DPM2_MAX_PULSE_SKIP * (max_sclk - min_sclk)) / max_sclk);
		smc_state->levels[i].dpm2.NearTDPDec = NISLANDS_DPM2_NEAR_TDP_DEC;
		smc_state->levels[i].dpm2.AboveSafeInc = NISLANDS_DPM2_ABOVE_SAFE_INC;
		smc_state->levels[i].dpm2.BelowSafeInc = NISLANDS_DPM2_BELOW_SAFE_INC;
		smc_state->levels[i].stateFlags |=
			((i != (state->performance_level_count - 1)) && power_boost_limit) ?
			PPSMC_STATEFLAG_POWERBOOST : 0;
	}

	return 0;
}
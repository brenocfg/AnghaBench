#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct si_ulv_param {scalar_t__ one_pcie_lane_in_ulv; int /*<<< orphan*/  pl; } ;
struct si_power_info {struct si_ulv_param ulv; } ;
struct evergreen_power_info {scalar_t__ sclk_deep_sleep; } ;
struct amdgpu_device {int dummy; } ;
struct TYPE_5__ {int ACIndex; int /*<<< orphan*/  vddc; int /*<<< orphan*/  std_vddc; scalar_t__ arbRefreshState; int /*<<< orphan*/  stateFlags; } ;
struct TYPE_4__ {int levelCount; int /*<<< orphan*/  flags; TYPE_3__* levels; } ;
typedef  TYPE_1__ SISLANDS_SMC_SWSTATE ;

/* Variables and functions */
 int /*<<< orphan*/  PPSMC_STATEFLAG_DEEPSLEEP_BYPASS ; 
 int /*<<< orphan*/  PPSMC_STATEFLAG_DEEPSLEEP_THROTTLE ; 
 int /*<<< orphan*/  PPSMC_SWSTATE_FLAG_DC ; 
 int /*<<< orphan*/  PPSMC_SWSTATE_FLAG_PCIE_X1 ; 
 scalar_t__ SCLK_MIN_DEEPSLEEP_FREQ ; 
 scalar_t__ SISLANDS_ULV_STATE_ARB_INDEX ; 
 struct evergreen_power_info* evergreen_get_pi (struct amdgpu_device*) ; 
 int si_convert_power_level_to_smc (struct amdgpu_device*,int /*<<< orphan*/ *,TYPE_3__*) ; 
 struct si_power_info* si_get_pi (struct amdgpu_device*) ; 

__attribute__((used)) static int si_populate_ulv_state(struct amdgpu_device *adev,
				 SISLANDS_SMC_SWSTATE *state)
{
	struct evergreen_power_info *eg_pi = evergreen_get_pi(adev);
	struct si_power_info *si_pi = si_get_pi(adev);
	struct si_ulv_param *ulv = &si_pi->ulv;
	u32 sclk_in_sr = 1350; /* ??? */
	int ret;

	ret = si_convert_power_level_to_smc(adev, &ulv->pl,
					    &state->levels[0]);
	if (!ret) {
		if (eg_pi->sclk_deep_sleep) {
			if (sclk_in_sr <= SCLK_MIN_DEEPSLEEP_FREQ)
				state->levels[0].stateFlags |= PPSMC_STATEFLAG_DEEPSLEEP_BYPASS;
			else
				state->levels[0].stateFlags |= PPSMC_STATEFLAG_DEEPSLEEP_THROTTLE;
		}
		if (ulv->one_pcie_lane_in_ulv)
			state->flags |= PPSMC_SWSTATE_FLAG_PCIE_X1;
		state->levels[0].arbRefreshState = (u8)(SISLANDS_ULV_STATE_ARB_INDEX);
		state->levels[0].ACIndex = 1;
		state->levels[0].std_vddc = state->levels[0].vddc;
		state->levelCount = 1;

		state->flags |= PPSMC_SWSTATE_FLAG_DC;
	}

	return ret;
}
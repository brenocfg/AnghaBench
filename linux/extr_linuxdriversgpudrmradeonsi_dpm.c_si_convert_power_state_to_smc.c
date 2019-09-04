#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_8__ ;
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct si_power_info {scalar_t__ sclk_deep_sleep_above_low; } ;
struct radeon_ps {scalar_t__ dclk; scalar_t__ vclk; } ;
struct radeon_device {int dummy; } ;
struct ni_ps {int performance_level_count; TYPE_7__* performance_levels; scalar_t__ dc_compatible; } ;
struct ni_power_info {int enable_power_containment; int enable_sq_ramping; } ;
struct evergreen_power_info {int uvd_enabled; scalar_t__ dynamic_ac_timing; scalar_t__ sclk_deep_sleep; scalar_t__ smu_uvd_hs; } ;
struct TYPE_11__ {scalar_t__ ACIndex; void* displayWatermark; scalar_t__ arbRefreshState; int /*<<< orphan*/  stateFlags; } ;
struct TYPE_10__ {int sclk; } ;
struct TYPE_9__ {scalar_t__ levelCount; TYPE_8__* levels; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ SISLANDS_SMC_SWSTATE ;

/* Variables and functions */
 int EINVAL ; 
 void* PPSMC_DISPLAY_WATERMARK_HIGH ; 
 void* PPSMC_DISPLAY_WATERMARK_LOW ; 
 int /*<<< orphan*/  PPSMC_STATEFLAG_DEEPSLEEP_BYPASS ; 
 int /*<<< orphan*/  PPSMC_STATEFLAG_DEEPSLEEP_THROTTLE ; 
 int /*<<< orphan*/  PPSMC_SWSTATE_FLAG_DC ; 
 int /*<<< orphan*/  PPSMC_SWSTATE_FLAG_UVD ; 
 scalar_t__ SCLK_MIN_DEEPSLEEP_FREQ ; 
 scalar_t__ SISLANDS_DRIVER_STATE_ARB_INDEX ; 
 int SISLANDS_MAX_HARDWARE_POWERLEVELS ; 
 scalar_t__ SISLANDS_MCREGISTERTABLE_FIRST_DRIVERSTATE_SLOT ; 
 int /*<<< orphan*/  SI_SMC_SOFT_REGISTER_watermark_threshold ; 
 struct evergreen_power_info* evergreen_get_pi (struct radeon_device*) ; 
 struct ni_power_info* ni_get_pi (struct radeon_device*) ; 
 struct ni_ps* ni_get_ps (struct radeon_ps*) ; 
 int si_convert_power_level_to_smc (struct radeon_device*,TYPE_7__*,TYPE_8__*) ; 
 struct si_power_info* si_get_pi (struct radeon_device*) ; 
 int si_populate_power_containment_values (struct radeon_device*,struct radeon_ps*,TYPE_1__*) ; 
 int /*<<< orphan*/  si_populate_smc_sp (struct radeon_device*,struct radeon_ps*,TYPE_1__*) ; 
 int si_populate_smc_t (struct radeon_device*,struct radeon_ps*,TYPE_1__*) ; 
 int si_populate_sq_ramping_values (struct radeon_device*,struct radeon_ps*,TYPE_1__*) ; 
 int /*<<< orphan*/  si_write_smc_soft_register (struct radeon_device*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int si_convert_power_state_to_smc(struct radeon_device *rdev,
					 struct radeon_ps *radeon_state,
					 SISLANDS_SMC_SWSTATE *smc_state)
{
	struct evergreen_power_info *eg_pi = evergreen_get_pi(rdev);
	struct ni_power_info *ni_pi = ni_get_pi(rdev);
	struct si_power_info *si_pi = si_get_pi(rdev);
	struct ni_ps *state = ni_get_ps(radeon_state);
	int i, ret;
	u32 threshold;
	u32 sclk_in_sr = 1350; /* ??? */

	if (state->performance_level_count > SISLANDS_MAX_HARDWARE_POWERLEVELS)
		return -EINVAL;

	threshold = state->performance_levels[state->performance_level_count-1].sclk * 100 / 100;

	if (radeon_state->vclk && radeon_state->dclk) {
		eg_pi->uvd_enabled = true;
		if (eg_pi->smu_uvd_hs)
			smc_state->flags |= PPSMC_SWSTATE_FLAG_UVD;
	} else {
		eg_pi->uvd_enabled = false;
	}

	if (state->dc_compatible)
		smc_state->flags |= PPSMC_SWSTATE_FLAG_DC;

	smc_state->levelCount = 0;
	for (i = 0; i < state->performance_level_count; i++) {
		if (eg_pi->sclk_deep_sleep) {
			if ((i == 0) || si_pi->sclk_deep_sleep_above_low) {
				if (sclk_in_sr <= SCLK_MIN_DEEPSLEEP_FREQ)
					smc_state->levels[i].stateFlags |= PPSMC_STATEFLAG_DEEPSLEEP_BYPASS;
				else
					smc_state->levels[i].stateFlags |= PPSMC_STATEFLAG_DEEPSLEEP_THROTTLE;
			}
		}

		ret = si_convert_power_level_to_smc(rdev, &state->performance_levels[i],
						    &smc_state->levels[i]);
		smc_state->levels[i].arbRefreshState =
			(u8)(SISLANDS_DRIVER_STATE_ARB_INDEX + i);

		if (ret)
			return ret;

		if (ni_pi->enable_power_containment)
			smc_state->levels[i].displayWatermark =
				(state->performance_levels[i].sclk < threshold) ?
				PPSMC_DISPLAY_WATERMARK_LOW : PPSMC_DISPLAY_WATERMARK_HIGH;
		else
			smc_state->levels[i].displayWatermark = (i < 2) ?
				PPSMC_DISPLAY_WATERMARK_LOW : PPSMC_DISPLAY_WATERMARK_HIGH;

		if (eg_pi->dynamic_ac_timing)
			smc_state->levels[i].ACIndex = SISLANDS_MCREGISTERTABLE_FIRST_DRIVERSTATE_SLOT + i;
		else
			smc_state->levels[i].ACIndex = 0;

		smc_state->levelCount++;
	}

	si_write_smc_soft_register(rdev,
				   SI_SMC_SOFT_REGISTER_watermark_threshold,
				   threshold / 512);

	si_populate_smc_sp(rdev, radeon_state, smc_state);

	ret = si_populate_power_containment_values(rdev, radeon_state, smc_state);
	if (ret)
		ni_pi->enable_power_containment = false;

	ret = si_populate_sq_ramping_values(rdev, radeon_state, smc_state);
	if (ret)
		ni_pi->enable_sq_ramping = false;

	return si_populate_smc_t(rdev, radeon_state, smc_state);
}
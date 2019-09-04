#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct rv7xx_ps {int /*<<< orphan*/  high; int /*<<< orphan*/  medium; int /*<<< orphan*/  low; } ;
struct radeon_ps {int caps; } ;
struct radeon_device {int dummy; } ;
struct evergreen_power_info {scalar_t__ dynamic_ac_timing; } ;
struct TYPE_7__ {int ACIndex; int /*<<< orphan*/  arbValue; } ;
struct TYPE_6__ {TYPE_5__* levels; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ RV770_SMC_SWSTATE ;

/* Variables and functions */
 int ATOM_PPLIB_DISALLOW_ON_DC ; 
 int /*<<< orphan*/  MC_CG_ARB_FREQ_F1 ; 
 int /*<<< orphan*/  MC_CG_ARB_FREQ_F2 ; 
 int /*<<< orphan*/  MC_CG_ARB_FREQ_F3 ; 
 int /*<<< orphan*/  PPSMC_DISPLAY_WATERMARK_HIGH ; 
 int /*<<< orphan*/  PPSMC_DISPLAY_WATERMARK_LOW ; 
 int /*<<< orphan*/  PPSMC_SWSTATE_FLAG_DC ; 
 int cypress_convert_power_level_to_smc (struct radeon_device*,int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ ) ; 
 struct evergreen_power_info* evergreen_get_pi (struct radeon_device*) ; 
 struct rv7xx_ps* rv770_get_ps (struct radeon_ps*) ; 
 int /*<<< orphan*/  rv770_populate_smc_sp (struct radeon_device*,struct radeon_ps*,TYPE_1__*) ; 
 int rv770_populate_smc_t (struct radeon_device*,struct radeon_ps*,TYPE_1__*) ; 

__attribute__((used)) static int cypress_convert_power_state_to_smc(struct radeon_device *rdev,
					      struct radeon_ps *radeon_state,
					      RV770_SMC_SWSTATE *smc_state)
{
	struct rv7xx_ps *state = rv770_get_ps(radeon_state);
	struct evergreen_power_info *eg_pi = evergreen_get_pi(rdev);
	int ret;

	if (!(radeon_state->caps & ATOM_PPLIB_DISALLOW_ON_DC))
		smc_state->flags |= PPSMC_SWSTATE_FLAG_DC;

	ret = cypress_convert_power_level_to_smc(rdev,
						 &state->low,
						 &smc_state->levels[0],
						 PPSMC_DISPLAY_WATERMARK_LOW);
	if (ret)
		return ret;

	ret = cypress_convert_power_level_to_smc(rdev,
						 &state->medium,
						 &smc_state->levels[1],
						 PPSMC_DISPLAY_WATERMARK_LOW);
	if (ret)
		return ret;

	ret = cypress_convert_power_level_to_smc(rdev,
						 &state->high,
						 &smc_state->levels[2],
						 PPSMC_DISPLAY_WATERMARK_HIGH);
	if (ret)
		return ret;

	smc_state->levels[0].arbValue = MC_CG_ARB_FREQ_F1;
	smc_state->levels[1].arbValue = MC_CG_ARB_FREQ_F2;
	smc_state->levels[2].arbValue = MC_CG_ARB_FREQ_F3;

	if (eg_pi->dynamic_ac_timing) {
		smc_state->levels[0].ACIndex = 2;
		smc_state->levels[1].ACIndex = 3;
		smc_state->levels[2].ACIndex = 4;
	} else {
		smc_state->levels[0].ACIndex = 0;
		smc_state->levels[1].ACIndex = 0;
		smc_state->levels[2].ACIndex = 0;
	}

	rv770_populate_smc_sp(rdev, radeon_state, smc_state);

	return rv770_populate_smc_t(rdev, radeon_state, smc_state);
}
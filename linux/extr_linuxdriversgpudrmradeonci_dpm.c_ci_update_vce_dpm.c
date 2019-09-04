#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct radeon_ps {scalar_t__ evclk; } ;
struct radeon_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  VceBootLevel; } ;
struct ci_power_info {TYPE_1__ smc_state_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPM_TABLE_475 ; 
 int /*<<< orphan*/  RADEON_CG_BLOCK_VCE ; 
 int /*<<< orphan*/  RREG32_SMC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VceBootLevel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VceBootLevel_MASK ; 
 int /*<<< orphan*/  WREG32_SMC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ci_enable_vce_dpm (struct radeon_device*,int) ; 
 struct ci_power_info* ci_get_pi (struct radeon_device*) ; 
 int /*<<< orphan*/  ci_get_vce_boot_level (struct radeon_device*) ; 
 int /*<<< orphan*/  cik_update_cg (struct radeon_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ci_update_vce_dpm(struct radeon_device *rdev,
			     struct radeon_ps *radeon_new_state,
			     struct radeon_ps *radeon_current_state)
{
	struct ci_power_info *pi = ci_get_pi(rdev);
	int ret = 0;
	u32 tmp;

	if (radeon_current_state->evclk != radeon_new_state->evclk) {
		if (radeon_new_state->evclk) {
			/* turn the clocks on when encoding */
			cik_update_cg(rdev, RADEON_CG_BLOCK_VCE, false);

			pi->smc_state_table.VceBootLevel = ci_get_vce_boot_level(rdev);
			tmp = RREG32_SMC(DPM_TABLE_475);
			tmp &= ~VceBootLevel_MASK;
			tmp |= VceBootLevel(pi->smc_state_table.VceBootLevel);
			WREG32_SMC(DPM_TABLE_475, tmp);

			ret = ci_enable_vce_dpm(rdev, true);
		} else {
			/* turn the clocks off when not encoding */
			cik_update_cg(rdev, RADEON_CG_BLOCK_VCE, true);

			ret = ci_enable_vce_dpm(rdev, false);
		}
	}
	return ret;
}
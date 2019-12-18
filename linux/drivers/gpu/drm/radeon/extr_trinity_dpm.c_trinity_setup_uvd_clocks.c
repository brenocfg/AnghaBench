#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct trinity_power_info {scalar_t__ enable_gfx_power_gating; scalar_t__ uvd_dpm; } ;
struct radeon_ps {int /*<<< orphan*/  dclk; int /*<<< orphan*/  vclk; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_MISC_REG ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  radeon_set_uvd_clocks (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct trinity_power_info* trinity_get_pi (struct radeon_device*) ; 
 int /*<<< orphan*/  trinity_gfx_powergating_enable (struct radeon_device*,int) ; 
 int /*<<< orphan*/  trinity_setup_uvd_clock_table (struct radeon_device*,struct radeon_ps*) ; 
 int /*<<< orphan*/  trinity_setup_uvd_dpm_interval (struct radeon_device*,int) ; 
 scalar_t__ trinity_uvd_clocks_equal (struct radeon_ps*,struct radeon_ps*) ; 
 scalar_t__ trinity_uvd_clocks_zero (struct radeon_ps*) ; 
 int /*<<< orphan*/  trinity_uvd_dpm_config (struct radeon_device*) ; 

__attribute__((used)) static void trinity_setup_uvd_clocks(struct radeon_device *rdev,
				     struct radeon_ps *new_rps,
				     struct radeon_ps *old_rps)
{
	struct trinity_power_info *pi = trinity_get_pi(rdev);

	if (pi->enable_gfx_power_gating) {
		trinity_gfx_powergating_enable(rdev, false);
	}

	if (pi->uvd_dpm) {
		if (trinity_uvd_clocks_zero(new_rps) &&
		    !trinity_uvd_clocks_zero(old_rps)) {
			trinity_setup_uvd_dpm_interval(rdev, 0);
		} else if (!trinity_uvd_clocks_zero(new_rps)) {
			trinity_setup_uvd_clock_table(rdev, new_rps);

			if (trinity_uvd_clocks_zero(old_rps)) {
				u32 tmp = RREG32(CG_MISC_REG);
				tmp &= 0xfffffffd;
				WREG32(CG_MISC_REG, tmp);

				radeon_set_uvd_clocks(rdev, new_rps->vclk, new_rps->dclk);

				trinity_setup_uvd_dpm_interval(rdev, 3000);
			}
		}
		trinity_uvd_dpm_config(rdev);
	} else {
		if (trinity_uvd_clocks_zero(new_rps) ||
		    trinity_uvd_clocks_equal(new_rps, old_rps))
			return;

		radeon_set_uvd_clocks(rdev, new_rps->vclk, new_rps->dclk);
	}

	if (pi->enable_gfx_power_gating) {
		trinity_gfx_powergating_enable(rdev, true);
	}
}
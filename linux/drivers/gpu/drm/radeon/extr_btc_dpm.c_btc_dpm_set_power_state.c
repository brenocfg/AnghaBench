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
struct radeon_ps {int dummy; } ;
struct radeon_device {int dummy; } ;
struct evergreen_power_info {scalar_t__ pcie_performance_request; scalar_t__ dynamic_ac_timing; scalar_t__ smu_uvd_hs; struct radeon_ps current_rps; struct radeon_ps requested_rps; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int btc_disable_ulv (struct radeon_device*) ; 
 int /*<<< orphan*/  btc_notify_uvd_to_smc (struct radeon_device*,struct radeon_ps*) ; 
 int /*<<< orphan*/  btc_set_at_for_uvd (struct radeon_device*,struct radeon_ps*) ; 
 int /*<<< orphan*/  btc_set_boot_state_timing (struct radeon_device*) ; 
 int btc_set_power_state_conditionally_enable_ulv (struct radeon_device*,struct radeon_ps*) ; 
 int /*<<< orphan*/  cypress_notify_link_speed_change_after_state_change (struct radeon_device*,struct radeon_ps*,struct radeon_ps*) ; 
 int /*<<< orphan*/  cypress_notify_link_speed_change_before_state_change (struct radeon_device*,struct radeon_ps*,struct radeon_ps*) ; 
 int /*<<< orphan*/  cypress_program_memory_timing_parameters (struct radeon_device*,struct radeon_ps*) ; 
 int cypress_upload_mc_reg_table (struct radeon_device*,struct radeon_ps*) ; 
 int cypress_upload_sw_state (struct radeon_device*,struct radeon_ps*) ; 
 struct evergreen_power_info* evergreen_get_pi (struct radeon_device*) ; 
 int rv770_halt_smc (struct radeon_device*) ; 
 int rv770_restrict_performance_levels_before_switch (struct radeon_device*) ; 
 int rv770_resume_smc (struct radeon_device*) ; 
 int rv770_set_sw_state (struct radeon_device*) ; 
 int /*<<< orphan*/  rv770_set_uvd_clock_after_set_eng_clock (struct radeon_device*,struct radeon_ps*,struct radeon_ps*) ; 
 int /*<<< orphan*/  rv770_set_uvd_clock_before_set_eng_clock (struct radeon_device*,struct radeon_ps*,struct radeon_ps*) ; 

int btc_dpm_set_power_state(struct radeon_device *rdev)
{
	struct evergreen_power_info *eg_pi = evergreen_get_pi(rdev);
	struct radeon_ps *new_ps = &eg_pi->requested_rps;
	struct radeon_ps *old_ps = &eg_pi->current_rps;
	int ret;

	ret = btc_disable_ulv(rdev);
	btc_set_boot_state_timing(rdev);
	ret = rv770_restrict_performance_levels_before_switch(rdev);
	if (ret) {
		DRM_ERROR("rv770_restrict_performance_levels_before_switch failed\n");
		return ret;
	}
	if (eg_pi->pcie_performance_request)
		cypress_notify_link_speed_change_before_state_change(rdev, new_ps, old_ps);

	rv770_set_uvd_clock_before_set_eng_clock(rdev, new_ps, old_ps);
	ret = rv770_halt_smc(rdev);
	if (ret) {
		DRM_ERROR("rv770_halt_smc failed\n");
		return ret;
	}
	btc_set_at_for_uvd(rdev, new_ps);
	if (eg_pi->smu_uvd_hs)
		btc_notify_uvd_to_smc(rdev, new_ps);
	ret = cypress_upload_sw_state(rdev, new_ps);
	if (ret) {
		DRM_ERROR("cypress_upload_sw_state failed\n");
		return ret;
	}
	if (eg_pi->dynamic_ac_timing) {
		ret = cypress_upload_mc_reg_table(rdev, new_ps);
		if (ret) {
			DRM_ERROR("cypress_upload_mc_reg_table failed\n");
			return ret;
		}
	}

	cypress_program_memory_timing_parameters(rdev, new_ps);

	ret = rv770_resume_smc(rdev);
	if (ret) {
		DRM_ERROR("rv770_resume_smc failed\n");
		return ret;
	}
	ret = rv770_set_sw_state(rdev);
	if (ret) {
		DRM_ERROR("rv770_set_sw_state failed\n");
		return ret;
	}
	rv770_set_uvd_clock_after_set_eng_clock(rdev, new_ps, old_ps);

	if (eg_pi->pcie_performance_request)
		cypress_notify_link_speed_change_after_state_change(rdev, new_ps, old_ps);

	ret = btc_set_power_state_conditionally_enable_ulv(rdev, new_ps);
	if (ret) {
		DRM_ERROR("btc_set_power_state_conditionally_enable_ulv failed\n");
		return ret;
	}

	return 0;
}
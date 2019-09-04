#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct radeon_ps {int dummy; } ;
struct TYPE_3__ {struct radeon_ps* current_ps; struct radeon_ps* requested_ps; } ;
struct TYPE_4__ {TYPE_1__ dpm; } ;
struct radeon_device {TYPE_2__ pm; } ;
struct evergreen_power_info {scalar_t__ pcie_performance_request; scalar_t__ dynamic_ac_timing; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
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

int cypress_dpm_set_power_state(struct radeon_device *rdev)
{
	struct evergreen_power_info *eg_pi = evergreen_get_pi(rdev);
	struct radeon_ps *new_ps = rdev->pm.dpm.requested_ps;
	struct radeon_ps *old_ps = rdev->pm.dpm.current_ps;
	int ret;

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

	return 0;
}
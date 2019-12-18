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
struct evergreen_power_info {scalar_t__ dynamic_ac_timing; scalar_t__ smu_uvd_hs; struct radeon_ps current_rps; struct radeon_ps requested_rps; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  btc_notify_uvd_to_smc (struct radeon_device*,struct radeon_ps*) ; 
 struct evergreen_power_info* evergreen_get_pi (struct radeon_device*) ; 
 int ni_enable_power_containment (struct radeon_device*,struct radeon_ps*,int) ; 
 int ni_enable_smc_cac (struct radeon_device*,struct radeon_ps*,int) ; 
 int ni_power_control_set_level (struct radeon_device*) ; 
 int ni_program_memory_timing_parameters (struct radeon_device*,struct radeon_ps*) ; 
 int ni_restrict_performance_levels_before_switch (struct radeon_device*) ; 
 int /*<<< orphan*/  ni_set_uvd_clock_after_set_eng_clock (struct radeon_device*,struct radeon_ps*,struct radeon_ps*) ; 
 int /*<<< orphan*/  ni_set_uvd_clock_before_set_eng_clock (struct radeon_device*,struct radeon_ps*,struct radeon_ps*) ; 
 int ni_upload_mc_reg_table (struct radeon_device*,struct radeon_ps*) ; 
 int ni_upload_sw_state (struct radeon_device*,struct radeon_ps*) ; 
 int rv770_halt_smc (struct radeon_device*) ; 
 int rv770_resume_smc (struct radeon_device*) ; 
 int rv770_set_sw_state (struct radeon_device*) ; 

int ni_dpm_set_power_state(struct radeon_device *rdev)
{
	struct evergreen_power_info *eg_pi = evergreen_get_pi(rdev);
	struct radeon_ps *new_ps = &eg_pi->requested_rps;
	struct radeon_ps *old_ps = &eg_pi->current_rps;
	int ret;

	ret = ni_restrict_performance_levels_before_switch(rdev);
	if (ret) {
		DRM_ERROR("ni_restrict_performance_levels_before_switch failed\n");
		return ret;
	}
	ni_set_uvd_clock_before_set_eng_clock(rdev, new_ps, old_ps);
	ret = ni_enable_power_containment(rdev, new_ps, false);
	if (ret) {
		DRM_ERROR("ni_enable_power_containment failed\n");
		return ret;
	}
	ret = ni_enable_smc_cac(rdev, new_ps, false);
	if (ret) {
		DRM_ERROR("ni_enable_smc_cac failed\n");
		return ret;
	}
	ret = rv770_halt_smc(rdev);
	if (ret) {
		DRM_ERROR("rv770_halt_smc failed\n");
		return ret;
	}
	if (eg_pi->smu_uvd_hs)
		btc_notify_uvd_to_smc(rdev, new_ps);
	ret = ni_upload_sw_state(rdev, new_ps);
	if (ret) {
		DRM_ERROR("ni_upload_sw_state failed\n");
		return ret;
	}
	if (eg_pi->dynamic_ac_timing) {
		ret = ni_upload_mc_reg_table(rdev, new_ps);
		if (ret) {
			DRM_ERROR("ni_upload_mc_reg_table failed\n");
			return ret;
		}
	}
	ret = ni_program_memory_timing_parameters(rdev, new_ps);
	if (ret) {
		DRM_ERROR("ni_program_memory_timing_parameters failed\n");
		return ret;
	}
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
	ni_set_uvd_clock_after_set_eng_clock(rdev, new_ps, old_ps);
	ret = ni_enable_smc_cac(rdev, new_ps, true);
	if (ret) {
		DRM_ERROR("ni_enable_smc_cac failed\n");
		return ret;
	}
	ret = ni_enable_power_containment(rdev, new_ps, true);
	if (ret) {
		DRM_ERROR("ni_enable_power_containment failed\n");
		return ret;
	}

	/* update tdp */
	ret = ni_power_control_set_level(rdev);
	if (ret) {
		DRM_ERROR("ni_power_control_set_level failed\n");
		return ret;
	}

	return 0;
}
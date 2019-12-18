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
struct evergreen_power_info {scalar_t__ pcie_performance_request; scalar_t__ dynamic_ac_timing; struct radeon_ps current_rps; struct radeon_ps requested_rps; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 struct evergreen_power_info* evergreen_get_pi (struct radeon_device*) ; 
 int /*<<< orphan*/  ni_set_uvd_clock_after_set_eng_clock (struct radeon_device*,struct radeon_ps*,struct radeon_ps*) ; 
 int /*<<< orphan*/  ni_set_uvd_clock_before_set_eng_clock (struct radeon_device*,struct radeon_ps*,struct radeon_ps*) ; 
 int si_disable_ulv (struct radeon_device*) ; 
 int si_enable_power_containment (struct radeon_device*,struct radeon_ps*,int) ; 
 int si_enable_smc_cac (struct radeon_device*,struct radeon_ps*,int) ; 
 int si_halt_smc (struct radeon_device*) ; 
 int /*<<< orphan*/  si_notify_link_speed_change_after_state_change (struct radeon_device*,struct radeon_ps*,struct radeon_ps*) ; 
 int si_power_control_set_level (struct radeon_device*) ; 
 int si_program_memory_timing_parameters (struct radeon_device*,struct radeon_ps*) ; 
 int /*<<< orphan*/  si_request_link_speed_change_before_state_change (struct radeon_device*,struct radeon_ps*,struct radeon_ps*) ; 
 int si_restrict_performance_levels_before_switch (struct radeon_device*) ; 
 int si_resume_smc (struct radeon_device*) ; 
 int /*<<< orphan*/  si_set_pcie_lane_width_in_smc (struct radeon_device*,struct radeon_ps*,struct radeon_ps*) ; 
 int si_set_power_state_conditionally_enable_ulv (struct radeon_device*,struct radeon_ps*) ; 
 int si_set_sw_state (struct radeon_device*) ; 
 int /*<<< orphan*/  si_set_vce_clock (struct radeon_device*,struct radeon_ps*,struct radeon_ps*) ; 
 int si_upload_mc_reg_table (struct radeon_device*,struct radeon_ps*) ; 
 int si_upload_smc_data (struct radeon_device*) ; 
 int si_upload_sw_state (struct radeon_device*,struct radeon_ps*) ; 
 int si_upload_ulv_state (struct radeon_device*) ; 

int si_dpm_set_power_state(struct radeon_device *rdev)
{
	struct evergreen_power_info *eg_pi = evergreen_get_pi(rdev);
	struct radeon_ps *new_ps = &eg_pi->requested_rps;
	struct radeon_ps *old_ps = &eg_pi->current_rps;
	int ret;

	ret = si_disable_ulv(rdev);
	if (ret) {
		DRM_ERROR("si_disable_ulv failed\n");
		return ret;
	}
	ret = si_restrict_performance_levels_before_switch(rdev);
	if (ret) {
		DRM_ERROR("si_restrict_performance_levels_before_switch failed\n");
		return ret;
	}
	if (eg_pi->pcie_performance_request)
		si_request_link_speed_change_before_state_change(rdev, new_ps, old_ps);
	ni_set_uvd_clock_before_set_eng_clock(rdev, new_ps, old_ps);
	ret = si_enable_power_containment(rdev, new_ps, false);
	if (ret) {
		DRM_ERROR("si_enable_power_containment failed\n");
		return ret;
	}
	ret = si_enable_smc_cac(rdev, new_ps, false);
	if (ret) {
		DRM_ERROR("si_enable_smc_cac failed\n");
		return ret;
	}
	ret = si_halt_smc(rdev);
	if (ret) {
		DRM_ERROR("si_halt_smc failed\n");
		return ret;
	}
	ret = si_upload_sw_state(rdev, new_ps);
	if (ret) {
		DRM_ERROR("si_upload_sw_state failed\n");
		return ret;
	}
	ret = si_upload_smc_data(rdev);
	if (ret) {
		DRM_ERROR("si_upload_smc_data failed\n");
		return ret;
	}
	ret = si_upload_ulv_state(rdev);
	if (ret) {
		DRM_ERROR("si_upload_ulv_state failed\n");
		return ret;
	}
	if (eg_pi->dynamic_ac_timing) {
		ret = si_upload_mc_reg_table(rdev, new_ps);
		if (ret) {
			DRM_ERROR("si_upload_mc_reg_table failed\n");
			return ret;
		}
	}
	ret = si_program_memory_timing_parameters(rdev, new_ps);
	if (ret) {
		DRM_ERROR("si_program_memory_timing_parameters failed\n");
		return ret;
	}
	si_set_pcie_lane_width_in_smc(rdev, new_ps, old_ps);

	ret = si_resume_smc(rdev);
	if (ret) {
		DRM_ERROR("si_resume_smc failed\n");
		return ret;
	}
	ret = si_set_sw_state(rdev);
	if (ret) {
		DRM_ERROR("si_set_sw_state failed\n");
		return ret;
	}
	ni_set_uvd_clock_after_set_eng_clock(rdev, new_ps, old_ps);
	si_set_vce_clock(rdev, new_ps, old_ps);
	if (eg_pi->pcie_performance_request)
		si_notify_link_speed_change_after_state_change(rdev, new_ps, old_ps);
	ret = si_set_power_state_conditionally_enable_ulv(rdev, new_ps);
	if (ret) {
		DRM_ERROR("si_set_power_state_conditionally_enable_ulv failed\n");
		return ret;
	}
	ret = si_enable_smc_cac(rdev, new_ps, true);
	if (ret) {
		DRM_ERROR("si_enable_smc_cac failed\n");
		return ret;
	}
	ret = si_enable_power_containment(rdev, new_ps, true);
	if (ret) {
		DRM_ERROR("si_enable_power_containment failed\n");
		return ret;
	}

	ret = si_power_control_set_level(rdev);
	if (ret) {
		DRM_ERROR("si_power_control_set_level failed\n");
		return ret;
	}

	return 0;
}
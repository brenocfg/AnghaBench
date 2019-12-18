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
struct amdgpu_ps {int dummy; } ;
struct evergreen_power_info {scalar_t__ pcie_performance_request; scalar_t__ dynamic_ac_timing; struct amdgpu_ps current_rps; struct amdgpu_ps requested_rps; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 struct evergreen_power_info* evergreen_get_pi (struct amdgpu_device*) ; 
 int /*<<< orphan*/  ni_set_uvd_clock_after_set_eng_clock (struct amdgpu_device*,struct amdgpu_ps*,struct amdgpu_ps*) ; 
 int /*<<< orphan*/  ni_set_uvd_clock_before_set_eng_clock (struct amdgpu_device*,struct amdgpu_ps*,struct amdgpu_ps*) ; 
 int si_disable_ulv (struct amdgpu_device*) ; 
 int si_enable_power_containment (struct amdgpu_device*,struct amdgpu_ps*,int) ; 
 int si_enable_smc_cac (struct amdgpu_device*,struct amdgpu_ps*,int) ; 
 int si_halt_smc (struct amdgpu_device*) ; 
 int /*<<< orphan*/  si_notify_link_speed_change_after_state_change (struct amdgpu_device*,struct amdgpu_ps*,struct amdgpu_ps*) ; 
 int si_power_control_set_level (struct amdgpu_device*) ; 
 int si_program_memory_timing_parameters (struct amdgpu_device*,struct amdgpu_ps*) ; 
 int /*<<< orphan*/  si_request_link_speed_change_before_state_change (struct amdgpu_device*,struct amdgpu_ps*,struct amdgpu_ps*) ; 
 int si_restrict_performance_levels_before_switch (struct amdgpu_device*) ; 
 int si_resume_smc (struct amdgpu_device*) ; 
 int /*<<< orphan*/  si_set_pcie_lane_width_in_smc (struct amdgpu_device*,struct amdgpu_ps*,struct amdgpu_ps*) ; 
 int si_set_power_state_conditionally_enable_ulv (struct amdgpu_device*,struct amdgpu_ps*) ; 
 int si_set_sw_state (struct amdgpu_device*) ; 
 int si_upload_mc_reg_table (struct amdgpu_device*,struct amdgpu_ps*) ; 
 int si_upload_smc_data (struct amdgpu_device*) ; 
 int si_upload_sw_state (struct amdgpu_device*,struct amdgpu_ps*) ; 
 int si_upload_ulv_state (struct amdgpu_device*) ; 

__attribute__((used)) static int si_dpm_set_power_state(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;
	struct evergreen_power_info *eg_pi = evergreen_get_pi(adev);
	struct amdgpu_ps *new_ps = &eg_pi->requested_rps;
	struct amdgpu_ps *old_ps = &eg_pi->current_rps;
	int ret;

	ret = si_disable_ulv(adev);
	if (ret) {
		DRM_ERROR("si_disable_ulv failed\n");
		return ret;
	}
	ret = si_restrict_performance_levels_before_switch(adev);
	if (ret) {
		DRM_ERROR("si_restrict_performance_levels_before_switch failed\n");
		return ret;
	}
	if (eg_pi->pcie_performance_request)
		si_request_link_speed_change_before_state_change(adev, new_ps, old_ps);
	ni_set_uvd_clock_before_set_eng_clock(adev, new_ps, old_ps);
	ret = si_enable_power_containment(adev, new_ps, false);
	if (ret) {
		DRM_ERROR("si_enable_power_containment failed\n");
		return ret;
	}
	ret = si_enable_smc_cac(adev, new_ps, false);
	if (ret) {
		DRM_ERROR("si_enable_smc_cac failed\n");
		return ret;
	}
	ret = si_halt_smc(adev);
	if (ret) {
		DRM_ERROR("si_halt_smc failed\n");
		return ret;
	}
	ret = si_upload_sw_state(adev, new_ps);
	if (ret) {
		DRM_ERROR("si_upload_sw_state failed\n");
		return ret;
	}
	ret = si_upload_smc_data(adev);
	if (ret) {
		DRM_ERROR("si_upload_smc_data failed\n");
		return ret;
	}
	ret = si_upload_ulv_state(adev);
	if (ret) {
		DRM_ERROR("si_upload_ulv_state failed\n");
		return ret;
	}
	if (eg_pi->dynamic_ac_timing) {
		ret = si_upload_mc_reg_table(adev, new_ps);
		if (ret) {
			DRM_ERROR("si_upload_mc_reg_table failed\n");
			return ret;
		}
	}
	ret = si_program_memory_timing_parameters(adev, new_ps);
	if (ret) {
		DRM_ERROR("si_program_memory_timing_parameters failed\n");
		return ret;
	}
	si_set_pcie_lane_width_in_smc(adev, new_ps, old_ps);

	ret = si_resume_smc(adev);
	if (ret) {
		DRM_ERROR("si_resume_smc failed\n");
		return ret;
	}
	ret = si_set_sw_state(adev);
	if (ret) {
		DRM_ERROR("si_set_sw_state failed\n");
		return ret;
	}
	ni_set_uvd_clock_after_set_eng_clock(adev, new_ps, old_ps);
	if (eg_pi->pcie_performance_request)
		si_notify_link_speed_change_after_state_change(adev, new_ps, old_ps);
	ret = si_set_power_state_conditionally_enable_ulv(adev, new_ps);
	if (ret) {
		DRM_ERROR("si_set_power_state_conditionally_enable_ulv failed\n");
		return ret;
	}
	ret = si_enable_smc_cac(adev, new_ps, true);
	if (ret) {
		DRM_ERROR("si_enable_smc_cac failed\n");
		return ret;
	}
	ret = si_enable_power_containment(adev, new_ps, true);
	if (ret) {
		DRM_ERROR("si_enable_power_containment failed\n");
		return ret;
	}

	ret = si_power_control_set_level(adev);
	if (ret) {
		DRM_ERROR("si_power_control_set_level failed\n");
		return ret;
	}

	return 0;
}
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
struct ci_power_info {scalar_t__ pcie_performance_request; scalar_t__ caps_dynamic_ac_timing; struct radeon_ps current_rps; struct radeon_ps requested_rps; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  ci_find_dpm_states_clocks_in_dpm_table (struct radeon_device*,struct radeon_ps*) ; 
 int ci_freeze_sclk_mclk_dpm (struct radeon_device*) ; 
 int ci_generate_dpm_level_enable_mask (struct radeon_device*,struct radeon_ps*) ; 
 struct ci_power_info* ci_get_pi (struct radeon_device*) ; 
 int /*<<< orphan*/  ci_notify_link_speed_change_after_state_change (struct radeon_device*,struct radeon_ps*,struct radeon_ps*) ; 
 int ci_populate_and_upload_sclk_mclk_dpm_levels (struct radeon_device*,struct radeon_ps*) ; 
 int ci_program_memory_timing_parameters (struct radeon_device*) ; 
 int /*<<< orphan*/  ci_request_link_speed_change_before_state_change (struct radeon_device*,struct radeon_ps*,struct radeon_ps*) ; 
 int ci_unfreeze_sclk_mclk_dpm (struct radeon_device*) ; 
 int ci_update_and_upload_mc_reg_table (struct radeon_device*) ; 
 int ci_update_sclk_t (struct radeon_device*) ; 
 int ci_update_vce_dpm (struct radeon_device*,struct radeon_ps*,struct radeon_ps*) ; 
 int ci_upload_dpm_level_enable_mask (struct radeon_device*) ; 

int ci_dpm_set_power_state(struct radeon_device *rdev)
{
	struct ci_power_info *pi = ci_get_pi(rdev);
	struct radeon_ps *new_ps = &pi->requested_rps;
	struct radeon_ps *old_ps = &pi->current_rps;
	int ret;

	ci_find_dpm_states_clocks_in_dpm_table(rdev, new_ps);
	if (pi->pcie_performance_request)
		ci_request_link_speed_change_before_state_change(rdev, new_ps, old_ps);
	ret = ci_freeze_sclk_mclk_dpm(rdev);
	if (ret) {
		DRM_ERROR("ci_freeze_sclk_mclk_dpm failed\n");
		return ret;
	}
	ret = ci_populate_and_upload_sclk_mclk_dpm_levels(rdev, new_ps);
	if (ret) {
		DRM_ERROR("ci_populate_and_upload_sclk_mclk_dpm_levels failed\n");
		return ret;
	}
	ret = ci_generate_dpm_level_enable_mask(rdev, new_ps);
	if (ret) {
		DRM_ERROR("ci_generate_dpm_level_enable_mask failed\n");
		return ret;
	}

	ret = ci_update_vce_dpm(rdev, new_ps, old_ps);
	if (ret) {
		DRM_ERROR("ci_update_vce_dpm failed\n");
		return ret;
	}

	ret = ci_update_sclk_t(rdev);
	if (ret) {
		DRM_ERROR("ci_update_sclk_t failed\n");
		return ret;
	}
	if (pi->caps_dynamic_ac_timing) {
		ret = ci_update_and_upload_mc_reg_table(rdev);
		if (ret) {
			DRM_ERROR("ci_update_and_upload_mc_reg_table failed\n");
			return ret;
		}
	}
	ret = ci_program_memory_timing_parameters(rdev);
	if (ret) {
		DRM_ERROR("ci_program_memory_timing_parameters failed\n");
		return ret;
	}
	ret = ci_unfreeze_sclk_mclk_dpm(rdev);
	if (ret) {
		DRM_ERROR("ci_unfreeze_sclk_mclk_dpm failed\n");
		return ret;
	}
	ret = ci_upload_dpm_level_enable_mask(rdev);
	if (ret) {
		DRM_ERROR("ci_upload_dpm_level_enable_mask failed\n");
		return ret;
	}
	if (pi->pcie_performance_request)
		ci_notify_link_speed_change_after_state_change(rdev, new_ps, old_ps);

	return 0;
}
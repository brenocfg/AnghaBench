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
struct TYPE_3__ {int /*<<< orphan*/  boot_ps; } ;
struct TYPE_4__ {TYPE_1__ dpm; } ;
struct radeon_device {TYPE_2__ pm; } ;
struct kv_power_info {scalar_t__ enable_auto_thermal_throttling; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  kv_calculate_dfs_bypass_settings (struct radeon_device*) ; 
 int kv_enable_auto_thermal_throttling (struct radeon_device*) ; 
 int kv_enable_didt (struct radeon_device*,int) ; 
 int kv_enable_dpm_voltage_scaling (struct radeon_device*) ; 
 int kv_enable_smc_cac (struct radeon_device*,int) ; 
 int kv_enable_ulv (struct radeon_device*,int) ; 
 struct kv_power_info* kv_get_pi (struct radeon_device*) ; 
 int /*<<< orphan*/  kv_init_fps_limits (struct radeon_device*) ; 
 int /*<<< orphan*/  kv_init_graphics_levels (struct radeon_device*) ; 
 int /*<<< orphan*/  kv_initialize_hardware_cac_manager (struct radeon_device*) ; 
 int kv_populate_acp_table (struct radeon_device*) ; 
 int kv_populate_samu_table (struct radeon_device*) ; 
 int kv_populate_uvd_table (struct radeon_device*) ; 
 int kv_populate_vce_table (struct radeon_device*) ; 
 int kv_process_firmware_header (struct radeon_device*) ; 
 int kv_program_bootup_state (struct radeon_device*) ; 
 int /*<<< orphan*/  kv_program_vc (struct radeon_device*) ; 
 int /*<<< orphan*/  kv_reset_acp_boot_level (struct radeon_device*) ; 
 int kv_set_dpm_boot_state (struct radeon_device*) ; 
 int kv_set_dpm_interval (struct radeon_device*) ; 
 int kv_smc_bapm_enable (struct radeon_device*,int) ; 
 int /*<<< orphan*/  kv_start_am (struct radeon_device*) ; 
 int /*<<< orphan*/  kv_start_dpm (struct radeon_device*) ; 
 int /*<<< orphan*/  kv_update_current_ps (struct radeon_device*,int /*<<< orphan*/ ) ; 
 int kv_upload_dpm_settings (struct radeon_device*) ; 

int kv_dpm_enable(struct radeon_device *rdev)
{
	struct kv_power_info *pi = kv_get_pi(rdev);
	int ret;

	ret = kv_process_firmware_header(rdev);
	if (ret) {
		DRM_ERROR("kv_process_firmware_header failed\n");
		return ret;
	}
	kv_init_fps_limits(rdev);
	kv_init_graphics_levels(rdev);
	ret = kv_program_bootup_state(rdev);
	if (ret) {
		DRM_ERROR("kv_program_bootup_state failed\n");
		return ret;
	}
	kv_calculate_dfs_bypass_settings(rdev);
	ret = kv_upload_dpm_settings(rdev);
	if (ret) {
		DRM_ERROR("kv_upload_dpm_settings failed\n");
		return ret;
	}
	ret = kv_populate_uvd_table(rdev);
	if (ret) {
		DRM_ERROR("kv_populate_uvd_table failed\n");
		return ret;
	}
	ret = kv_populate_vce_table(rdev);
	if (ret) {
		DRM_ERROR("kv_populate_vce_table failed\n");
		return ret;
	}
	ret = kv_populate_samu_table(rdev);
	if (ret) {
		DRM_ERROR("kv_populate_samu_table failed\n");
		return ret;
	}
	ret = kv_populate_acp_table(rdev);
	if (ret) {
		DRM_ERROR("kv_populate_acp_table failed\n");
		return ret;
	}
	kv_program_vc(rdev);
#if 0
	kv_initialize_hardware_cac_manager(rdev);
#endif
	kv_start_am(rdev);
	if (pi->enable_auto_thermal_throttling) {
		ret = kv_enable_auto_thermal_throttling(rdev);
		if (ret) {
			DRM_ERROR("kv_enable_auto_thermal_throttling failed\n");
			return ret;
		}
	}
	ret = kv_enable_dpm_voltage_scaling(rdev);
	if (ret) {
		DRM_ERROR("kv_enable_dpm_voltage_scaling failed\n");
		return ret;
	}
	ret = kv_set_dpm_interval(rdev);
	if (ret) {
		DRM_ERROR("kv_set_dpm_interval failed\n");
		return ret;
	}
	ret = kv_set_dpm_boot_state(rdev);
	if (ret) {
		DRM_ERROR("kv_set_dpm_boot_state failed\n");
		return ret;
	}
	ret = kv_enable_ulv(rdev, true);
	if (ret) {
		DRM_ERROR("kv_enable_ulv failed\n");
		return ret;
	}
	kv_start_dpm(rdev);
	ret = kv_enable_didt(rdev, true);
	if (ret) {
		DRM_ERROR("kv_enable_didt failed\n");
		return ret;
	}
	ret = kv_enable_smc_cac(rdev, true);
	if (ret) {
		DRM_ERROR("kv_enable_smc_cac failed\n");
		return ret;
	}

	kv_reset_acp_boot_level(rdev);

	ret = kv_smc_bapm_enable(rdev, false);
	if (ret) {
		DRM_ERROR("kv_smc_bapm_enable failed\n");
		return ret;
	}

	kv_update_current_ps(rdev, rdev->pm.dpm.boot_ps);

	return ret;
}
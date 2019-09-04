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
struct amdgpu_ps {int dummy; } ;
struct kv_power_info {scalar_t__ enable_dpm; scalar_t__ bapm_enable; struct amdgpu_ps current_rps; struct amdgpu_ps requested_rps; } ;
struct TYPE_2__ {int /*<<< orphan*/  ac_power; } ;
struct amdgpu_device {scalar_t__ asic_type; TYPE_1__ pm; } ;

/* Variables and functions */
 scalar_t__ CHIP_KABINI ; 
 scalar_t__ CHIP_MULLINS ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int amdgpu_kv_smc_bapm_enable (struct amdgpu_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kv_calculate_dpm_settings (struct amdgpu_device*) ; 
 int kv_calculate_ds_divider (struct amdgpu_device*) ; 
 int /*<<< orphan*/  kv_calculate_nbps_level_settings (struct amdgpu_device*) ; 
 int /*<<< orphan*/  kv_enable_nb_dpm (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  kv_enable_new_levels (struct amdgpu_device*) ; 
 int /*<<< orphan*/  kv_force_lowest_valid (struct amdgpu_device*) ; 
 int /*<<< orphan*/  kv_freeze_sclk_dpm (struct amdgpu_device*,int) ; 
 struct kv_power_info* kv_get_pi (struct amdgpu_device*) ; 
 int /*<<< orphan*/  kv_program_nbps_index_settings (struct amdgpu_device*,struct amdgpu_ps*) ; 
 int /*<<< orphan*/  kv_set_enabled_levels (struct amdgpu_device*) ; 
 int /*<<< orphan*/  kv_set_valid_clock_range (struct amdgpu_device*,struct amdgpu_ps*) ; 
 int /*<<< orphan*/  kv_unforce_levels (struct amdgpu_device*) ; 
 int /*<<< orphan*/  kv_update_acp_boot_level (struct amdgpu_device*) ; 
 int /*<<< orphan*/  kv_update_dfs_bypass_settings (struct amdgpu_device*,struct amdgpu_ps*) ; 
 int /*<<< orphan*/  kv_update_sclk_t (struct amdgpu_device*) ; 
 int kv_update_vce_dpm (struct amdgpu_device*,struct amdgpu_ps*,struct amdgpu_ps*) ; 
 int /*<<< orphan*/  kv_upload_dpm_settings (struct amdgpu_device*) ; 

__attribute__((used)) static int kv_dpm_set_power_state(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;
	struct kv_power_info *pi = kv_get_pi(adev);
	struct amdgpu_ps *new_ps = &pi->requested_rps;
	struct amdgpu_ps *old_ps = &pi->current_rps;
	int ret;

	if (pi->bapm_enable) {
		ret = amdgpu_kv_smc_bapm_enable(adev, adev->pm.ac_power);
		if (ret) {
			DRM_ERROR("amdgpu_kv_smc_bapm_enable failed\n");
			return ret;
		}
	}

	if (adev->asic_type == CHIP_KABINI || adev->asic_type == CHIP_MULLINS) {
		if (pi->enable_dpm) {
			kv_set_valid_clock_range(adev, new_ps);
			kv_update_dfs_bypass_settings(adev, new_ps);
			ret = kv_calculate_ds_divider(adev);
			if (ret) {
				DRM_ERROR("kv_calculate_ds_divider failed\n");
				return ret;
			}
			kv_calculate_nbps_level_settings(adev);
			kv_calculate_dpm_settings(adev);
			kv_force_lowest_valid(adev);
			kv_enable_new_levels(adev);
			kv_upload_dpm_settings(adev);
			kv_program_nbps_index_settings(adev, new_ps);
			kv_unforce_levels(adev);
			kv_set_enabled_levels(adev);
			kv_force_lowest_valid(adev);
			kv_unforce_levels(adev);

			ret = kv_update_vce_dpm(adev, new_ps, old_ps);
			if (ret) {
				DRM_ERROR("kv_update_vce_dpm failed\n");
				return ret;
			}
			kv_update_sclk_t(adev);
			if (adev->asic_type == CHIP_MULLINS)
				kv_enable_nb_dpm(adev, true);
		}
	} else {
		if (pi->enable_dpm) {
			kv_set_valid_clock_range(adev, new_ps);
			kv_update_dfs_bypass_settings(adev, new_ps);
			ret = kv_calculate_ds_divider(adev);
			if (ret) {
				DRM_ERROR("kv_calculate_ds_divider failed\n");
				return ret;
			}
			kv_calculate_nbps_level_settings(adev);
			kv_calculate_dpm_settings(adev);
			kv_freeze_sclk_dpm(adev, true);
			kv_upload_dpm_settings(adev);
			kv_program_nbps_index_settings(adev, new_ps);
			kv_freeze_sclk_dpm(adev, false);
			kv_set_enabled_levels(adev);
			ret = kv_update_vce_dpm(adev, new_ps, old_ps);
			if (ret) {
				DRM_ERROR("kv_update_vce_dpm failed\n");
				return ret;
			}
			kv_update_acp_boot_level(adev);
			kv_update_sclk_t(adev);
			kv_enable_nb_dpm(adev, true);
		}
	}

	return 0;
}
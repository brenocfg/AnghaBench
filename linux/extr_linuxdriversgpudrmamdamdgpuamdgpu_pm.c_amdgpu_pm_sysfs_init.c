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
struct TYPE_2__ {int sysfs_initialized; scalar_t__ dpm_enabled; int /*<<< orphan*/  int_hwmon_dev; } ;
struct amdgpu_device {TYPE_1__ pm; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_NAME ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int amdgpu_debugfs_pm_init (struct amdgpu_device*) ; 
 int /*<<< orphan*/  dev_attr_gpu_busy_percent ; 
 int /*<<< orphan*/  dev_attr_power_dpm_force_performance_level ; 
 int /*<<< orphan*/  dev_attr_power_dpm_state ; 
 int /*<<< orphan*/  dev_attr_pp_cur_state ; 
 int /*<<< orphan*/  dev_attr_pp_dpm_mclk ; 
 int /*<<< orphan*/  dev_attr_pp_dpm_pcie ; 
 int /*<<< orphan*/  dev_attr_pp_dpm_sclk ; 
 int /*<<< orphan*/  dev_attr_pp_force_state ; 
 int /*<<< orphan*/  dev_attr_pp_mclk_od ; 
 int /*<<< orphan*/  dev_attr_pp_num_states ; 
 int /*<<< orphan*/  dev_attr_pp_od_clk_voltage ; 
 int /*<<< orphan*/  dev_attr_pp_power_profile_mode ; 
 int /*<<< orphan*/  dev_attr_pp_sclk_od ; 
 int /*<<< orphan*/  dev_attr_pp_table ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int device_create_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hwmon_device_register_with_groups (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct amdgpu_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwmon_groups ; 

int amdgpu_pm_sysfs_init(struct amdgpu_device *adev)
{
	int ret;

	if (adev->pm.sysfs_initialized)
		return 0;

	if (adev->pm.dpm_enabled == 0)
		return 0;

	adev->pm.int_hwmon_dev = hwmon_device_register_with_groups(adev->dev,
								   DRIVER_NAME, adev,
								   hwmon_groups);
	if (IS_ERR(adev->pm.int_hwmon_dev)) {
		ret = PTR_ERR(adev->pm.int_hwmon_dev);
		dev_err(adev->dev,
			"Unable to register hwmon device: %d\n", ret);
		return ret;
	}

	ret = device_create_file(adev->dev, &dev_attr_power_dpm_state);
	if (ret) {
		DRM_ERROR("failed to create device file for dpm state\n");
		return ret;
	}
	ret = device_create_file(adev->dev, &dev_attr_power_dpm_force_performance_level);
	if (ret) {
		DRM_ERROR("failed to create device file for dpm state\n");
		return ret;
	}


	ret = device_create_file(adev->dev, &dev_attr_pp_num_states);
	if (ret) {
		DRM_ERROR("failed to create device file pp_num_states\n");
		return ret;
	}
	ret = device_create_file(adev->dev, &dev_attr_pp_cur_state);
	if (ret) {
		DRM_ERROR("failed to create device file pp_cur_state\n");
		return ret;
	}
	ret = device_create_file(adev->dev, &dev_attr_pp_force_state);
	if (ret) {
		DRM_ERROR("failed to create device file pp_force_state\n");
		return ret;
	}
	ret = device_create_file(adev->dev, &dev_attr_pp_table);
	if (ret) {
		DRM_ERROR("failed to create device file pp_table\n");
		return ret;
	}

	ret = device_create_file(adev->dev, &dev_attr_pp_dpm_sclk);
	if (ret) {
		DRM_ERROR("failed to create device file pp_dpm_sclk\n");
		return ret;
	}
	ret = device_create_file(adev->dev, &dev_attr_pp_dpm_mclk);
	if (ret) {
		DRM_ERROR("failed to create device file pp_dpm_mclk\n");
		return ret;
	}
	ret = device_create_file(adev->dev, &dev_attr_pp_dpm_pcie);
	if (ret) {
		DRM_ERROR("failed to create device file pp_dpm_pcie\n");
		return ret;
	}
	ret = device_create_file(adev->dev, &dev_attr_pp_sclk_od);
	if (ret) {
		DRM_ERROR("failed to create device file pp_sclk_od\n");
		return ret;
	}
	ret = device_create_file(adev->dev, &dev_attr_pp_mclk_od);
	if (ret) {
		DRM_ERROR("failed to create device file pp_mclk_od\n");
		return ret;
	}
	ret = device_create_file(adev->dev,
			&dev_attr_pp_power_profile_mode);
	if (ret) {
		DRM_ERROR("failed to create device file	"
				"pp_power_profile_mode\n");
		return ret;
	}
	ret = device_create_file(adev->dev,
			&dev_attr_pp_od_clk_voltage);
	if (ret) {
		DRM_ERROR("failed to create device file	"
				"pp_od_clk_voltage\n");
		return ret;
	}
	ret = device_create_file(adev->dev,
			&dev_attr_gpu_busy_percent);
	if (ret) {
		DRM_ERROR("failed to create device file	"
				"gpu_busy_level\n");
		return ret;
	}
	ret = amdgpu_debugfs_pm_init(adev);
	if (ret) {
		DRM_ERROR("Failed to register debugfs file for dpm!\n");
		return ret;
	}

	adev->pm.sysfs_initialized = true;

	return 0;
}
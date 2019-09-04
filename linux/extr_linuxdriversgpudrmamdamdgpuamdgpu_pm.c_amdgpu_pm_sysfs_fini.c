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
struct TYPE_2__ {scalar_t__ dpm_enabled; scalar_t__ int_hwmon_dev; } ;
struct amdgpu_device {int /*<<< orphan*/  dev; TYPE_1__ pm; } ;

/* Variables and functions */
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
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hwmon_device_unregister (scalar_t__) ; 

void amdgpu_pm_sysfs_fini(struct amdgpu_device *adev)
{
	if (adev->pm.dpm_enabled == 0)
		return;

	if (adev->pm.int_hwmon_dev)
		hwmon_device_unregister(adev->pm.int_hwmon_dev);
	device_remove_file(adev->dev, &dev_attr_power_dpm_state);
	device_remove_file(adev->dev, &dev_attr_power_dpm_force_performance_level);

	device_remove_file(adev->dev, &dev_attr_pp_num_states);
	device_remove_file(adev->dev, &dev_attr_pp_cur_state);
	device_remove_file(adev->dev, &dev_attr_pp_force_state);
	device_remove_file(adev->dev, &dev_attr_pp_table);

	device_remove_file(adev->dev, &dev_attr_pp_dpm_sclk);
	device_remove_file(adev->dev, &dev_attr_pp_dpm_mclk);
	device_remove_file(adev->dev, &dev_attr_pp_dpm_pcie);
	device_remove_file(adev->dev, &dev_attr_pp_sclk_od);
	device_remove_file(adev->dev, &dev_attr_pp_mclk_od);
	device_remove_file(adev->dev,
			&dev_attr_pp_power_profile_mode);
	device_remove_file(adev->dev,
			&dev_attr_pp_od_clk_voltage);
	device_remove_file(adev->dev, &dev_attr_gpu_busy_percent);
}
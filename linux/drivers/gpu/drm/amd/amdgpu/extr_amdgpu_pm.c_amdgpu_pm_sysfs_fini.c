#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pp_hwmgr {scalar_t__ od_enabled; } ;
struct TYPE_6__ {scalar_t__ od_enabled; } ;
struct TYPE_5__ {scalar_t__ dpm_enabled; scalar_t__ int_hwmon_dev; } ;
struct TYPE_4__ {struct pp_hwmgr* pp_handle; } ;
struct amdgpu_device {scalar_t__ asic_type; int flags; int /*<<< orphan*/  dev; scalar_t__ unique_id; TYPE_3__ smu; TYPE_2__ pm; TYPE_1__ powerplay; } ;

/* Variables and functions */
 int AMD_IS_APU ; 
 scalar_t__ CHIP_ARCTURUS ; 
 scalar_t__ CHIP_VEGA10 ; 
 scalar_t__ CHIP_VEGA20 ; 
 int /*<<< orphan*/  dev_attr_gpu_busy_percent ; 
 int /*<<< orphan*/  dev_attr_mem_busy_percent ; 
 int /*<<< orphan*/  dev_attr_pcie_bw ; 
 int /*<<< orphan*/  dev_attr_power_dpm_force_performance_level ; 
 int /*<<< orphan*/  dev_attr_power_dpm_state ; 
 int /*<<< orphan*/  dev_attr_pp_cur_state ; 
 int /*<<< orphan*/  dev_attr_pp_dpm_dcefclk ; 
 int /*<<< orphan*/  dev_attr_pp_dpm_fclk ; 
 int /*<<< orphan*/  dev_attr_pp_dpm_mclk ; 
 int /*<<< orphan*/  dev_attr_pp_dpm_pcie ; 
 int /*<<< orphan*/  dev_attr_pp_dpm_sclk ; 
 int /*<<< orphan*/  dev_attr_pp_dpm_socclk ; 
 int /*<<< orphan*/  dev_attr_pp_features ; 
 int /*<<< orphan*/  dev_attr_pp_force_state ; 
 int /*<<< orphan*/  dev_attr_pp_mclk_od ; 
 int /*<<< orphan*/  dev_attr_pp_num_states ; 
 int /*<<< orphan*/  dev_attr_pp_od_clk_voltage ; 
 int /*<<< orphan*/  dev_attr_pp_power_profile_mode ; 
 int /*<<< orphan*/  dev_attr_pp_sclk_od ; 
 int /*<<< orphan*/  dev_attr_pp_table ; 
 int /*<<< orphan*/  dev_attr_unique_id ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hwmon_device_unregister (scalar_t__) ; 
 scalar_t__ is_support_sw_smu (struct amdgpu_device*) ; 

void amdgpu_pm_sysfs_fini(struct amdgpu_device *adev)
{
	struct pp_hwmgr *hwmgr = adev->powerplay.pp_handle;

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
	if (adev->asic_type >= CHIP_VEGA10) {
		device_remove_file(adev->dev, &dev_attr_pp_dpm_socclk);
		if (adev->asic_type != CHIP_ARCTURUS)
			device_remove_file(adev->dev, &dev_attr_pp_dpm_dcefclk);
	}
	if (adev->asic_type != CHIP_ARCTURUS)
		device_remove_file(adev->dev, &dev_attr_pp_dpm_pcie);
	if (adev->asic_type >= CHIP_VEGA20)
		device_remove_file(adev->dev, &dev_attr_pp_dpm_fclk);
	device_remove_file(adev->dev, &dev_attr_pp_sclk_od);
	device_remove_file(adev->dev, &dev_attr_pp_mclk_od);
	device_remove_file(adev->dev,
			&dev_attr_pp_power_profile_mode);
	if ((is_support_sw_smu(adev) && adev->smu.od_enabled) ||
	    (!is_support_sw_smu(adev) && hwmgr->od_enabled))
		device_remove_file(adev->dev,
				&dev_attr_pp_od_clk_voltage);
	device_remove_file(adev->dev, &dev_attr_gpu_busy_percent);
	if (!(adev->flags & AMD_IS_APU) &&
	     (adev->asic_type != CHIP_VEGA10))
		device_remove_file(adev->dev, &dev_attr_mem_busy_percent);
	if (!(adev->flags & AMD_IS_APU))
		device_remove_file(adev->dev, &dev_attr_pcie_bw);
	if (adev->unique_id)
		device_remove_file(adev->dev, &dev_attr_unique_id);
	if ((adev->asic_type >= CHIP_VEGA10) &&
	    !(adev->flags & AMD_IS_APU))
		device_remove_file(adev->dev, &dev_attr_pp_features);
}
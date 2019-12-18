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
struct smu_context {int /*<<< orphan*/  pm_enabled; } ;
struct TYPE_4__ {int dpm_enabled; } ;
struct TYPE_3__ {scalar_t__ load_type; } ;
struct amdgpu_device {scalar_t__ asic_type; int flags; TYPE_2__ pm; struct smu_context smu; TYPE_1__ firmware; } ;

/* Variables and functions */
 scalar_t__ AMDGPU_FW_LOAD_PSP ; 
 int AMD_IS_APU ; 
 scalar_t__ CHIP_NAVI10 ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int smu_alloc_memory_pool (struct smu_context*) ; 
 int smu_check_fw_status (struct smu_context*) ; 
 int smu_feature_init_dpm (struct smu_context*) ; 
 int smu_load_microcode (struct smu_context*) ; 
 int smu_notify_memory_pool_location (struct smu_context*) ; 
 int /*<<< orphan*/  smu_powergate_sdma (struct smu_context*,int) ; 
 int /*<<< orphan*/  smu_powergate_vcn (struct smu_context*,int) ; 
 int smu_smc_table_hw_init (struct smu_context*,int) ; 
 int smu_start_thermal_control (struct smu_context*) ; 

__attribute__((used)) static int smu_hw_init(void *handle)
{
	int ret;
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;
	struct smu_context *smu = &adev->smu;

	if (adev->firmware.load_type != AMDGPU_FW_LOAD_PSP) {
		if (adev->asic_type < CHIP_NAVI10) {
			ret = smu_load_microcode(smu);
			if (ret)
				return ret;
		}
	}

	ret = smu_check_fw_status(smu);
	if (ret) {
		pr_err("SMC firmware status is not correct\n");
		return ret;
	}

	if (adev->flags & AMD_IS_APU) {
		smu_powergate_sdma(&adev->smu, false);
		smu_powergate_vcn(&adev->smu, false);
	}

	if (!smu->pm_enabled)
		return 0;

	ret = smu_feature_init_dpm(smu);
	if (ret)
		goto failed;

	ret = smu_smc_table_hw_init(smu, true);
	if (ret)
		goto failed;

	ret = smu_alloc_memory_pool(smu);
	if (ret)
		goto failed;

	/*
	 * Use msg SetSystemVirtualDramAddr and DramLogSetDramAddr can notify
	 * pool location.
	 */
	ret = smu_notify_memory_pool_location(smu);
	if (ret)
		goto failed;

	ret = smu_start_thermal_control(smu);
	if (ret)
		goto failed;

	if (!smu->pm_enabled)
		adev->pm.dpm_enabled = false;
	else
		adev->pm.dpm_enabled = true;	/* TODO: will set dpm_enabled flag while VCN and DAL DPM is workable */

	pr_info("SMU is initialized successfully!\n");

	return 0;

failed:
	return ret;
}
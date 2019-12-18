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
struct TYPE_2__ {int /*<<< orphan*/  load_type; } ;
struct amdgpu_device {TYPE_1__ firmware; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_device_check_block_size (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_device_check_smu_prv_buffer_size (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_device_check_vm_size (struct amdgpu_device*) ; 
 int amdgpu_device_get_job_timeout_settings (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_fw_load_type ; 
 int amdgpu_gart_size ; 
 int amdgpu_gtt_size ; 
 int amdgpu_sched_jobs ; 
 int /*<<< orphan*/  amdgpu_ucode_get_load_type (struct amdgpu_device*,int /*<<< orphan*/ ) ; 
 int amdgpu_vm_fragment_size ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  is_power_of_2 (int) ; 
 int roundup_pow_of_two (int) ; 

__attribute__((used)) static int amdgpu_device_check_arguments(struct amdgpu_device *adev)
{
	int ret = 0;

	if (amdgpu_sched_jobs < 4) {
		dev_warn(adev->dev, "sched jobs (%d) must be at least 4\n",
			 amdgpu_sched_jobs);
		amdgpu_sched_jobs = 4;
	} else if (!is_power_of_2(amdgpu_sched_jobs)){
		dev_warn(adev->dev, "sched jobs (%d) must be a power of 2\n",
			 amdgpu_sched_jobs);
		amdgpu_sched_jobs = roundup_pow_of_two(amdgpu_sched_jobs);
	}

	if (amdgpu_gart_size != -1 && amdgpu_gart_size < 32) {
		/* gart size must be greater or equal to 32M */
		dev_warn(adev->dev, "gart size (%d) too small\n",
			 amdgpu_gart_size);
		amdgpu_gart_size = -1;
	}

	if (amdgpu_gtt_size != -1 && amdgpu_gtt_size < 32) {
		/* gtt size must be greater or equal to 32M */
		dev_warn(adev->dev, "gtt size (%d) too small\n",
				 amdgpu_gtt_size);
		amdgpu_gtt_size = -1;
	}

	/* valid range is between 4 and 9 inclusive */
	if (amdgpu_vm_fragment_size != -1 &&
	    (amdgpu_vm_fragment_size > 9 || amdgpu_vm_fragment_size < 4)) {
		dev_warn(adev->dev, "valid range is between 4 and 9\n");
		amdgpu_vm_fragment_size = -1;
	}

	amdgpu_device_check_smu_prv_buffer_size(adev);

	amdgpu_device_check_vm_size(adev);

	amdgpu_device_check_block_size(adev);

	ret = amdgpu_device_get_job_timeout_settings(adev);
	if (ret) {
		dev_err(adev->dev, "invalid lockup_timeout parameter syntax\n");
		return ret;
	}

	adev->firmware.load_type = amdgpu_ucode_get_load_type(adev, amdgpu_fw_load_type);

	return ret;
}
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
struct TYPE_2__ {int dpm_enabled; int /*<<< orphan*/  mutex; } ;
struct amdgpu_device {TYPE_1__ pm; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_pm_compute_clocks (struct amdgpu_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int si_dpm_enable (struct amdgpu_device*) ; 
 int /*<<< orphan*/  si_dpm_setup_asic (struct amdgpu_device*) ; 

__attribute__((used)) static int si_dpm_resume(void *handle)
{
	int ret;
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	if (adev->pm.dpm_enabled) {
		/* asic init will reset to the boot state */
		mutex_lock(&adev->pm.mutex);
		si_dpm_setup_asic(adev);
		ret = si_dpm_enable(adev);
		if (ret)
			adev->pm.dpm_enabled = false;
		else
			adev->pm.dpm_enabled = true;
		mutex_unlock(&adev->pm.mutex);
		if (adev->pm.dpm_enabled)
			amdgpu_pm_compute_clocks(adev);
	}
	return 0;
}
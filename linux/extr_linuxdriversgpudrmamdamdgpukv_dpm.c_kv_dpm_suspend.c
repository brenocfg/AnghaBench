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
struct TYPE_3__ {int /*<<< orphan*/  boot_ps; int /*<<< orphan*/  requested_ps; int /*<<< orphan*/  current_ps; } ;
struct TYPE_4__ {int /*<<< orphan*/  mutex; TYPE_1__ dpm; scalar_t__ dpm_enabled; } ;
struct amdgpu_device {TYPE_2__ pm; } ;

/* Variables and functions */
 int /*<<< orphan*/  kv_dpm_disable (struct amdgpu_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int kv_dpm_suspend(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	if (adev->pm.dpm_enabled) {
		mutex_lock(&adev->pm.mutex);
		/* disable dpm */
		kv_dpm_disable(adev);
		/* reset the power state */
		adev->pm.dpm.current_ps = adev->pm.dpm.requested_ps = adev->pm.dpm.boot_ps;
		mutex_unlock(&adev->pm.mutex);
	}
	return 0;
}
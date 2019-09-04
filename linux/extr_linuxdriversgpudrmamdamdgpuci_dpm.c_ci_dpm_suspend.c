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
struct TYPE_4__ {int /*<<< orphan*/  irq; } ;
struct TYPE_5__ {void* state; void* user_state; void* last_state; void* last_user_state; TYPE_1__ thermal; } ;
struct TYPE_6__ {int /*<<< orphan*/  mutex; TYPE_2__ dpm; scalar_t__ dpm_enabled; } ;
struct amdgpu_device {TYPE_3__ pm; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_THERMAL_IRQ_HIGH_TO_LOW ; 
 int /*<<< orphan*/  AMDGPU_THERMAL_IRQ_LOW_TO_HIGH ; 
 void* POWER_STATE_TYPE_INTERNAL_BOOT ; 
 int /*<<< orphan*/  amdgpu_irq_put (struct amdgpu_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_pm_compute_clocks (struct amdgpu_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ci_dpm_suspend(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	if (adev->pm.dpm_enabled) {
		mutex_lock(&adev->pm.mutex);
		amdgpu_irq_put(adev, &adev->pm.dpm.thermal.irq,
			       AMDGPU_THERMAL_IRQ_LOW_TO_HIGH);
		amdgpu_irq_put(adev, &adev->pm.dpm.thermal.irq,
			       AMDGPU_THERMAL_IRQ_HIGH_TO_LOW);
		adev->pm.dpm.last_user_state = adev->pm.dpm.user_state;
		adev->pm.dpm.last_state = adev->pm.dpm.state;
		adev->pm.dpm.user_state = POWER_STATE_TYPE_INTERNAL_BOOT;
		adev->pm.dpm.state = POWER_STATE_TYPE_INTERNAL_BOOT;
		mutex_unlock(&adev->pm.mutex);
		amdgpu_pm_compute_clocks(adev);

	}

	return 0;
}
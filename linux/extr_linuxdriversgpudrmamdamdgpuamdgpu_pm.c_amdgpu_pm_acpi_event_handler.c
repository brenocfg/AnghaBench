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
struct TYPE_6__ {int ac_power; int /*<<< orphan*/  mutex; scalar_t__ dpm_enabled; } ;
struct TYPE_5__ {TYPE_1__* pp_funcs; } ;
struct amdgpu_device {TYPE_3__ pm; TYPE_2__ powerplay; } ;
struct TYPE_4__ {scalar_t__ enable_bapm; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_dpm_enable_bapm (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ power_supply_is_system_supplied () ; 

void amdgpu_pm_acpi_event_handler(struct amdgpu_device *adev)
{
	if (adev->pm.dpm_enabled) {
		mutex_lock(&adev->pm.mutex);
		if (power_supply_is_system_supplied() > 0)
			adev->pm.ac_power = true;
		else
			adev->pm.ac_power = false;
		if (adev->powerplay.pp_funcs->enable_bapm)
			amdgpu_dpm_enable_bapm(adev, adev->pm.ac_power);
		mutex_unlock(&adev->pm.mutex);
	}
}
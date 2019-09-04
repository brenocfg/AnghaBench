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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {scalar_t__ ucode_fan_control; } ;
struct TYPE_5__ {TYPE_1__ fan; } ;
struct TYPE_6__ {TYPE_2__ dpm; } ;
struct amdgpu_device {TYPE_3__ pm; } ;

/* Variables and functions */
 int /*<<< orphan*/  si_fan_ctrl_set_default_mode (struct amdgpu_device*) ; 
 int /*<<< orphan*/  si_fan_ctrl_set_static_mode (struct amdgpu_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  si_fan_ctrl_stop_smc_fan_control (struct amdgpu_device*) ; 
 int /*<<< orphan*/  si_thermal_start_smc_fan_control (struct amdgpu_device*) ; 

__attribute__((used)) static void si_dpm_set_fan_control_mode(void *handle, u32 mode)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	if (mode) {
		/* stop auto-manage */
		if (adev->pm.dpm.fan.ucode_fan_control)
			si_fan_ctrl_stop_smc_fan_control(adev);
		si_fan_ctrl_set_static_mode(adev, mode);
	} else {
		/* restart auto-manage */
		if (adev->pm.dpm.fan.ucode_fan_control)
			si_thermal_start_smc_fan_control(adev);
		else
			si_fan_ctrl_set_default_mode(adev);
	}
}
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
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  ucode_fan_control; } ;
struct TYPE_5__ {TYPE_1__ fan; } ;
struct TYPE_6__ {TYPE_2__ dpm; } ;
struct amdgpu_device {TYPE_3__ pm; } ;

/* Variables and functions */
#define  AMD_FAN_CTRL_AUTO 130 
#define  AMD_FAN_CTRL_MANUAL 129 
#define  AMD_FAN_CTRL_NONE 128 
 int /*<<< orphan*/  ci_dpm_set_fan_speed_percent (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  ci_fan_ctrl_stop_smc_fan_control (struct amdgpu_device*) ; 
 int /*<<< orphan*/  ci_thermal_start_smc_fan_control (struct amdgpu_device*) ; 

__attribute__((used)) static void ci_dpm_set_fan_control_mode(void *handle, u32 mode)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	switch (mode) {
	case AMD_FAN_CTRL_NONE:
		if (adev->pm.dpm.fan.ucode_fan_control)
			ci_fan_ctrl_stop_smc_fan_control(adev);
		ci_dpm_set_fan_speed_percent(adev, 100);
		break;
	case AMD_FAN_CTRL_MANUAL:
		if (adev->pm.dpm.fan.ucode_fan_control)
			ci_fan_ctrl_stop_smc_fan_control(adev);
		break;
	case AMD_FAN_CTRL_AUTO:
		if (adev->pm.dpm.fan.ucode_fan_control)
			ci_thermal_start_smc_fan_control(adev);
		break;
	default:
		break;
	}
}
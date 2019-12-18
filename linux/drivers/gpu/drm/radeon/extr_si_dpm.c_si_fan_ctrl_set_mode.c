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
typedef  scalar_t__ u32 ;
struct TYPE_4__ {scalar_t__ ucode_fan_control; } ;
struct TYPE_5__ {TYPE_1__ fan; } ;
struct TYPE_6__ {TYPE_2__ dpm; } ;
struct radeon_device {TYPE_3__ pm; } ;

/* Variables and functions */
 int /*<<< orphan*/  si_fan_ctrl_set_default_mode (struct radeon_device*) ; 
 int /*<<< orphan*/  si_fan_ctrl_set_static_mode (struct radeon_device*,scalar_t__) ; 
 int /*<<< orphan*/  si_fan_ctrl_stop_smc_fan_control (struct radeon_device*) ; 
 int /*<<< orphan*/  si_thermal_start_smc_fan_control (struct radeon_device*) ; 

void si_fan_ctrl_set_mode(struct radeon_device *rdev, u32 mode)
{
	if (mode) {
		/* stop auto-manage */
		if (rdev->pm.dpm.fan.ucode_fan_control)
			si_fan_ctrl_stop_smc_fan_control(rdev);
		si_fan_ctrl_set_static_mode(rdev, mode);
	} else {
		/* restart auto-manage */
		if (rdev->pm.dpm.fan.ucode_fan_control)
			si_thermal_start_smc_fan_control(rdev);
		else
			si_fan_ctrl_set_default_mode(rdev);
	}
}
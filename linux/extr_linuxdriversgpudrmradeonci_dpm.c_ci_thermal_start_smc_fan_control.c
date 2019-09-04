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
struct TYPE_4__ {scalar_t__ ucode_fan_control; } ;
struct TYPE_5__ {TYPE_1__ fan; } ;
struct TYPE_6__ {TYPE_2__ dpm; } ;
struct radeon_device {TYPE_3__ pm; } ;

/* Variables and functions */
 int /*<<< orphan*/  FDO_PWM_MODE_STATIC ; 
 int /*<<< orphan*/  ci_fan_ctrl_set_static_mode (struct radeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ci_fan_ctrl_start_smc_fan_control (struct radeon_device*) ; 

__attribute__((used)) static void ci_thermal_start_smc_fan_control(struct radeon_device *rdev)
{
	if (rdev->pm.dpm.fan.ucode_fan_control) {
		ci_fan_ctrl_start_smc_fan_control(rdev);
		ci_fan_ctrl_set_static_mode(rdev, FDO_PWM_MODE_STATIC);
	}
}
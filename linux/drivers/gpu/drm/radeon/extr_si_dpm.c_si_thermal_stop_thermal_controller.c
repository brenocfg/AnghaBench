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
struct TYPE_2__ {int /*<<< orphan*/  no_fan; } ;
struct radeon_device {TYPE_1__ pm; } ;

/* Variables and functions */
 int /*<<< orphan*/  si_fan_ctrl_set_default_mode (struct radeon_device*) ; 
 int /*<<< orphan*/  si_fan_ctrl_stop_smc_fan_control (struct radeon_device*) ; 

__attribute__((used)) static void si_thermal_stop_thermal_controller(struct radeon_device *rdev)
{
	if (!rdev->pm.no_fan) {
		si_fan_ctrl_set_default_mode(rdev);
		si_fan_ctrl_stop_smc_fan_control(rdev);
	}
}
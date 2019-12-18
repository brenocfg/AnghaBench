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
struct amdgpu_device {TYPE_1__ pm; } ;

/* Variables and functions */
 int /*<<< orphan*/  si_fan_ctrl_set_default_mode (struct amdgpu_device*) ; 
 int /*<<< orphan*/  si_fan_ctrl_stop_smc_fan_control (struct amdgpu_device*) ; 

__attribute__((used)) static void si_thermal_stop_thermal_controller(struct amdgpu_device *adev)
{
	if (!adev->pm.no_fan) {
		si_fan_ctrl_set_default_mode(adev);
		si_fan_ctrl_stop_smc_fan_control(adev);
	}
}
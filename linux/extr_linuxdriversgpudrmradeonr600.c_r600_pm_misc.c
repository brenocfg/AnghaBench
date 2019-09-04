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
struct radeon_voltage {scalar_t__ type; int voltage; } ;
struct radeon_power_state {TYPE_1__* clock_info; } ;
struct TYPE_4__ {int requested_power_state_index; int requested_clock_mode_index; int current_vddc; struct radeon_power_state* power_state; } ;
struct radeon_device {TYPE_2__ pm; } ;
struct TYPE_3__ {struct radeon_voltage voltage; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int) ; 
 int /*<<< orphan*/  SET_VOLTAGE_TYPE_ASIC_VDDC ; 
 scalar_t__ VOLTAGE_SW ; 
 int /*<<< orphan*/  radeon_atom_set_voltage (struct radeon_device*,int,int /*<<< orphan*/ ) ; 

void r600_pm_misc(struct radeon_device *rdev)
{
	int req_ps_idx = rdev->pm.requested_power_state_index;
	int req_cm_idx = rdev->pm.requested_clock_mode_index;
	struct radeon_power_state *ps = &rdev->pm.power_state[req_ps_idx];
	struct radeon_voltage *voltage = &ps->clock_info[req_cm_idx].voltage;

	if ((voltage->type == VOLTAGE_SW) && voltage->voltage) {
		/* 0xff01 is a flag rather then an actual voltage */
		if (voltage->voltage == 0xff01)
			return;
		if (voltage->voltage != rdev->pm.current_vddc) {
			radeon_atom_set_voltage(rdev, voltage->voltage, SET_VOLTAGE_TYPE_ASIC_VDDC);
			rdev->pm.current_vddc = voltage->voltage;
			DRM_DEBUG_DRIVER("Setting: v: %d\n", voltage->voltage);
		}
	}
}
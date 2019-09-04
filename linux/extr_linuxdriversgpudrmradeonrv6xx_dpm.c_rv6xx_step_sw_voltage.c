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
typedef  scalar_t__ u16 ;
struct TYPE_3__ {int voltage_response_time; } ;
struct TYPE_4__ {TYPE_1__ dpm; } ;
struct radeon_device {TYPE_2__ pm; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  R600_POWER_LEVEL_CTXSW ; 
 int /*<<< orphan*/  SET_VOLTAGE_TYPE_ASIC_VDDC ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ radeon_atom_get_voltage_step (struct radeon_device*,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ radeon_atom_round_to_true_voltage (struct radeon_device*,int /*<<< orphan*/ ,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  rv6xx_program_voltage_stepping_entry (struct radeon_device*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int rv6xx_step_sw_voltage(struct radeon_device *rdev,
				 u16 initial_voltage,
				 u16 target_voltage)
{
	u16 current_voltage;
	u16 true_target_voltage;
	u16 voltage_step;
	int signed_voltage_step;

	if ((radeon_atom_get_voltage_step(rdev, SET_VOLTAGE_TYPE_ASIC_VDDC,
					  &voltage_step)) ||
	    (radeon_atom_round_to_true_voltage(rdev, SET_VOLTAGE_TYPE_ASIC_VDDC,
					       initial_voltage, &current_voltage)) ||
	    (radeon_atom_round_to_true_voltage(rdev, SET_VOLTAGE_TYPE_ASIC_VDDC,
					       target_voltage, &true_target_voltage)))
		return -EINVAL;

	if (true_target_voltage < current_voltage)
		signed_voltage_step = -(int)voltage_step;
	else
		signed_voltage_step = voltage_step;

	while (current_voltage != true_target_voltage) {
		current_voltage += signed_voltage_step;
		rv6xx_program_voltage_stepping_entry(rdev, R600_POWER_LEVEL_CTXSW,
						     current_voltage);
		msleep((rdev->pm.dpm.voltage_response_time + 999) / 1000);
	}

	return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ radeon_atom_get_max_voltage (struct radeon_device*,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ radeon_atom_get_min_voltage (struct radeon_device*,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ radeon_atom_get_voltage_step (struct radeon_device*,int /*<<< orphan*/ ,scalar_t__*) ; 

int radeon_atom_round_to_true_voltage(struct radeon_device *rdev,
				      u8 voltage_type,
				      u16 nominal_voltage,
				      u16 *true_voltage)
{
	u16 min_voltage, max_voltage, voltage_step;

	if (radeon_atom_get_max_voltage(rdev, voltage_type, &max_voltage))
		return -EINVAL;
	if (radeon_atom_get_min_voltage(rdev, voltage_type, &min_voltage))
		return -EINVAL;
	if (radeon_atom_get_voltage_step(rdev, voltage_type, &voltage_step))
		return -EINVAL;

	if (nominal_voltage <= min_voltage)
		*true_voltage = min_voltage;
	else if (nominal_voltage >= max_voltage)
		*true_voltage = max_voltage;
	else
		*true_voltage = min_voltage +
			((nominal_voltage - min_voltage) / voltage_step) *
			voltage_step;

	return 0;
}
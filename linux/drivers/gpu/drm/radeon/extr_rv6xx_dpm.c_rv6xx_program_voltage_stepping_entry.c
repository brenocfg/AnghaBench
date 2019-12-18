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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SET_VOLTAGE_TYPE_ASIC_VDDC ; 
 int /*<<< orphan*/  r600_voltage_control_program_voltages (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int radeon_atom_get_voltage_gpio_settings (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rv6xx_program_voltage_stepping_entry(struct radeon_device *rdev,
						u32 entry, u16 voltage)
{
	u32 mask, set_pins;
	int ret;

	ret = radeon_atom_get_voltage_gpio_settings(rdev, voltage,
						    SET_VOLTAGE_TYPE_ASIC_VDDC,
						    &set_pins, &mask);
	if (ret)
		return ret;

	r600_voltage_control_program_voltages(rdev, entry, set_pins);

	return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct radeon_device {int dummy; } ;
struct TYPE_3__ {scalar_t__ count; } ;
struct evergreen_power_info {TYPE_1__ vddci_voltage_table; scalar_t__ vddci_control; TYPE_1__ vddc_voltage_table; } ;

/* Variables and functions */
 scalar_t__ MAX_NO_VREG_STEPS ; 
 int /*<<< orphan*/  SET_VOLTAGE_TYPE_ASIC_VDDC ; 
 int /*<<< orphan*/  SET_VOLTAGE_TYPE_ASIC_VDDCI ; 
 int /*<<< orphan*/  cypress_trim_voltage_table_to_fit_state_table (struct radeon_device*,TYPE_1__*) ; 
 struct evergreen_power_info* evergreen_get_pi (struct radeon_device*) ; 
 int radeon_atom_get_voltage_table (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

int cypress_construct_voltage_tables(struct radeon_device *rdev)
{
	struct evergreen_power_info *eg_pi = evergreen_get_pi(rdev);
	int ret;

	ret = radeon_atom_get_voltage_table(rdev, SET_VOLTAGE_TYPE_ASIC_VDDC, 0,
					    &eg_pi->vddc_voltage_table);
	if (ret)
		return ret;

	if (eg_pi->vddc_voltage_table.count > MAX_NO_VREG_STEPS)
		cypress_trim_voltage_table_to_fit_state_table(rdev,
							      &eg_pi->vddc_voltage_table);

	if (eg_pi->vddci_control) {
		ret = radeon_atom_get_voltage_table(rdev, SET_VOLTAGE_TYPE_ASIC_VDDCI, 0,
						    &eg_pi->vddci_voltage_table);
		if (ret)
			return ret;

		if (eg_pi->vddci_voltage_table.count > MAX_NO_VREG_STEPS)
			cypress_trim_voltage_table_to_fit_state_table(rdev,
								      &eg_pi->vddci_voltage_table);
	}

	return 0;
}
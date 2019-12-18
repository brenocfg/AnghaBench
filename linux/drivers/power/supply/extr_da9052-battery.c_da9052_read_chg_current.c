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
struct da9052_battery {scalar_t__ status; int /*<<< orphan*/  da9052; } ;

/* Variables and functions */
 int DA9052_ICHGAV_ICHGAV ; 
 int /*<<< orphan*/  DA9052_ICHG_AV_REG ; 
 int EINVAL ; 
 scalar_t__ POWER_SUPPLY_STATUS_DISCHARGING ; 
 int da9052_reg_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ichg_reg_to_mA (int) ; 

__attribute__((used)) static int da9052_read_chg_current(struct da9052_battery *bat, int *current_mA)
{
	int ret;

	if (bat->status == POWER_SUPPLY_STATUS_DISCHARGING)
		return -EINVAL;

	ret = da9052_reg_read(bat->da9052, DA9052_ICHG_AV_REG);
	if (ret < 0)
		return ret;

	*current_mA = ichg_reg_to_mA(ret & DA9052_ICHGAV_ICHGAV);

	return 0;
}
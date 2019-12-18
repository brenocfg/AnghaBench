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
union power_supply_propval {int intval; } ;
struct da9150_charger {int /*<<< orphan*/  da9150; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA9150_PPR_CHGCTRL_D ; 
 int da9150_reg_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int da9150_charger_battery_current_max(struct da9150_charger *charger,
					      union power_supply_propval *val)
{
	int reg;

	reg = da9150_reg_read(charger->da9150, DA9150_PPR_CHGCTRL_D);

	/* 25mA increments */
	val->intval = reg * 25000;

	return 0;
}
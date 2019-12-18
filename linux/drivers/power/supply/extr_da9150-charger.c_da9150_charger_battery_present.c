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
typedef  int u8 ;
struct da9150_charger {int /*<<< orphan*/  da9150; } ;

/* Variables and functions */
 int DA9150_CHG_STAT_BAT ; 
 int DA9150_CHG_STAT_MASK ; 
 int /*<<< orphan*/  DA9150_STATUS_J ; 
 int da9150_reg_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int da9150_charger_battery_present(struct da9150_charger *charger,
					  union power_supply_propval *val)
{
	u8 reg;

	/* Check if battery present or removed */
	reg = da9150_reg_read(charger->da9150, DA9150_STATUS_J);
	if ((reg & DA9150_CHG_STAT_MASK) == DA9150_CHG_STAT_BAT)
		val->intval = 0;
	else
		val->intval = 1;

	return 0;
}
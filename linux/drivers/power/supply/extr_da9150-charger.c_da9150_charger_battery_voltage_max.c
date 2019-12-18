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
 int DA9150_CHG_VBAT_MASK ; 
 int /*<<< orphan*/  DA9150_PPR_CHGCTRL_B ; 
 int da9150_reg_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int da9150_charger_battery_voltage_max(struct da9150_charger *charger,
					      union power_supply_propval *val)
{
	u8 reg;

	reg = da9150_reg_read(charger->da9150, DA9150_PPR_CHGCTRL_B);

	/* Value starts at 3650 mV, 25 mV increments, presented in uV */
	val->intval = ((reg & DA9150_CHG_VBAT_MASK) * 25000) + 3650000;
	return 0;
}
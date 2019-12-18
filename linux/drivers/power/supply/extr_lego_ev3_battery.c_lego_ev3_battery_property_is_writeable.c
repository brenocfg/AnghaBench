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
struct power_supply {int dummy; } ;
struct lego_ev3_battery {scalar_t__ technology; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int POWER_SUPPLY_PROP_TECHNOLOGY ; 
 scalar_t__ POWER_SUPPLY_TECHNOLOGY_UNKNOWN ; 
 struct lego_ev3_battery* power_supply_get_drvdata (struct power_supply*) ; 

__attribute__((used)) static int lego_ev3_battery_property_is_writeable(struct power_supply *psy,
						  enum power_supply_property psp)
{
	struct lego_ev3_battery *batt = power_supply_get_drvdata(psy);

	return psp == POWER_SUPPLY_PROP_TECHNOLOGY &&
		batt->technology == POWER_SUPPLY_TECHNOLOGY_UNKNOWN;
}
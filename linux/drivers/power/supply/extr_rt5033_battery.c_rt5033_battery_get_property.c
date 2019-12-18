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
union power_supply_propval {int /*<<< orphan*/  intval; } ;
struct rt5033_battery {int /*<<< orphan*/  client; } ;
struct power_supply {int dummy; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int EINVAL ; 
#define  POWER_SUPPLY_PROP_CAPACITY 132 
#define  POWER_SUPPLY_PROP_PRESENT 131 
#define  POWER_SUPPLY_PROP_VOLTAGE_AVG 130 
#define  POWER_SUPPLY_PROP_VOLTAGE_NOW 129 
#define  POWER_SUPPLY_PROP_VOLTAGE_OCV 128 
 struct rt5033_battery* power_supply_get_drvdata (struct power_supply*) ; 
 int /*<<< orphan*/  rt5033_battery_get_capacity (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt5033_battery_get_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt5033_battery_get_watt_prop (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rt5033_battery_get_property(struct power_supply *psy,
		enum power_supply_property psp,
		union power_supply_propval *val)
{
	struct rt5033_battery *battery = power_supply_get_drvdata(psy);

	switch (psp) {
	case POWER_SUPPLY_PROP_VOLTAGE_NOW:
	case POWER_SUPPLY_PROP_VOLTAGE_AVG:
	case POWER_SUPPLY_PROP_VOLTAGE_OCV:
		val->intval = rt5033_battery_get_watt_prop(battery->client,
									psp);
		break;
	case POWER_SUPPLY_PROP_PRESENT:
		val->intval = rt5033_battery_get_present(battery->client);
		break;
	case POWER_SUPPLY_PROP_CAPACITY:
		val->intval = rt5033_battery_get_capacity(battery->client);
		break;
	default:
		return -EINVAL;
	}
	return 0;
}
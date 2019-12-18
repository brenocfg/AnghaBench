#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
union power_supply_propval {int intval; } ;
struct twl4030_madc_battery {TYPE_1__* pdata; } ;
struct power_supply {int dummy; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;
struct TYPE_2__ {int capacity; } ;

/* Variables and functions */
 int EINVAL ; 
#define  POWER_SUPPLY_PROP_CAPACITY 137 
#define  POWER_SUPPLY_PROP_CHARGE_FULL 136 
#define  POWER_SUPPLY_PROP_CHARGE_NOW 135 
#define  POWER_SUPPLY_PROP_CURRENT_NOW 134 
#define  POWER_SUPPLY_PROP_PRESENT 133 
#define  POWER_SUPPLY_PROP_STATUS 132 
#define  POWER_SUPPLY_PROP_TECHNOLOGY 131 
#define  POWER_SUPPLY_PROP_TEMP 130 
#define  POWER_SUPPLY_PROP_TIME_TO_EMPTY_NOW 129 
#define  POWER_SUPPLY_PROP_VOLTAGE_NOW 128 
 int POWER_SUPPLY_STATUS_CHARGING ; 
 int POWER_SUPPLY_STATUS_DISCHARGING ; 
 int POWER_SUPPLY_STATUS_FULL ; 
 int POWER_SUPPLY_TECHNOLOGY_LION ; 
 struct twl4030_madc_battery* power_supply_get_drvdata (struct power_supply*) ; 
 int /*<<< orphan*/  twl4030_madc_bat_get_charging_status (struct twl4030_madc_battery*) ; 
 int twl4030_madc_bat_get_current (struct twl4030_madc_battery*) ; 
 int twl4030_madc_bat_get_temp (struct twl4030_madc_battery*) ; 
 int twl4030_madc_bat_get_voltage (struct twl4030_madc_battery*) ; 
 int twl4030_madc_bat_voltscale (struct twl4030_madc_battery*,int) ; 

__attribute__((used)) static int twl4030_madc_bat_get_property(struct power_supply *psy,
					enum power_supply_property psp,
					union power_supply_propval *val)
{
	struct twl4030_madc_battery *bat = power_supply_get_drvdata(psy);

	switch (psp) {
	case POWER_SUPPLY_PROP_STATUS:
		if (twl4030_madc_bat_voltscale(bat,
				twl4030_madc_bat_get_voltage(bat)) > 95)
			val->intval = POWER_SUPPLY_STATUS_FULL;
		else {
			if (twl4030_madc_bat_get_charging_status(bat))
				val->intval = POWER_SUPPLY_STATUS_CHARGING;
			else
				val->intval = POWER_SUPPLY_STATUS_DISCHARGING;
		}
		break;
	case POWER_SUPPLY_PROP_VOLTAGE_NOW:
		val->intval = twl4030_madc_bat_get_voltage(bat) * 1000;
		break;
	case POWER_SUPPLY_PROP_TECHNOLOGY:
		val->intval = POWER_SUPPLY_TECHNOLOGY_LION;
		break;
	case POWER_SUPPLY_PROP_CURRENT_NOW:
		val->intval = twl4030_madc_bat_get_current(bat);
		break;
	case POWER_SUPPLY_PROP_PRESENT:
		/* assume battery is always present */
		val->intval = 1;
		break;
	case POWER_SUPPLY_PROP_CHARGE_NOW: {
			int percent = twl4030_madc_bat_voltscale(bat,
					twl4030_madc_bat_get_voltage(bat));
			val->intval = (percent * bat->pdata->capacity) / 100;
			break;
		}
	case POWER_SUPPLY_PROP_CAPACITY:
		val->intval = twl4030_madc_bat_voltscale(bat,
					twl4030_madc_bat_get_voltage(bat));
		break;
	case POWER_SUPPLY_PROP_CHARGE_FULL:
		val->intval = bat->pdata->capacity;
		break;
	case POWER_SUPPLY_PROP_TEMP:
		val->intval = twl4030_madc_bat_get_temp(bat);
		break;
	case POWER_SUPPLY_PROP_TIME_TO_EMPTY_NOW: {
			int percent = twl4030_madc_bat_voltscale(bat,
					twl4030_madc_bat_get_voltage(bat));
			/* in mAh */
			int chg = (percent * (bat->pdata->capacity/1000))/100;

			/* assume discharge with 400 mA (ca. 1.5W) */
			val->intval = (3600l * chg) / 400;
			break;
		}
	default:
		return -EINVAL;
	}

	return 0;
}
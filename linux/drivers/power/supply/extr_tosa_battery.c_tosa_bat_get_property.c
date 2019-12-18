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
struct tosa_bat {int (* is_present ) (struct tosa_bat*) ;int status; int technology; int full_chrg; int bat_max; int bat_min; } ;
struct power_supply {int dummy; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
#define  POWER_SUPPLY_PROP_PRESENT 135 
#define  POWER_SUPPLY_PROP_STATUS 134 
#define  POWER_SUPPLY_PROP_TECHNOLOGY 133 
#define  POWER_SUPPLY_PROP_TEMP 132 
#define  POWER_SUPPLY_PROP_VOLTAGE_MAX 131 
#define  POWER_SUPPLY_PROP_VOLTAGE_MAX_DESIGN 130 
#define  POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN 129 
#define  POWER_SUPPLY_PROP_VOLTAGE_NOW 128 
 struct tosa_bat* power_supply_get_drvdata (struct power_supply*) ; 
 int stub1 (struct tosa_bat*) ; 
 int stub2 (struct tosa_bat*) ; 
 int tosa_read_bat (struct tosa_bat*) ; 
 int tosa_read_temp (struct tosa_bat*) ; 

__attribute__((used)) static int tosa_bat_get_property(struct power_supply *psy,
			    enum power_supply_property psp,
			    union power_supply_propval *val)
{
	int ret = 0;
	struct tosa_bat *bat = power_supply_get_drvdata(psy);

	if (bat->is_present && !bat->is_present(bat)
			&& psp != POWER_SUPPLY_PROP_PRESENT) {
		return -ENODEV;
	}

	switch (psp) {
	case POWER_SUPPLY_PROP_STATUS:
		val->intval = bat->status;
		break;
	case POWER_SUPPLY_PROP_TECHNOLOGY:
		val->intval = bat->technology;
		break;
	case POWER_SUPPLY_PROP_VOLTAGE_NOW:
		val->intval = tosa_read_bat(bat);
		break;
	case POWER_SUPPLY_PROP_VOLTAGE_MAX:
		if (bat->full_chrg == -1)
			val->intval = bat->bat_max;
		else
			val->intval = bat->full_chrg;
		break;
	case POWER_SUPPLY_PROP_VOLTAGE_MAX_DESIGN:
		val->intval = bat->bat_max;
		break;
	case POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN:
		val->intval = bat->bat_min;
		break;
	case POWER_SUPPLY_PROP_TEMP:
		val->intval = tosa_read_temp(bat);
		break;
	case POWER_SUPPLY_PROP_PRESENT:
		val->intval = bat->is_present ? bat->is_present(bat) : 1;
		break;
	default:
		ret = -EINVAL;
		break;
	}
	return ret;
}
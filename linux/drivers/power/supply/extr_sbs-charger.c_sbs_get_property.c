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
struct sbs_info {unsigned int last_state; } ;
struct power_supply {int dummy; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int EINVAL ; 
 int POWER_SUPPLY_HEALTH_COLD ; 
 int POWER_SUPPLY_HEALTH_GOOD ; 
 int POWER_SUPPLY_HEALTH_OVERHEAT ; 
#define  POWER_SUPPLY_PROP_HEALTH 131 
#define  POWER_SUPPLY_PROP_ONLINE 130 
#define  POWER_SUPPLY_PROP_PRESENT 129 
#define  POWER_SUPPLY_PROP_STATUS 128 
 int POWER_SUPPLY_STATUS_CHARGING ; 
 int POWER_SUPPLY_STATUS_DISCHARGING ; 
 int POWER_SUPPLY_STATUS_NOT_CHARGING ; 
 int POWER_SUPPLY_STATUS_UNKNOWN ; 
 unsigned int SBS_CHARGER_STATUS_AC_PRESENT ; 
 unsigned int SBS_CHARGER_STATUS_BATTERY_PRESENT ; 
 unsigned int SBS_CHARGER_STATUS_CHARGE_INHIBITED ; 
 unsigned int SBS_CHARGER_STATUS_RES_COLD ; 
 unsigned int SBS_CHARGER_STATUS_RES_HOT ; 
 struct sbs_info* power_supply_get_drvdata (struct power_supply*) ; 

__attribute__((used)) static int sbs_get_property(struct power_supply *psy,
			    enum power_supply_property psp,
			    union power_supply_propval *val)
{
	struct sbs_info *chip = power_supply_get_drvdata(psy);
	unsigned int reg;

	reg = chip->last_state;

	switch (psp) {
	case POWER_SUPPLY_PROP_PRESENT:
		val->intval = !!(reg & SBS_CHARGER_STATUS_BATTERY_PRESENT);
		break;

	case POWER_SUPPLY_PROP_ONLINE:
		val->intval = !!(reg & SBS_CHARGER_STATUS_AC_PRESENT);
		break;

	case POWER_SUPPLY_PROP_STATUS:
		val->intval = POWER_SUPPLY_STATUS_UNKNOWN;

		if (!(reg & SBS_CHARGER_STATUS_BATTERY_PRESENT))
			val->intval = POWER_SUPPLY_STATUS_NOT_CHARGING;
		else if (reg & SBS_CHARGER_STATUS_AC_PRESENT &&
			 !(reg & SBS_CHARGER_STATUS_CHARGE_INHIBITED))
			val->intval = POWER_SUPPLY_STATUS_CHARGING;
		else
			val->intval = POWER_SUPPLY_STATUS_DISCHARGING;

		break;

	case POWER_SUPPLY_PROP_HEALTH:
		if (reg & SBS_CHARGER_STATUS_RES_COLD)
			val->intval = POWER_SUPPLY_HEALTH_COLD;
		if (reg & SBS_CHARGER_STATUS_RES_HOT)
			val->intval = POWER_SUPPLY_HEALTH_OVERHEAT;
		else
			val->intval = POWER_SUPPLY_HEALTH_GOOD;

		break;

	default:
		return -EINVAL;
	}

	return 0;
}
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
union power_supply_propval {int intval; int /*<<< orphan*/  strval; } ;
struct power_supply {int dummy; } ;
struct max17211_device_info {int /*<<< orphan*/  SerialNumber; int /*<<< orphan*/  regmap; int /*<<< orphan*/  ManufacturerName; int /*<<< orphan*/  DeviceName; scalar_t__ rsense; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MAX1721X_REG_DEV_STR ; 
 int /*<<< orphan*/  MAX1721X_REG_MFG_STR ; 
 int /*<<< orphan*/  MAX1721X_REG_SER_HEX ; 
 unsigned int MAX172XX_BAT_PRESENT ; 
 int /*<<< orphan*/  MAX172XX_REG_AVGCURRENT ; 
 int /*<<< orphan*/  MAX172XX_REG_BATT ; 
 int /*<<< orphan*/  MAX172XX_REG_CURRENT ; 
 int /*<<< orphan*/  MAX172XX_REG_DESIGNCAP ; 
 int /*<<< orphan*/  MAX172XX_REG_REPCAP ; 
 int /*<<< orphan*/  MAX172XX_REG_REPSOC ; 
 int /*<<< orphan*/  MAX172XX_REG_STATUS ; 
 int /*<<< orphan*/  MAX172XX_REG_TEMP ; 
 int /*<<< orphan*/  MAX172XX_REG_TTE ; 
 int /*<<< orphan*/  MAX172XX_REG_TTF ; 
#define  POWER_SUPPLY_PROP_CAPACITY 140 
#define  POWER_SUPPLY_PROP_CHARGE_AVG 139 
#define  POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN 138 
#define  POWER_SUPPLY_PROP_CURRENT_AVG 137 
#define  POWER_SUPPLY_PROP_CURRENT_NOW 136 
#define  POWER_SUPPLY_PROP_MANUFACTURER 135 
#define  POWER_SUPPLY_PROP_MODEL_NAME 134 
#define  POWER_SUPPLY_PROP_PRESENT 133 
#define  POWER_SUPPLY_PROP_SERIAL_NUMBER 132 
#define  POWER_SUPPLY_PROP_TEMP 131 
#define  POWER_SUPPLY_PROP_TIME_TO_EMPTY_AVG 130 
#define  POWER_SUPPLY_PROP_TIME_TO_FULL_AVG 129 
#define  POWER_SUPPLY_PROP_VOLTAGE_NOW 128 
 void* max172xx_capacity_to_ps (unsigned int) ; 
 int max172xx_current_to_voltage (unsigned int) ; 
 int max172xx_percent_to_ps (unsigned int) ; 
 int max172xx_temperature_to_ps (unsigned int) ; 
 void* max172xx_time_to_ps (unsigned int) ; 
 int max172xx_voltage_to_ps (unsigned int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 struct max17211_device_info* to_device_info (struct power_supply*) ; 

__attribute__((used)) static int max1721x_battery_get_property(struct power_supply *psy,
	enum power_supply_property psp,
	union power_supply_propval *val)
{
	struct max17211_device_info *info = to_device_info(psy);
	unsigned int reg = 0;
	int ret = 0;

	switch (psp) {
	case POWER_SUPPLY_PROP_PRESENT:
		/*
		 * POWER_SUPPLY_PROP_PRESENT will always readable via
		 * sysfs interface. Value return 0 if battery not
		 * present or unaccesable via W1.
		 */
		val->intval =
			regmap_read(info->regmap, MAX172XX_REG_STATUS,
			&reg) ? 0 : !(reg & MAX172XX_BAT_PRESENT);
		break;
	case POWER_SUPPLY_PROP_CAPACITY:
		ret = regmap_read(info->regmap, MAX172XX_REG_REPSOC, &reg);
		val->intval = max172xx_percent_to_ps(reg);
		break;
	case POWER_SUPPLY_PROP_VOLTAGE_NOW:
		ret = regmap_read(info->regmap, MAX172XX_REG_BATT, &reg);
		val->intval = max172xx_voltage_to_ps(reg);
		break;
	case POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN:
		ret = regmap_read(info->regmap, MAX172XX_REG_DESIGNCAP, &reg);
		val->intval = max172xx_capacity_to_ps(reg);
		break;
	case POWER_SUPPLY_PROP_CHARGE_AVG:
		ret = regmap_read(info->regmap, MAX172XX_REG_REPCAP, &reg);
		val->intval = max172xx_capacity_to_ps(reg);
		break;
	case POWER_SUPPLY_PROP_TIME_TO_EMPTY_AVG:
		ret = regmap_read(info->regmap, MAX172XX_REG_TTE, &reg);
		val->intval = max172xx_time_to_ps(reg);
		break;
	case POWER_SUPPLY_PROP_TIME_TO_FULL_AVG:
		ret = regmap_read(info->regmap, MAX172XX_REG_TTF, &reg);
		val->intval = max172xx_time_to_ps(reg);
		break;
	case POWER_SUPPLY_PROP_TEMP:
		ret = regmap_read(info->regmap, MAX172XX_REG_TEMP, &reg);
		val->intval = max172xx_temperature_to_ps(reg);
		break;
	/* We need signed current, so must cast info->rsense to signed type */
	case POWER_SUPPLY_PROP_CURRENT_NOW:
		ret = regmap_read(info->regmap, MAX172XX_REG_CURRENT, &reg);
		val->intval =
			max172xx_current_to_voltage(reg) / (int)info->rsense;
		break;
	case POWER_SUPPLY_PROP_CURRENT_AVG:
		ret = regmap_read(info->regmap, MAX172XX_REG_AVGCURRENT, &reg);
		val->intval =
			max172xx_current_to_voltage(reg) / (int)info->rsense;
		break;
	/*
	 * Strings already received and inited by probe.
	 * We do dummy read for check battery still available.
	 */
	case POWER_SUPPLY_PROP_MODEL_NAME:
		ret = regmap_read(info->regmap, MAX1721X_REG_DEV_STR, &reg);
		val->strval = info->DeviceName;
		break;
	case POWER_SUPPLY_PROP_MANUFACTURER:
		ret = regmap_read(info->regmap, MAX1721X_REG_MFG_STR, &reg);
		val->strval = info->ManufacturerName;
		break;
	case POWER_SUPPLY_PROP_SERIAL_NUMBER:
		ret = regmap_read(info->regmap, MAX1721X_REG_SER_HEX, &reg);
		val->strval = info->SerialNumber;
		break;
	default:
		ret = -EINVAL;
	}

	return ret;
}
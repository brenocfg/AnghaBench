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
struct power_supply {int dummy; } ;
struct axp20x_ac_power {int /*<<< orphan*/  regmap; int /*<<< orphan*/  acin_i; int /*<<< orphan*/  acin_v; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int /*<<< orphan*/  AXP20X_PWR_INPUT_STATUS ; 
 int AXP20X_PWR_STATUS_ACIN_AVAIL ; 
 int AXP20X_PWR_STATUS_ACIN_PRESENT ; 
 int /*<<< orphan*/  AXP813_ACIN_PATH_CTRL ; 
 int AXP813_CURR_LIMIT_REG_TO_UA (int) ; 
 int AXP813_VHOLD_REG_TO_UV (int) ; 
 int EINVAL ; 
 int POWER_SUPPLY_HEALTH_GOOD ; 
 int POWER_SUPPLY_HEALTH_UNKNOWN ; 
#define  POWER_SUPPLY_PROP_CURRENT_NOW 134 
#define  POWER_SUPPLY_PROP_HEALTH 133 
#define  POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT 132 
#define  POWER_SUPPLY_PROP_ONLINE 131 
#define  POWER_SUPPLY_PROP_PRESENT 130 
#define  POWER_SUPPLY_PROP_VOLTAGE_MIN 129 
#define  POWER_SUPPLY_PROP_VOLTAGE_NOW 128 
 int iio_read_channel_processed (int /*<<< orphan*/ ,int*) ; 
 struct axp20x_ac_power* power_supply_get_drvdata (struct power_supply*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int axp20x_ac_power_get_property(struct power_supply *psy,
					enum power_supply_property psp,
					union power_supply_propval *val)
{
	struct axp20x_ac_power *power = power_supply_get_drvdata(psy);
	int ret, reg;

	switch (psp) {
	case POWER_SUPPLY_PROP_HEALTH:
		ret = regmap_read(power->regmap, AXP20X_PWR_INPUT_STATUS, &reg);
		if (ret)
			return ret;

		if (reg & AXP20X_PWR_STATUS_ACIN_PRESENT) {
			val->intval = POWER_SUPPLY_HEALTH_GOOD;
			return 0;
		}

		val->intval = POWER_SUPPLY_HEALTH_UNKNOWN;
		return 0;

	case POWER_SUPPLY_PROP_PRESENT:
		ret = regmap_read(power->regmap, AXP20X_PWR_INPUT_STATUS, &reg);
		if (ret)
			return ret;

		val->intval = !!(reg & AXP20X_PWR_STATUS_ACIN_PRESENT);
		return 0;

	case POWER_SUPPLY_PROP_ONLINE:
		ret = regmap_read(power->regmap, AXP20X_PWR_INPUT_STATUS, &reg);
		if (ret)
			return ret;

		val->intval = !!(reg & AXP20X_PWR_STATUS_ACIN_AVAIL);
		return 0;

	case POWER_SUPPLY_PROP_VOLTAGE_NOW:
		ret = iio_read_channel_processed(power->acin_v, &val->intval);
		if (ret)
			return ret;

		/* IIO framework gives mV but Power Supply framework gives uV */
		val->intval *= 1000;

		return 0;

	case POWER_SUPPLY_PROP_CURRENT_NOW:
		ret = iio_read_channel_processed(power->acin_i, &val->intval);
		if (ret)
			return ret;

		/* IIO framework gives mA but Power Supply framework gives uA */
		val->intval *= 1000;

		return 0;

	case POWER_SUPPLY_PROP_VOLTAGE_MIN:
		ret = regmap_read(power->regmap, AXP813_ACIN_PATH_CTRL, &reg);
		if (ret)
			return ret;

		val->intval = AXP813_VHOLD_REG_TO_UV(reg);

		return 0;

	case POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT:
		ret = regmap_read(power->regmap, AXP813_ACIN_PATH_CTRL, &reg);
		if (ret)
			return ret;

		val->intval = AXP813_CURR_LIMIT_REG_TO_UA(reg);
		/* AXP813 datasheet defines values 11x as 4000mA */
		if (val->intval > 4000000)
			val->intval = 4000000;

		return 0;

	default:
		return -EINVAL;
	}

	return -EINVAL;
}
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
struct power_supply {int dummy; } ;
struct iio_channel {int dummy; } ;
struct axp20x_batt_ps {int max_ccc; struct iio_channel* batt_v; int /*<<< orphan*/  regmap; TYPE_1__* data; struct iio_channel* batt_dischrg_i; struct iio_channel* batt_chrg_i; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;
struct TYPE_2__ {int (* get_max_voltage ) (struct axp20x_batt_ps*,int*) ;int /*<<< orphan*/  has_fg_valid; } ;

/* Variables and functions */
 int AXP209_FG_PERCENT ; 
 int /*<<< orphan*/  AXP20X_FG_RES ; 
 int /*<<< orphan*/  AXP20X_PWR_INPUT_STATUS ; 
 int AXP20X_PWR_OP_BATT_ACTIVATED ; 
 int AXP20X_PWR_OP_BATT_PRESENT ; 
 int /*<<< orphan*/  AXP20X_PWR_OP_MODE ; 
 int AXP20X_PWR_STATUS_BAT_CHARGING ; 
 int /*<<< orphan*/  AXP20X_V_OFF ; 
 int AXP20X_V_OFF_MASK ; 
 int AXP22X_FG_VALID ; 
 int EINVAL ; 
 int POWER_SUPPLY_HEALTH_DEAD ; 
 int POWER_SUPPLY_HEALTH_GOOD ; 
#define  POWER_SUPPLY_PROP_CAPACITY 138 
#define  POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT 137 
#define  POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT_MAX 136 
#define  POWER_SUPPLY_PROP_CURRENT_NOW 135 
#define  POWER_SUPPLY_PROP_HEALTH 134 
#define  POWER_SUPPLY_PROP_ONLINE 133 
#define  POWER_SUPPLY_PROP_PRESENT 132 
#define  POWER_SUPPLY_PROP_STATUS 131 
#define  POWER_SUPPLY_PROP_VOLTAGE_MAX_DESIGN 130 
#define  POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN 129 
#define  POWER_SUPPLY_PROP_VOLTAGE_NOW 128 
 int POWER_SUPPLY_STATUS_CHARGING ; 
 int POWER_SUPPLY_STATUS_DISCHARGING ; 
 int POWER_SUPPLY_STATUS_FULL ; 
 int POWER_SUPPLY_STATUS_NOT_CHARGING ; 
 int axp20x_get_constant_charge_current (struct axp20x_batt_ps*,int*) ; 
 int iio_read_channel_processed (struct iio_channel*,int*) ; 
 struct axp20x_batt_ps* power_supply_get_drvdata (struct power_supply*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int stub1 (struct axp20x_batt_ps*,int*) ; 

__attribute__((used)) static int axp20x_battery_get_prop(struct power_supply *psy,
				   enum power_supply_property psp,
				   union power_supply_propval *val)
{
	struct axp20x_batt_ps *axp20x_batt = power_supply_get_drvdata(psy);
	struct iio_channel *chan;
	int ret = 0, reg, val1;

	switch (psp) {
	case POWER_SUPPLY_PROP_PRESENT:
	case POWER_SUPPLY_PROP_ONLINE:
		ret = regmap_read(axp20x_batt->regmap, AXP20X_PWR_OP_MODE,
				  &reg);
		if (ret)
			return ret;

		val->intval = !!(reg & AXP20X_PWR_OP_BATT_PRESENT);
		break;

	case POWER_SUPPLY_PROP_STATUS:
		ret = regmap_read(axp20x_batt->regmap, AXP20X_PWR_INPUT_STATUS,
				  &reg);
		if (ret)
			return ret;

		if (reg & AXP20X_PWR_STATUS_BAT_CHARGING) {
			val->intval = POWER_SUPPLY_STATUS_CHARGING;
			return 0;
		}

		ret = iio_read_channel_processed(axp20x_batt->batt_dischrg_i,
						 &val1);
		if (ret)
			return ret;

		if (val1) {
			val->intval = POWER_SUPPLY_STATUS_DISCHARGING;
			return 0;
		}

		ret = regmap_read(axp20x_batt->regmap, AXP20X_FG_RES, &val1);
		if (ret)
			return ret;

		/*
		 * Fuel Gauge data takes 7 bits but the stored value seems to be
		 * directly the raw percentage without any scaling to 7 bits.
		 */
		if ((val1 & AXP209_FG_PERCENT) == 100)
			val->intval = POWER_SUPPLY_STATUS_FULL;
		else
			val->intval = POWER_SUPPLY_STATUS_NOT_CHARGING;
		break;

	case POWER_SUPPLY_PROP_HEALTH:
		ret = regmap_read(axp20x_batt->regmap, AXP20X_PWR_OP_MODE,
				  &val1);
		if (ret)
			return ret;

		if (val1 & AXP20X_PWR_OP_BATT_ACTIVATED) {
			val->intval = POWER_SUPPLY_HEALTH_DEAD;
			return 0;
		}

		val->intval = POWER_SUPPLY_HEALTH_GOOD;
		break;

	case POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT:
		ret = axp20x_get_constant_charge_current(axp20x_batt,
							 &val->intval);
		if (ret)
			return ret;
		break;

	case POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT_MAX:
		val->intval = axp20x_batt->max_ccc;
		break;

	case POWER_SUPPLY_PROP_CURRENT_NOW:
		ret = regmap_read(axp20x_batt->regmap, AXP20X_PWR_INPUT_STATUS,
				  &reg);
		if (ret)
			return ret;

		if (reg & AXP20X_PWR_STATUS_BAT_CHARGING)
			chan = axp20x_batt->batt_chrg_i;
		else
			chan = axp20x_batt->batt_dischrg_i;

		ret = iio_read_channel_processed(chan, &val->intval);
		if (ret)
			return ret;

		/* IIO framework gives mA but Power Supply framework gives uA */
		val->intval *= 1000;
		break;

	case POWER_SUPPLY_PROP_CAPACITY:
		/* When no battery is present, return capacity is 100% */
		ret = regmap_read(axp20x_batt->regmap, AXP20X_PWR_OP_MODE,
				  &reg);
		if (ret)
			return ret;

		if (!(reg & AXP20X_PWR_OP_BATT_PRESENT)) {
			val->intval = 100;
			return 0;
		}

		ret = regmap_read(axp20x_batt->regmap, AXP20X_FG_RES, &reg);
		if (ret)
			return ret;

		if (axp20x_batt->data->has_fg_valid && !(reg & AXP22X_FG_VALID))
			return -EINVAL;

		/*
		 * Fuel Gauge data takes 7 bits but the stored value seems to be
		 * directly the raw percentage without any scaling to 7 bits.
		 */
		val->intval = reg & AXP209_FG_PERCENT;
		break;

	case POWER_SUPPLY_PROP_VOLTAGE_MAX_DESIGN:
		return axp20x_batt->data->get_max_voltage(axp20x_batt,
							  &val->intval);

	case POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN:
		ret = regmap_read(axp20x_batt->regmap, AXP20X_V_OFF, &reg);
		if (ret)
			return ret;

		val->intval = 2600000 + 100000 * (reg & AXP20X_V_OFF_MASK);
		break;

	case POWER_SUPPLY_PROP_VOLTAGE_NOW:
		ret = iio_read_channel_processed(axp20x_batt->batt_v,
						 &val->intval);
		if (ret)
			return ret;

		/* IIO framework gives mV but Power Supply framework gives uV */
		val->intval *= 1000;
		break;

	default:
		return -EINVAL;
	}

	return 0;
}
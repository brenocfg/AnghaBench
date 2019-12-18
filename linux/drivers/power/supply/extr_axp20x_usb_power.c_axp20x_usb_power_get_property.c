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
struct axp20x_usb_power {int /*<<< orphan*/  regmap; int /*<<< orphan*/  axp20x_id; int /*<<< orphan*/  vbus_i; int /*<<< orphan*/  vbus_v; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int /*<<< orphan*/  AXP202_ID ; 
 int /*<<< orphan*/  AXP20X_PWR_INPUT_STATUS ; 
 unsigned int AXP20X_PWR_STATUS_VBUS_PRESENT ; 
 unsigned int AXP20X_PWR_STATUS_VBUS_USED ; 
 int /*<<< orphan*/  AXP20X_USB_OTG_STATUS ; 
 unsigned int AXP20X_USB_STATUS_VBUS_VALID ; 
 int /*<<< orphan*/  AXP20X_VBUS_IPSOUT_MGMT ; 
 int /*<<< orphan*/  AXP20X_VBUS_I_ADC_H ; 
 int AXP20X_VBUS_VHOLD_uV (unsigned int) ; 
 int /*<<< orphan*/  AXP20X_VBUS_V_ADC_H ; 
 int /*<<< orphan*/  AXP813_ID ; 
 int /*<<< orphan*/  CONFIG_AXP20X_ADC ; 
 int EINVAL ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int POWER_SUPPLY_HEALTH_GOOD ; 
 int POWER_SUPPLY_HEALTH_UNKNOWN ; 
 int POWER_SUPPLY_HEALTH_UNSPEC_FAILURE ; 
#define  POWER_SUPPLY_PROP_CURRENT_MAX 134 
#define  POWER_SUPPLY_PROP_CURRENT_NOW 133 
#define  POWER_SUPPLY_PROP_HEALTH 132 
#define  POWER_SUPPLY_PROP_ONLINE 131 
#define  POWER_SUPPLY_PROP_PRESENT 130 
#define  POWER_SUPPLY_PROP_VOLTAGE_MIN 129 
#define  POWER_SUPPLY_PROP_VOLTAGE_NOW 128 
 int axp20x_get_current_max (struct axp20x_usb_power*,int*) ; 
 int axp20x_read_variable_width (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int axp813_get_current_max (struct axp20x_usb_power*,int*) ; 
 int iio_read_channel_processed (int /*<<< orphan*/ ,int*) ; 
 struct axp20x_usb_power* power_supply_get_drvdata (struct power_supply*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int axp20x_usb_power_get_property(struct power_supply *psy,
	enum power_supply_property psp, union power_supply_propval *val)
{
	struct axp20x_usb_power *power = power_supply_get_drvdata(psy);
	unsigned int input, v;
	int ret;

	switch (psp) {
	case POWER_SUPPLY_PROP_VOLTAGE_MIN:
		ret = regmap_read(power->regmap, AXP20X_VBUS_IPSOUT_MGMT, &v);
		if (ret)
			return ret;

		val->intval = AXP20X_VBUS_VHOLD_uV(v);
		return 0;
	case POWER_SUPPLY_PROP_VOLTAGE_NOW:
		if (IS_ENABLED(CONFIG_AXP20X_ADC)) {
			ret = iio_read_channel_processed(power->vbus_v,
							 &val->intval);
			if (ret)
				return ret;

			/*
			 * IIO framework gives mV but Power Supply framework
			 * gives uV.
			 */
			val->intval *= 1000;
			return 0;
		}

		ret = axp20x_read_variable_width(power->regmap,
						 AXP20X_VBUS_V_ADC_H, 12);
		if (ret < 0)
			return ret;

		val->intval = ret * 1700; /* 1 step = 1.7 mV */
		return 0;
	case POWER_SUPPLY_PROP_CURRENT_MAX:
		if (power->axp20x_id == AXP813_ID)
			return axp813_get_current_max(power, &val->intval);
		return axp20x_get_current_max(power, &val->intval);
	case POWER_SUPPLY_PROP_CURRENT_NOW:
		if (IS_ENABLED(CONFIG_AXP20X_ADC)) {
			ret = iio_read_channel_processed(power->vbus_i,
							 &val->intval);
			if (ret)
				return ret;

			/*
			 * IIO framework gives mA but Power Supply framework
			 * gives uA.
			 */
			val->intval *= 1000;
			return 0;
		}

		ret = axp20x_read_variable_width(power->regmap,
						 AXP20X_VBUS_I_ADC_H, 12);
		if (ret < 0)
			return ret;

		val->intval = ret * 375; /* 1 step = 0.375 mA */
		return 0;
	default:
		break;
	}

	/* All the properties below need the input-status reg value */
	ret = regmap_read(power->regmap, AXP20X_PWR_INPUT_STATUS, &input);
	if (ret)
		return ret;

	switch (psp) {
	case POWER_SUPPLY_PROP_HEALTH:
		if (!(input & AXP20X_PWR_STATUS_VBUS_PRESENT)) {
			val->intval = POWER_SUPPLY_HEALTH_UNKNOWN;
			break;
		}

		val->intval = POWER_SUPPLY_HEALTH_GOOD;

		if (power->axp20x_id == AXP202_ID) {
			ret = regmap_read(power->regmap,
					  AXP20X_USB_OTG_STATUS, &v);
			if (ret)
				return ret;

			if (!(v & AXP20X_USB_STATUS_VBUS_VALID))
				val->intval =
					POWER_SUPPLY_HEALTH_UNSPEC_FAILURE;
		}
		break;
	case POWER_SUPPLY_PROP_PRESENT:
		val->intval = !!(input & AXP20X_PWR_STATUS_VBUS_PRESENT);
		break;
	case POWER_SUPPLY_PROP_ONLINE:
		val->intval = !!(input & AXP20X_PWR_STATUS_VBUS_USED);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}
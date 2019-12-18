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
struct power_supply {int dummy; } ;
struct axp20x_usb_power {int /*<<< orphan*/  axp20x_id; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int /*<<< orphan*/  AXP813_ID ; 
 int EINVAL ; 
#define  POWER_SUPPLY_PROP_CURRENT_MAX 129 
#define  POWER_SUPPLY_PROP_VOLTAGE_MIN 128 
 int axp20x_usb_power_set_current_max (struct axp20x_usb_power*,int /*<<< orphan*/ ) ; 
 int axp20x_usb_power_set_voltage_min (struct axp20x_usb_power*,int /*<<< orphan*/ ) ; 
 int axp813_usb_power_set_current_max (struct axp20x_usb_power*,int /*<<< orphan*/ ) ; 
 struct axp20x_usb_power* power_supply_get_drvdata (struct power_supply*) ; 

__attribute__((used)) static int axp20x_usb_power_set_property(struct power_supply *psy,
					 enum power_supply_property psp,
					 const union power_supply_propval *val)
{
	struct axp20x_usb_power *power = power_supply_get_drvdata(psy);

	switch (psp) {
	case POWER_SUPPLY_PROP_VOLTAGE_MIN:
		return axp20x_usb_power_set_voltage_min(power, val->intval);

	case POWER_SUPPLY_PROP_CURRENT_MAX:
		if (power->axp20x_id == AXP813_ID)
			return axp813_usb_power_set_current_max(power,
								val->intval);
		return axp20x_usb_power_set_current_max(power, val->intval);

	default:
		return -EINVAL;
	}

	return -EINVAL;
}
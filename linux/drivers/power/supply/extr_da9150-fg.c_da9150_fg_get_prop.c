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
typedef  union power_supply_propval {int dummy; } power_supply_propval ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct power_supply {TYPE_1__ dev; } ;
struct da9150_fg {int dummy; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int EINVAL ; 
#define  POWER_SUPPLY_PROP_CAPACITY 132 
#define  POWER_SUPPLY_PROP_CHARGE_FULL 131 
#define  POWER_SUPPLY_PROP_CURRENT_AVG 130 
#define  POWER_SUPPLY_PROP_TEMP 129 
#define  POWER_SUPPLY_PROP_VOLTAGE_AVG 128 
 int da9150_fg_capacity (struct da9150_fg*,union power_supply_propval*) ; 
 int da9150_fg_charge_full (struct da9150_fg*,union power_supply_propval*) ; 
 int da9150_fg_current_avg (struct da9150_fg*,union power_supply_propval*) ; 
 int da9150_fg_temp (struct da9150_fg*,union power_supply_propval*) ; 
 int da9150_fg_voltage_avg (struct da9150_fg*,union power_supply_propval*) ; 
 struct da9150_fg* dev_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int da9150_fg_get_prop(struct power_supply *psy,
			      enum power_supply_property psp,
			      union power_supply_propval *val)
{
	struct da9150_fg *fg = dev_get_drvdata(psy->dev.parent);
	int ret;

	switch (psp) {
	case POWER_SUPPLY_PROP_CAPACITY:
		ret = da9150_fg_capacity(fg, val);
		break;
	case POWER_SUPPLY_PROP_CURRENT_AVG:
		ret = da9150_fg_current_avg(fg, val);
		break;
	case POWER_SUPPLY_PROP_VOLTAGE_AVG:
		ret = da9150_fg_voltage_avg(fg, val);
		break;
	case POWER_SUPPLY_PROP_CHARGE_FULL:
		ret = da9150_fg_charge_full(fg, val);
		break;
	case POWER_SUPPLY_PROP_TEMP:
		ret = da9150_fg_temp(fg, val);
		break;
	default:
		ret = -EINVAL;
		break;
	}

	return ret;
}
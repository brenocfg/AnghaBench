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
union power_supply_propval {int /*<<< orphan*/  strval; int /*<<< orphan*/  intval; } ;
struct power_supply {int dummy; } ;
struct max14656_chip {int /*<<< orphan*/  online; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MAX14656_MANUFACTURER ; 
 int /*<<< orphan*/  MAX14656_NAME ; 
#define  POWER_SUPPLY_PROP_MANUFACTURER 130 
#define  POWER_SUPPLY_PROP_MODEL_NAME 129 
#define  POWER_SUPPLY_PROP_ONLINE 128 
 struct max14656_chip* power_supply_get_drvdata (struct power_supply*) ; 

__attribute__((used)) static int max14656_get_property(struct power_supply *psy,
			    enum power_supply_property psp,
			    union power_supply_propval *val)
{
	struct max14656_chip *chip = power_supply_get_drvdata(psy);

	switch (psp) {
	case POWER_SUPPLY_PROP_ONLINE:
		val->intval = chip->online;
		break;
	case POWER_SUPPLY_PROP_MODEL_NAME:
		val->strval = MAX14656_NAME;
		break;
	case POWER_SUPPLY_PROP_MANUFACTURER:
		val->strval = MAX14656_MANUFACTURER;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}
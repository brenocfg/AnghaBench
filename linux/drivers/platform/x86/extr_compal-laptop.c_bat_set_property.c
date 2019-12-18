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
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int /*<<< orphan*/  BAT_CHARGE_LIMIT ; 
 int BAT_CHARGE_LIMIT_MAX ; 
 int EINVAL ; 
 int EIO ; 
#define  POWER_SUPPLY_PROP_CHARGE_CONTROL_LIMIT 128 
 int /*<<< orphan*/  ec_write (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int bat_set_property(struct power_supply *psy,
				enum power_supply_property psp,
				const union power_supply_propval *val)
{
	int level;

	switch (psp) {
	case POWER_SUPPLY_PROP_CHARGE_CONTROL_LIMIT:
		level = val->intval;
		if (level < 0 || level > BAT_CHARGE_LIMIT_MAX)
			return -EINVAL;
		if (ec_write(BAT_CHARGE_LIMIT, level) < 0)
			return -EIO;
		break;
	default:
		break;
	}
	return 0;
}
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
struct bq24735 {int charging; int /*<<< orphan*/  lock; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
#define  POWER_SUPPLY_PROP_STATUS 131 
#define  POWER_SUPPLY_STATUS_CHARGING 130 
#define  POWER_SUPPLY_STATUS_DISCHARGING 129 
#define  POWER_SUPPLY_STATUS_NOT_CHARGING 128 
 int bq24735_disable_charging (struct bq24735*) ; 
 int bq24735_enable_charging (struct bq24735*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  power_supply_changed (struct power_supply*) ; 
 struct bq24735* to_bq24735 (struct power_supply*) ; 

__attribute__((used)) static int bq24735_charger_set_property(struct power_supply *psy,
					enum power_supply_property psp,
					const union power_supply_propval *val)
{
	struct bq24735 *charger = to_bq24735(psy);
	int ret;

	switch (psp) {
	case POWER_SUPPLY_PROP_STATUS:
		switch (val->intval) {
		case POWER_SUPPLY_STATUS_CHARGING:
			mutex_lock(&charger->lock);
			charger->charging = true;
			ret = bq24735_enable_charging(charger);
			mutex_unlock(&charger->lock);
			if (ret)
				return ret;
			break;
		case POWER_SUPPLY_STATUS_DISCHARGING:
		case POWER_SUPPLY_STATUS_NOT_CHARGING:
			mutex_lock(&charger->lock);
			charger->charging = false;
			ret = bq24735_disable_charging(charger);
			mutex_unlock(&charger->lock);
			if (ret)
				return ret;
			break;
		default:
			return -EINVAL;
		}
		power_supply_changed(psy);
		break;
	default:
		return -EPERM;
	}

	return 0;
}
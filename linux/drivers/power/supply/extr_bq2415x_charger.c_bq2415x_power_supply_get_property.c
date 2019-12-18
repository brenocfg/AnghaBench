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
struct bq2415x_device {int /*<<< orphan*/  model; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int /*<<< orphan*/  BQ2415X_CHARGE_STATUS ; 
 int EINVAL ; 
#define  POWER_SUPPLY_PROP_MODEL_NAME 129 
#define  POWER_SUPPLY_PROP_STATUS 128 
 int /*<<< orphan*/  POWER_SUPPLY_STATUS_CHARGING ; 
 int /*<<< orphan*/  POWER_SUPPLY_STATUS_FULL ; 
 int /*<<< orphan*/  POWER_SUPPLY_STATUS_NOT_CHARGING ; 
 int /*<<< orphan*/  POWER_SUPPLY_STATUS_UNKNOWN ; 
 int bq2415x_exec_command (struct bq2415x_device*,int /*<<< orphan*/ ) ; 
 struct bq2415x_device* power_supply_get_drvdata (struct power_supply*) ; 

__attribute__((used)) static int bq2415x_power_supply_get_property(struct power_supply *psy,
					     enum power_supply_property psp,
					     union power_supply_propval *val)
{
	struct bq2415x_device *bq = power_supply_get_drvdata(psy);
	int ret;

	switch (psp) {
	case POWER_SUPPLY_PROP_STATUS:
		ret = bq2415x_exec_command(bq, BQ2415X_CHARGE_STATUS);
		if (ret < 0)
			return ret;
		else if (ret == 0) /* Ready */
			val->intval = POWER_SUPPLY_STATUS_NOT_CHARGING;
		else if (ret == 1) /* Charge in progress */
			val->intval = POWER_SUPPLY_STATUS_CHARGING;
		else if (ret == 2) /* Charge done */
			val->intval = POWER_SUPPLY_STATUS_FULL;
		else
			val->intval = POWER_SUPPLY_STATUS_UNKNOWN;
		break;
	case POWER_SUPPLY_PROP_MODEL_NAME:
		val->strval = bq->model;
		break;
	default:
		return -EINVAL;
	}
	return 0;
}
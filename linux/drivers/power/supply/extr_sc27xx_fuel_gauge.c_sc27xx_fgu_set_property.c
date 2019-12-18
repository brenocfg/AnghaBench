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
struct sc27xx_fgu_data {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; } ;
struct power_supply {int dummy; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int EINVAL ; 
#define  POWER_SUPPLY_PROP_CALIBRATE 129 
#define  POWER_SUPPLY_PROP_CAPACITY 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct sc27xx_fgu_data* power_supply_get_drvdata (struct power_supply*) ; 
 int /*<<< orphan*/  sc27xx_fgu_adjust_cap (struct sc27xx_fgu_data*,int /*<<< orphan*/ ) ; 
 int sc27xx_fgu_save_last_cap (struct sc27xx_fgu_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sc27xx_fgu_set_property(struct power_supply *psy,
				   enum power_supply_property psp,
				   const union power_supply_propval *val)
{
	struct sc27xx_fgu_data *data = power_supply_get_drvdata(psy);
	int ret;

	mutex_lock(&data->lock);

	switch (psp) {
	case POWER_SUPPLY_PROP_CAPACITY:
		ret = sc27xx_fgu_save_last_cap(data, val->intval);
		if (ret < 0)
			dev_err(data->dev, "failed to save battery capacity\n");
		break;

	case POWER_SUPPLY_PROP_CALIBRATE:
		sc27xx_fgu_adjust_cap(data, val->intval);
		ret = 0;
		break;

	default:
		ret = -EINVAL;
	}

	mutex_unlock(&data->lock);

	return ret;
}
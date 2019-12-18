#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct gb_power_supply_prop {scalar_t__ val; } ;
struct gb_power_supply {int pm_acquired; int /*<<< orphan*/  supply_lock; } ;
struct gb_connection {TYPE_1__* bundle; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ GB_POWER_SUPPLY_STATUS_CHARGING ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int gb_pm_runtime_get_sync (TYPE_1__*) ; 
 int gb_pm_runtime_put_autosuspend (TYPE_1__*) ; 
 struct gb_connection* get_conn_from_psy (struct gb_power_supply*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gb_power_supply_state_change(struct gb_power_supply *gbpsy,
					 struct gb_power_supply_prop *prop)
{
	struct gb_connection *connection = get_conn_from_psy(gbpsy);
	int ret;

	/*
	 * Check gbpsy->pm_acquired to make sure only one pair of 'get_sync'
	 * and 'put_autosuspend' runtime pm call for state property change.
	 */
	mutex_lock(&gbpsy->supply_lock);

	if ((prop->val == GB_POWER_SUPPLY_STATUS_CHARGING) &&
	    !gbpsy->pm_acquired) {
		ret = gb_pm_runtime_get_sync(connection->bundle);
		if (ret)
			dev_err(&connection->bundle->dev,
				"Fail to set wake lock for charging state\n");
		else
			gbpsy->pm_acquired = true;
	} else {
		if (gbpsy->pm_acquired) {
			ret = gb_pm_runtime_put_autosuspend(connection->bundle);
			if (ret)
				dev_err(&connection->bundle->dev,
					"Fail to set wake unlock for none charging\n");
			else
				gbpsy->pm_acquired = false;
		}
	}

	mutex_unlock(&gbpsy->supply_lock);
}
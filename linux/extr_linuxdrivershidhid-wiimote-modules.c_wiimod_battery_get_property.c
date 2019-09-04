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
struct TYPE_2__ {int cmd_battery; int /*<<< orphan*/  lock; } ;
struct wiimote_data {TYPE_1__ state; } ;
struct power_supply {int dummy; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int EINVAL ; 
 int POWER_SUPPLY_PROP_CAPACITY ; 
 int POWER_SUPPLY_PROP_SCOPE ; 
 int POWER_SUPPLY_SCOPE_DEVICE ; 
 int /*<<< orphan*/  WIIPROTO_REQ_SREQ ; 
 struct wiimote_data* power_supply_get_drvdata (struct power_supply*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int wiimote_cmd_acquire (struct wiimote_data*) ; 
 int /*<<< orphan*/  wiimote_cmd_release (struct wiimote_data*) ; 
 int /*<<< orphan*/  wiimote_cmd_set (struct wiimote_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wiimote_cmd_wait (struct wiimote_data*) ; 
 int /*<<< orphan*/  wiiproto_req_status (struct wiimote_data*) ; 

__attribute__((used)) static int wiimod_battery_get_property(struct power_supply *psy,
				       enum power_supply_property psp,
				       union power_supply_propval *val)
{
	struct wiimote_data *wdata = power_supply_get_drvdata(psy);
	int ret = 0, state;
	unsigned long flags;

	if (psp == POWER_SUPPLY_PROP_SCOPE) {
		val->intval = POWER_SUPPLY_SCOPE_DEVICE;
		return 0;
	} else if (psp != POWER_SUPPLY_PROP_CAPACITY) {
		return -EINVAL;
	}

	ret = wiimote_cmd_acquire(wdata);
	if (ret)
		return ret;

	spin_lock_irqsave(&wdata->state.lock, flags);
	wiimote_cmd_set(wdata, WIIPROTO_REQ_SREQ, 0);
	wiiproto_req_status(wdata);
	spin_unlock_irqrestore(&wdata->state.lock, flags);

	wiimote_cmd_wait(wdata);
	wiimote_cmd_release(wdata);

	spin_lock_irqsave(&wdata->state.lock, flags);
	state = wdata->state.cmd_battery;
	spin_unlock_irqrestore(&wdata->state.lock, flags);

	val->intval = state * 100 / 255;
	return ret;
}
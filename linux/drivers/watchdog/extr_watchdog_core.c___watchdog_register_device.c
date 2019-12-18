#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  notifier_call; } ;
struct watchdog_device {int id; TYPE_3__ restart_nb; TYPE_2__* ops; TYPE_1__* parent; int /*<<< orphan*/  max_hw_heartbeat_ms; int /*<<< orphan*/ * info; } ;
struct TYPE_5__ {scalar_t__ restart; int /*<<< orphan*/  stop; int /*<<< orphan*/  start; } ;
struct TYPE_4__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MAX_DOGS ; 
 int ida_simple_get (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int) ; 
 int of_alias_get_id (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pr_warn (char*,int,int) ; 
 int register_restart_handler (TYPE_3__*) ; 
 int /*<<< orphan*/  watchdog_check_min_max_timeout (struct watchdog_device*) ; 
 int watchdog_dev_register (struct watchdog_device*) ; 
 int /*<<< orphan*/  watchdog_ida ; 
 int /*<<< orphan*/  watchdog_restart_notifier ; 

__attribute__((used)) static int __watchdog_register_device(struct watchdog_device *wdd)
{
	int ret, id = -1;

	if (wdd == NULL || wdd->info == NULL || wdd->ops == NULL)
		return -EINVAL;

	/* Mandatory operations need to be supported */
	if (!wdd->ops->start || (!wdd->ops->stop && !wdd->max_hw_heartbeat_ms))
		return -EINVAL;

	watchdog_check_min_max_timeout(wdd);

	/*
	 * Note: now that all watchdog_device data has been verified, we
	 * will not check this anymore in other functions. If data gets
	 * corrupted in a later stage then we expect a kernel panic!
	 */

	/* Use alias for watchdog id if possible */
	if (wdd->parent) {
		ret = of_alias_get_id(wdd->parent->of_node, "watchdog");
		if (ret >= 0)
			id = ida_simple_get(&watchdog_ida, ret,
					    ret + 1, GFP_KERNEL);
	}

	if (id < 0)
		id = ida_simple_get(&watchdog_ida, 0, MAX_DOGS, GFP_KERNEL);

	if (id < 0)
		return id;
	wdd->id = id;

	ret = watchdog_dev_register(wdd);
	if (ret) {
		ida_simple_remove(&watchdog_ida, id);
		if (!(id == 0 && ret == -EBUSY))
			return ret;

		/* Retry in case a legacy watchdog module exists */
		id = ida_simple_get(&watchdog_ida, 1, MAX_DOGS, GFP_KERNEL);
		if (id < 0)
			return id;
		wdd->id = id;

		ret = watchdog_dev_register(wdd);
		if (ret) {
			ida_simple_remove(&watchdog_ida, id);
			return ret;
		}
	}

	if (wdd->ops->restart) {
		wdd->restart_nb.notifier_call = watchdog_restart_notifier;

		ret = register_restart_handler(&wdd->restart_nb);
		if (ret)
			pr_warn("watchdog%d: Cannot register restart handler (%d)\n",
				wdd->id, ret);
	}

	return 0;
}
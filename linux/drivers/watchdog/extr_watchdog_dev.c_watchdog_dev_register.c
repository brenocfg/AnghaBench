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
struct TYPE_2__ {int /*<<< orphan*/  notifier_call; } ;
struct watchdog_device {int /*<<< orphan*/  id; TYPE_1__ reboot_nb; int /*<<< orphan*/  status; int /*<<< orphan*/  groups; int /*<<< orphan*/  parent; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct device*) ; 
 int /*<<< orphan*/  MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PTR_ERR (struct device*) ; 
 int /*<<< orphan*/  WDOG_STOP_ON_REBOOT ; 
 struct device* device_create_with_groups (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct watchdog_device*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int devm_register_reboot_notifier (struct device*,TYPE_1__*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int watchdog_cdev_register (struct watchdog_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  watchdog_cdev_unregister (struct watchdog_device*) ; 
 int /*<<< orphan*/  watchdog_class ; 
 int /*<<< orphan*/  watchdog_dev_unregister (struct watchdog_device*) ; 
 int /*<<< orphan*/  watchdog_devt ; 
 int /*<<< orphan*/  watchdog_reboot_notifier ; 
 int watchdog_register_pretimeout (struct watchdog_device*) ; 

int watchdog_dev_register(struct watchdog_device *wdd)
{
	struct device *dev;
	dev_t devno;
	int ret;

	devno = MKDEV(MAJOR(watchdog_devt), wdd->id);

	ret = watchdog_cdev_register(wdd, devno);
	if (ret)
		return ret;

	dev = device_create_with_groups(&watchdog_class, wdd->parent,
					devno, wdd, wdd->groups,
					"watchdog%d", wdd->id);
	if (IS_ERR(dev)) {
		watchdog_cdev_unregister(wdd);
		return PTR_ERR(dev);
	}

	ret = watchdog_register_pretimeout(wdd);
	if (ret) {
		device_destroy(&watchdog_class, devno);
		watchdog_cdev_unregister(wdd);
		return ret;
	}

	if (test_bit(WDOG_STOP_ON_REBOOT, &wdd->status)) {
		wdd->reboot_nb.notifier_call = watchdog_reboot_notifier;

		ret = devm_register_reboot_notifier(dev, &wdd->reboot_nb);
		if (ret) {
			pr_err("watchdog%d: Cannot register reboot notifier (%d)\n",
			       wdd->id, ret);
			watchdog_dev_unregister(wdd);
		}
	}

	return ret;
}
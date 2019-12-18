#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  max_timeout; int /*<<< orphan*/  min_timeout; int /*<<< orphan*/  timeout; struct device* parent; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * info; } ;
struct mei_wdt {int /*<<< orphan*/  reg_lock; int /*<<< orphan*/  state; TYPE_2__ wdd; TYPE_1__* cldev; } ;
struct device {int dummy; } ;
struct TYPE_5__ {struct device dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MEI_WDT_DEFAULT_TIMEOUT ; 
 int /*<<< orphan*/  MEI_WDT_IDLE ; 
 int /*<<< orphan*/  MEI_WDT_MAX_TIMEOUT ; 
 int /*<<< orphan*/  MEI_WDT_MIN_TIMEOUT ; 
 scalar_t__ __mei_wdt_is_registered (struct mei_wdt*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int watchdog_register_device (TYPE_2__*) ; 
 int /*<<< orphan*/  watchdog_set_drvdata (TYPE_2__*,struct mei_wdt*) ; 
 int /*<<< orphan*/  watchdog_stop_on_reboot (TYPE_2__*) ; 
 int /*<<< orphan*/  wd_info ; 
 int /*<<< orphan*/  wd_ops ; 

__attribute__((used)) static int mei_wdt_register(struct mei_wdt *wdt)
{
	struct device *dev;
	int ret;

	if (!wdt || !wdt->cldev)
		return -EINVAL;

	dev = &wdt->cldev->dev;

	mutex_lock(&wdt->reg_lock);

	if (__mei_wdt_is_registered(wdt)) {
		ret = 0;
		goto out;
	}

	wdt->wdd.info = &wd_info;
	wdt->wdd.ops = &wd_ops;
	wdt->wdd.parent = dev;
	wdt->wdd.timeout = MEI_WDT_DEFAULT_TIMEOUT;
	wdt->wdd.min_timeout = MEI_WDT_MIN_TIMEOUT;
	wdt->wdd.max_timeout = MEI_WDT_MAX_TIMEOUT;

	watchdog_set_drvdata(&wdt->wdd, wdt);
	watchdog_stop_on_reboot(&wdt->wdd);

	ret = watchdog_register_device(&wdt->wdd);
	if (ret)
		watchdog_set_drvdata(&wdt->wdd, NULL);

	wdt->state = MEI_WDT_IDLE;

out:
	mutex_unlock(&wdt->reg_lock);
	return ret;
}
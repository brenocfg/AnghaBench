#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct device {int /*<<< orphan*/  parent; } ;
struct platform_device {struct device dev; } ;
struct TYPE_5__ {struct device* parent; int /*<<< orphan*/  status; int /*<<< orphan*/  timeout; int /*<<< orphan*/  min_hw_heartbeat_ms; int /*<<< orphan*/  max_timeout; int /*<<< orphan*/  min_timeout; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * info; } ;
struct da9062_watchdog {TYPE_1__ wdtdev; struct da9062* hw; } ;
struct da9062 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA9062_RESET_PROTECTION_MS ; 
 int /*<<< orphan*/  DA9062_WDG_DEFAULT_TIMEOUT ; 
 int /*<<< orphan*/  DA9062_WDT_MAX_TIMEOUT ; 
 int /*<<< orphan*/  DA9062_WDT_MIN_TIMEOUT ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WATCHDOG_NOWAYOUT_INIT_STATUS ; 
 int /*<<< orphan*/  da9062_watchdog_info ; 
 int /*<<< orphan*/  da9062_watchdog_ops ; 
 int da9062_wdt_ping (TYPE_1__*) ; 
 struct da9062* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct da9062_watchdog* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_watchdog_register_device (struct device*,TYPE_1__*) ; 
 int /*<<< orphan*/  watchdog_set_drvdata (TYPE_1__*,struct da9062_watchdog*) ; 
 int /*<<< orphan*/  watchdog_set_restart_priority (TYPE_1__*,int) ; 

__attribute__((used)) static int da9062_wdt_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	int ret;
	struct da9062 *chip;
	struct da9062_watchdog *wdt;

	chip = dev_get_drvdata(dev->parent);
	if (!chip)
		return -EINVAL;

	wdt = devm_kzalloc(dev, sizeof(*wdt), GFP_KERNEL);
	if (!wdt)
		return -ENOMEM;

	wdt->hw = chip;

	wdt->wdtdev.info = &da9062_watchdog_info;
	wdt->wdtdev.ops = &da9062_watchdog_ops;
	wdt->wdtdev.min_timeout = DA9062_WDT_MIN_TIMEOUT;
	wdt->wdtdev.max_timeout = DA9062_WDT_MAX_TIMEOUT;
	wdt->wdtdev.min_hw_heartbeat_ms = DA9062_RESET_PROTECTION_MS;
	wdt->wdtdev.timeout = DA9062_WDG_DEFAULT_TIMEOUT;
	wdt->wdtdev.status = WATCHDOG_NOWAYOUT_INIT_STATUS;
	wdt->wdtdev.parent = dev;

	watchdog_set_restart_priority(&wdt->wdtdev, 128);

	watchdog_set_drvdata(&wdt->wdtdev, wdt);

	ret = devm_watchdog_register_device(dev, &wdt->wdtdev);
	if (ret < 0)
		return ret;

	return da9062_wdt_ping(&wdt->wdtdev);
}
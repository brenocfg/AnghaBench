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
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct TYPE_5__ {int max_timeout; struct device* parent; int /*<<< orphan*/  timeout; int /*<<< orphan*/  min_timeout; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * info; } ;
struct bcm7038_watchdog {int rate; TYPE_1__ wdd; int /*<<< orphan*/ * clk; int /*<<< orphan*/ * base; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 void* WDT_DEFAULT_RATE ; 
 int /*<<< orphan*/  WDT_DEFAULT_TIMEOUT ; 
 int /*<<< orphan*/  WDT_MIN_TIMEOUT ; 
 int /*<<< orphan*/  bcm7038_clk_disable_unprepare ; 
 int /*<<< orphan*/  bcm7038_wdt_info ; 
 int /*<<< orphan*/  bcm7038_wdt_ops ; 
 int clk_get_rate (int /*<<< orphan*/ *) ; 
 int clk_prepare_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int devm_add_action_or_reset (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * devm_clk_get (struct device*,int /*<<< orphan*/ *) ; 
 struct bcm7038_watchdog* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int devm_watchdog_register_device (struct device*,TYPE_1__*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct bcm7038_watchdog*) ; 
 int /*<<< orphan*/  watchdog_set_drvdata (TYPE_1__*,struct bcm7038_watchdog*) ; 
 int /*<<< orphan*/  watchdog_stop_on_reboot (TYPE_1__*) ; 
 int /*<<< orphan*/  watchdog_stop_on_unregister (TYPE_1__*) ; 

__attribute__((used)) static int bcm7038_wdt_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct bcm7038_watchdog *wdt;
	int err;

	wdt = devm_kzalloc(dev, sizeof(*wdt), GFP_KERNEL);
	if (!wdt)
		return -ENOMEM;

	platform_set_drvdata(pdev, wdt);

	wdt->base = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(wdt->base))
		return PTR_ERR(wdt->base);

	wdt->clk = devm_clk_get(dev, NULL);
	/* If unable to get clock, use default frequency */
	if (!IS_ERR(wdt->clk)) {
		err = clk_prepare_enable(wdt->clk);
		if (err)
			return err;
		err = devm_add_action_or_reset(dev,
					       bcm7038_clk_disable_unprepare,
					       wdt->clk);
		if (err)
			return err;
		wdt->rate = clk_get_rate(wdt->clk);
		/* Prevent divide-by-zero exception */
		if (!wdt->rate)
			wdt->rate = WDT_DEFAULT_RATE;
	} else {
		wdt->rate = WDT_DEFAULT_RATE;
		wdt->clk = NULL;
	}

	wdt->wdd.info		= &bcm7038_wdt_info;
	wdt->wdd.ops		= &bcm7038_wdt_ops;
	wdt->wdd.min_timeout	= WDT_MIN_TIMEOUT;
	wdt->wdd.timeout	= WDT_DEFAULT_TIMEOUT;
	wdt->wdd.max_timeout	= 0xffffffff / wdt->rate;
	wdt->wdd.parent		= dev;
	watchdog_set_drvdata(&wdt->wdd, wdt);

	watchdog_stop_on_reboot(&wdt->wdd);
	watchdog_stop_on_unregister(&wdt->wdd);
	err = devm_watchdog_register_device(dev, &wdt->wdd);
	if (err)
		return err;

	dev_info(dev, "Registered BCM7038 Watchdog\n");

	return 0;
}
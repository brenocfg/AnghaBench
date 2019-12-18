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
struct watchdog_device {int timeout; int min_timeout; int max_timeout; struct device* parent; scalar_t__ status; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * info; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct watchdog_device* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_watchdog_register_device (struct device*,struct watchdog_device*) ; 
 int /*<<< orphan*/  nowayout ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct watchdog_device*) ; 
 int /*<<< orphan*/  twl4030_wdt_info ; 
 int /*<<< orphan*/  twl4030_wdt_ops ; 
 int /*<<< orphan*/  twl4030_wdt_stop (struct watchdog_device*) ; 
 int /*<<< orphan*/  watchdog_set_nowayout (struct watchdog_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int twl4030_wdt_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct watchdog_device *wdt;

	wdt = devm_kzalloc(dev, sizeof(*wdt), GFP_KERNEL);
	if (!wdt)
		return -ENOMEM;

	wdt->info		= &twl4030_wdt_info;
	wdt->ops		= &twl4030_wdt_ops;
	wdt->status		= 0;
	wdt->timeout		= 30;
	wdt->min_timeout	= 1;
	wdt->max_timeout	= 30;
	wdt->parent = dev;

	watchdog_set_nowayout(wdt, nowayout);
	platform_set_drvdata(pdev, wdt);

	twl4030_wdt_stop(wdt);

	return devm_watchdog_register_device(dev, wdt);
}
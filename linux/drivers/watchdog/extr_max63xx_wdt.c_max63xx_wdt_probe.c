#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct platform_device {TYPE_1__* id_entry; struct device dev; } ;
struct TYPE_8__ {int /*<<< orphan*/ * ops; int /*<<< orphan*/ * info; int /*<<< orphan*/  timeout; struct device* parent; } ;
struct max63xx_wdt {TYPE_5__* timeout; TYPE_2__ wdd; } ;
struct max63xx_timeout {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  tdelay; int /*<<< orphan*/  twd; } ;
struct TYPE_7__ {scalar_t__ driver_data; } ;

/* Variables and functions */
 int DEFAULT_HEARTBEAT ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MAX_HEARTBEAT ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct max63xx_wdt* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_watchdog_register_device (struct device*,TYPE_2__*) ; 
 int heartbeat ; 
 int max63xx_mmap_init (struct platform_device*,struct max63xx_wdt*) ; 
 TYPE_5__* max63xx_select_timeout (struct max63xx_timeout*,int) ; 
 int /*<<< orphan*/  max63xx_wdt_info ; 
 int /*<<< orphan*/  max63xx_wdt_ops ; 
 int /*<<< orphan*/  nowayout ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,TYPE_2__*) ; 
 int /*<<< orphan*/  watchdog_set_drvdata (TYPE_2__*,struct max63xx_wdt*) ; 
 int /*<<< orphan*/  watchdog_set_nowayout (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int max63xx_wdt_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct max63xx_wdt *wdt;
	struct max63xx_timeout *table;
	int err;

	wdt = devm_kzalloc(dev, sizeof(*wdt), GFP_KERNEL);
	if (!wdt)
		return -ENOMEM;

	table = (struct max63xx_timeout *)pdev->id_entry->driver_data;

	if (heartbeat < 1 || heartbeat > MAX_HEARTBEAT)
		heartbeat = DEFAULT_HEARTBEAT;

	wdt->timeout = max63xx_select_timeout(table, heartbeat);
	if (!wdt->timeout) {
		dev_err(dev, "unable to satisfy %ds heartbeat request\n",
			heartbeat);
		return -EINVAL;
	}

	err = max63xx_mmap_init(pdev, wdt);
	if (err)
		return err;

	platform_set_drvdata(pdev, &wdt->wdd);
	watchdog_set_drvdata(&wdt->wdd, wdt);

	wdt->wdd.parent = dev;
	wdt->wdd.timeout = wdt->timeout->twd;
	wdt->wdd.info = &max63xx_wdt_info;
	wdt->wdd.ops = &max63xx_wdt_ops;

	watchdog_set_nowayout(&wdt->wdd, nowayout);

	err = devm_watchdog_register_device(dev, &wdt->wdd);
	if (err)
		return err;

	dev_info(dev, "using %ds heartbeat with %ds initial delay\n",
		 wdt->timeout->twd, wdt->timeout->tdelay);
	return 0;
}
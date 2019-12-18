#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  expires; } ;
struct sh_wdt {TYPE_4__ timer; int /*<<< orphan*/  lock; int /*<<< orphan*/ * base; int /*<<< orphan*/ * clk; int /*<<< orphan*/ * dev; } ;
struct platform_device {int id; int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  timeout; int /*<<< orphan*/ * parent; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WATCHDOG_HEARTBEAT ; 
 int /*<<< orphan*/  clock_division_ratio ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * devm_clk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct sh_wdt* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heartbeat ; 
 int /*<<< orphan*/  next_ping_period (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nowayout ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ *) ; 
 TYPE_1__ sh_wdt_dev ; 
 int /*<<< orphan*/  sh_wdt_ping ; 
 int sh_wdt_set_heartbeat (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int watchdog_register_device (TYPE_1__*) ; 
 int /*<<< orphan*/  watchdog_set_drvdata (TYPE_1__*,struct sh_wdt*) ; 
 int /*<<< orphan*/  watchdog_set_nowayout (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sh_wdt_probe(struct platform_device *pdev)
{
	struct sh_wdt *wdt;
	int rc;

	/*
	 * As this driver only covers the global watchdog case, reject
	 * any attempts to register per-CPU watchdogs.
	 */
	if (pdev->id != -1)
		return -EINVAL;

	wdt = devm_kzalloc(&pdev->dev, sizeof(struct sh_wdt), GFP_KERNEL);
	if (unlikely(!wdt))
		return -ENOMEM;

	wdt->dev = &pdev->dev;

	wdt->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(wdt->clk)) {
		/*
		 * Clock framework support is optional, continue on
		 * anyways if we don't find a matching clock.
		 */
		wdt->clk = NULL;
	}

	wdt->base = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(wdt->base))
		return PTR_ERR(wdt->base);

	watchdog_set_nowayout(&sh_wdt_dev, nowayout);
	watchdog_set_drvdata(&sh_wdt_dev, wdt);
	sh_wdt_dev.parent = &pdev->dev;

	spin_lock_init(&wdt->lock);

	rc = sh_wdt_set_heartbeat(&sh_wdt_dev, heartbeat);
	if (unlikely(rc)) {
		/* Default timeout if invalid */
		sh_wdt_set_heartbeat(&sh_wdt_dev, WATCHDOG_HEARTBEAT);

		dev_warn(&pdev->dev,
			 "heartbeat value must be 1<=x<=3600, using %d\n",
			 sh_wdt_dev.timeout);
	}

	dev_info(&pdev->dev, "configured with heartbeat=%d sec (nowayout=%d)\n",
		 sh_wdt_dev.timeout, nowayout);

	rc = watchdog_register_device(&sh_wdt_dev);
	if (unlikely(rc)) {
		dev_err(&pdev->dev, "Can't register watchdog (err=%d)\n", rc);
		return rc;
	}

	timer_setup(&wdt->timer, sh_wdt_ping, 0);
	wdt->timer.expires	= next_ping_period(clock_division_ratio);

	dev_info(&pdev->dev, "initialized.\n");

	pm_runtime_enable(&pdev->dev);

	return 0;
}
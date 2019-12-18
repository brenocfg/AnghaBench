#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_8__ {int min_timeout; int max_hw_heartbeat_ms; int /*<<< orphan*/  status; int /*<<< orphan*/  timeout; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * info; int /*<<< orphan*/ * parent; } ;
struct tangox_wdt_device {int clk_rate; TYPE_1__ wdt; scalar_t__ base; scalar_t__ clk; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_TIMEOUT ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 int U32_MAX ; 
 int /*<<< orphan*/  WDOG_HW_RUNNING ; 
 scalar_t__ WD_CONFIG ; 
 int WD_CONFIG_DISABLE ; 
 int /*<<< orphan*/  WD_CONFIG_XTAL_IN ; 
 scalar_t__ WD_COUNTER ; 
 int clk_get_rate (scalar_t__) ; 
 int clk_prepare_enable (scalar_t__) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int devm_add_action_or_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ devm_clk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct tangox_wdt_device* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int devm_watchdog_register_device (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  nowayout ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct tangox_wdt_device*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tangox_clk_disable_unprepare ; 
 int /*<<< orphan*/  tangox_wdt_info ; 
 int /*<<< orphan*/  tangox_wdt_ops ; 
 int /*<<< orphan*/  tangox_wdt_start (TYPE_1__*) ; 
 int /*<<< orphan*/  timeout ; 
 int /*<<< orphan*/  watchdog_init_timeout (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  watchdog_set_drvdata (TYPE_1__*,struct tangox_wdt_device*) ; 
 int /*<<< orphan*/  watchdog_set_nowayout (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  watchdog_set_restart_priority (TYPE_1__*,int) ; 
 int /*<<< orphan*/  watchdog_stop_on_unregister (TYPE_1__*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int tangox_wdt_probe(struct platform_device *pdev)
{
	struct tangox_wdt_device *dev;
	u32 config;
	int err;

	dev = devm_kzalloc(&pdev->dev, sizeof(*dev), GFP_KERNEL);
	if (!dev)
		return -ENOMEM;

	dev->base = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(dev->base))
		return PTR_ERR(dev->base);

	dev->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(dev->clk))
		return PTR_ERR(dev->clk);

	err = clk_prepare_enable(dev->clk);
	if (err)
		return err;
	err = devm_add_action_or_reset(&pdev->dev,
				       tangox_clk_disable_unprepare, dev->clk);
	if (err)
		return err;

	dev->clk_rate = clk_get_rate(dev->clk);
	if (!dev->clk_rate)
		return -EINVAL;

	dev->wdt.parent = &pdev->dev;
	dev->wdt.info = &tangox_wdt_info;
	dev->wdt.ops = &tangox_wdt_ops;
	dev->wdt.timeout = DEFAULT_TIMEOUT;
	dev->wdt.min_timeout = 1;
	dev->wdt.max_hw_heartbeat_ms = (U32_MAX - 1) / dev->clk_rate;

	watchdog_init_timeout(&dev->wdt, timeout, &pdev->dev);
	watchdog_set_nowayout(&dev->wdt, nowayout);
	watchdog_set_drvdata(&dev->wdt, dev);

	/*
	 * Deactivate counter if disable bit is set to avoid
	 * accidental reset.
	 */
	config = readl(dev->base + WD_CONFIG);
	if (config & WD_CONFIG_DISABLE)
		writel(0, dev->base + WD_COUNTER);

	writel(WD_CONFIG_XTAL_IN, dev->base + WD_CONFIG);

	/*
	 * Mark as active and restart with configured timeout if
	 * already running.
	 */
	if (readl(dev->base + WD_COUNTER)) {
		set_bit(WDOG_HW_RUNNING, &dev->wdt.status);
		tangox_wdt_start(&dev->wdt);
	}

	watchdog_set_restart_priority(&dev->wdt, 128);

	watchdog_stop_on_unregister(&dev->wdt);
	err = devm_watchdog_register_device(&pdev->dev, &dev->wdt);
	if (err)
		return err;

	platform_set_drvdata(pdev, dev);

	dev_info(&pdev->dev, "SMP86xx/SMP87xx watchdog registered\n");

	return 0;
}
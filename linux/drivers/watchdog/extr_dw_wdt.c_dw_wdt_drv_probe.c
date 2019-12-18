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
struct watchdog_device {int min_timeout; int max_hw_heartbeat_ms; int /*<<< orphan*/  timeout; int /*<<< orphan*/  status; struct device* parent; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * info; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct dw_wdt {scalar_t__ rate; int /*<<< orphan*/  clk; struct watchdog_device wdd; int /*<<< orphan*/  rst; int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DW_WDT_DEFAULT_SECONDS ; 
 int /*<<< orphan*/  DW_WDT_MAX_TOP ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WDOG_HW_RUNNING ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 scalar_t__ clk_get_rate (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,int /*<<< orphan*/ *) ; 
 struct dw_wdt* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_reset_control_get_optional_shared (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dw_wdt_get_top (struct dw_wdt*) ; 
 int /*<<< orphan*/  dw_wdt_ident ; 
 scalar_t__ dw_wdt_is_enabled (struct dw_wdt*) ; 
 int /*<<< orphan*/  dw_wdt_ops ; 
 int dw_wdt_top_in_seconds (struct dw_wdt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nowayout ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct dw_wdt*) ; 
 int /*<<< orphan*/  reset_control_deassert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  watchdog_init_timeout (struct watchdog_device*,int /*<<< orphan*/ ,struct device*) ; 
 int watchdog_register_device (struct watchdog_device*) ; 
 int /*<<< orphan*/  watchdog_set_drvdata (struct watchdog_device*,struct dw_wdt*) ; 
 int /*<<< orphan*/  watchdog_set_nowayout (struct watchdog_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  watchdog_set_restart_priority (struct watchdog_device*,int) ; 

__attribute__((used)) static int dw_wdt_drv_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct watchdog_device *wdd;
	struct dw_wdt *dw_wdt;
	int ret;

	dw_wdt = devm_kzalloc(dev, sizeof(*dw_wdt), GFP_KERNEL);
	if (!dw_wdt)
		return -ENOMEM;

	dw_wdt->regs = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(dw_wdt->regs))
		return PTR_ERR(dw_wdt->regs);

	dw_wdt->clk = devm_clk_get(dev, NULL);
	if (IS_ERR(dw_wdt->clk))
		return PTR_ERR(dw_wdt->clk);

	ret = clk_prepare_enable(dw_wdt->clk);
	if (ret)
		return ret;

	dw_wdt->rate = clk_get_rate(dw_wdt->clk);
	if (dw_wdt->rate == 0) {
		ret = -EINVAL;
		goto out_disable_clk;
	}

	dw_wdt->rst = devm_reset_control_get_optional_shared(&pdev->dev, NULL);
	if (IS_ERR(dw_wdt->rst)) {
		ret = PTR_ERR(dw_wdt->rst);
		goto out_disable_clk;
	}

	reset_control_deassert(dw_wdt->rst);

	wdd = &dw_wdt->wdd;
	wdd->info = &dw_wdt_ident;
	wdd->ops = &dw_wdt_ops;
	wdd->min_timeout = 1;
	wdd->max_hw_heartbeat_ms =
		dw_wdt_top_in_seconds(dw_wdt, DW_WDT_MAX_TOP) * 1000;
	wdd->parent = dev;

	watchdog_set_drvdata(wdd, dw_wdt);
	watchdog_set_nowayout(wdd, nowayout);
	watchdog_init_timeout(wdd, 0, dev);

	/*
	 * If the watchdog is already running, use its already configured
	 * timeout. Otherwise use the default or the value provided through
	 * devicetree.
	 */
	if (dw_wdt_is_enabled(dw_wdt)) {
		wdd->timeout = dw_wdt_get_top(dw_wdt);
		set_bit(WDOG_HW_RUNNING, &wdd->status);
	} else {
		wdd->timeout = DW_WDT_DEFAULT_SECONDS;
		watchdog_init_timeout(wdd, 0, dev);
	}

	platform_set_drvdata(pdev, dw_wdt);

	watchdog_set_restart_priority(wdd, 128);

	ret = watchdog_register_device(wdd);
	if (ret)
		goto out_disable_clk;

	return 0;

out_disable_clk:
	clk_disable_unprepare(dw_wdt->clk);
	return ret;
}
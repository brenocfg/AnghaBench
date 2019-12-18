#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct dc_wdt {int /*<<< orphan*/  lock; int /*<<< orphan*/  clk; int /*<<< orphan*/  base; } ;
struct TYPE_7__ {int max_timeout; int timeout; struct device* parent; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int U32_MAX ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 TYPE_1__ dc_wdt_wdd ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,int /*<<< orphan*/ *) ; 
 struct dc_wdt* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int devm_watchdog_register_device (struct device*,TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timeout ; 
 int /*<<< orphan*/  watchdog_init_timeout (TYPE_1__*,int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  watchdog_set_drvdata (TYPE_1__*,struct dc_wdt*) ; 
 int /*<<< orphan*/  watchdog_set_restart_priority (TYPE_1__*,int) ; 
 int /*<<< orphan*/  watchdog_stop_on_reboot (TYPE_1__*) ; 

__attribute__((used)) static int dc_wdt_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct dc_wdt *wdt;

	wdt = devm_kzalloc(dev, sizeof(struct dc_wdt), GFP_KERNEL);
	if (!wdt)
		return -ENOMEM;

	wdt->base = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(wdt->base))
		return PTR_ERR(wdt->base);

	wdt->clk = devm_clk_get(dev, NULL);
	if (IS_ERR(wdt->clk))
		return PTR_ERR(wdt->clk);
	dc_wdt_wdd.max_timeout = U32_MAX / clk_get_rate(wdt->clk);
	dc_wdt_wdd.timeout = dc_wdt_wdd.max_timeout;
	dc_wdt_wdd.parent = dev;

	spin_lock_init(&wdt->lock);

	watchdog_set_drvdata(&dc_wdt_wdd, wdt);
	watchdog_set_restart_priority(&dc_wdt_wdd, 128);
	watchdog_init_timeout(&dc_wdt_wdd, timeout, dev);
	watchdog_stop_on_reboot(&dc_wdt_wdd);
	return devm_watchdog_register_device(dev, &dc_wdt_wdd);
}
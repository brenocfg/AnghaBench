#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct TYPE_6__ {int max_timeout; struct device* parent; int /*<<< orphan*/  bootstatus; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int RALINK_WDT_PRESCALE ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_reset_control_get_exclusive (struct device*,int /*<<< orphan*/ *) ; 
 int devm_watchdog_register_device (struct device*,TYPE_1__*) ; 
 int /*<<< orphan*/  nowayout ; 
 int /*<<< orphan*/  reset_control_deassert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt288x_wdt_base ; 
 int /*<<< orphan*/  rt288x_wdt_bootcause () ; 
 int /*<<< orphan*/  rt288x_wdt_clk ; 
 TYPE_1__ rt288x_wdt_dev ; 
 int rt288x_wdt_freq ; 
 int /*<<< orphan*/  rt288x_wdt_reset ; 
 int /*<<< orphan*/  watchdog_init_timeout (TYPE_1__*,int,struct device*) ; 
 int /*<<< orphan*/  watchdog_set_nowayout (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  watchdog_stop_on_reboot (TYPE_1__*) ; 

__attribute__((used)) static int rt288x_wdt_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	int ret;

	rt288x_wdt_base = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(rt288x_wdt_base))
		return PTR_ERR(rt288x_wdt_base);

	rt288x_wdt_clk = devm_clk_get(dev, NULL);
	if (IS_ERR(rt288x_wdt_clk))
		return PTR_ERR(rt288x_wdt_clk);

	rt288x_wdt_reset = devm_reset_control_get_exclusive(dev, NULL);
	if (!IS_ERR(rt288x_wdt_reset))
		reset_control_deassert(rt288x_wdt_reset);

	rt288x_wdt_freq = clk_get_rate(rt288x_wdt_clk) / RALINK_WDT_PRESCALE;

	rt288x_wdt_dev.bootstatus = rt288x_wdt_bootcause();
	rt288x_wdt_dev.max_timeout = (0xfffful / rt288x_wdt_freq);
	rt288x_wdt_dev.parent = dev;

	watchdog_init_timeout(&rt288x_wdt_dev, rt288x_wdt_dev.max_timeout,
			      dev);
	watchdog_set_nowayout(&rt288x_wdt_dev, nowayout);

	watchdog_stop_on_reboot(&rt288x_wdt_dev);
	ret = devm_watchdog_register_device(dev, &rt288x_wdt_dev);
	if (!ret)
		dev_info(dev, "Initialized\n");

	return 0;
}
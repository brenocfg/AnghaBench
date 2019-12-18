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
struct watchdog_device {int min_timeout; int timeout; struct device* parent; int /*<<< orphan*/  max_timeout; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * info; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct imx7ulp_wdt_device {int /*<<< orphan*/  base; struct watchdog_device wdd; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int DEFAULT_TIMEOUT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_TIMEOUT ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int WDOG_CLOCK_RATE ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int devm_add_action_or_reset (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,int /*<<< orphan*/ *) ; 
 struct imx7ulp_wdt_device* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int devm_watchdog_register_device (struct device*,struct watchdog_device*) ; 
 int /*<<< orphan*/  imx7ulp_wdt_action ; 
 int /*<<< orphan*/  imx7ulp_wdt_info ; 
 int /*<<< orphan*/  imx7ulp_wdt_init (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  imx7ulp_wdt_ops ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct imx7ulp_wdt_device*) ; 
 int /*<<< orphan*/  watchdog_init_timeout (struct watchdog_device*,int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  watchdog_set_drvdata (struct watchdog_device*,struct imx7ulp_wdt_device*) ; 
 int /*<<< orphan*/  watchdog_stop_on_reboot (struct watchdog_device*) ; 
 int /*<<< orphan*/  watchdog_stop_on_unregister (struct watchdog_device*) ; 

__attribute__((used)) static int imx7ulp_wdt_probe(struct platform_device *pdev)
{
	struct imx7ulp_wdt_device *imx7ulp_wdt;
	struct device *dev = &pdev->dev;
	struct watchdog_device *wdog;
	int ret;

	imx7ulp_wdt = devm_kzalloc(dev, sizeof(*imx7ulp_wdt), GFP_KERNEL);
	if (!imx7ulp_wdt)
		return -ENOMEM;

	platform_set_drvdata(pdev, imx7ulp_wdt);

	imx7ulp_wdt->base = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(imx7ulp_wdt->base))
		return PTR_ERR(imx7ulp_wdt->base);

	imx7ulp_wdt->clk = devm_clk_get(dev, NULL);
	if (IS_ERR(imx7ulp_wdt->clk)) {
		dev_err(dev, "Failed to get watchdog clock\n");
		return PTR_ERR(imx7ulp_wdt->clk);
	}

	ret = clk_prepare_enable(imx7ulp_wdt->clk);
	if (ret)
		return ret;

	ret = devm_add_action_or_reset(dev, imx7ulp_wdt_action, imx7ulp_wdt->clk);
	if (ret)
		return ret;

	wdog = &imx7ulp_wdt->wdd;
	wdog->info = &imx7ulp_wdt_info;
	wdog->ops = &imx7ulp_wdt_ops;
	wdog->min_timeout = 1;
	wdog->max_timeout = MAX_TIMEOUT;
	wdog->parent = dev;
	wdog->timeout = DEFAULT_TIMEOUT;

	watchdog_init_timeout(wdog, 0, dev);
	watchdog_stop_on_reboot(wdog);
	watchdog_stop_on_unregister(wdog);
	watchdog_set_drvdata(wdog, imx7ulp_wdt);
	imx7ulp_wdt_init(imx7ulp_wdt->base, wdog->timeout * WDOG_CLOCK_RATE);

	return devm_watchdog_register_device(dev, wdog);
}
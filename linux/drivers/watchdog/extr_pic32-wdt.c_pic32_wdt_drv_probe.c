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
struct watchdog_device {int /*<<< orphan*/  bootstatus; int /*<<< orphan*/  timeout; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct pic32_wdt {int /*<<< orphan*/  clk; int /*<<< orphan*/  rst_base; int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIC32_BASE_RESET ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WATCHDOG_NOWAYOUT ; 
 int /*<<< orphan*/  WDIOF_CARDRESET ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ) ; 
 int devm_add_action_or_reset (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap (struct device*,int /*<<< orphan*/ ,int) ; 
 struct pic32_wdt* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int devm_watchdog_register_device (struct device*,struct watchdog_device*) ; 
 int /*<<< orphan*/  pic32_clk_disable_unprepare ; 
 struct watchdog_device pic32_wdd ; 
 scalar_t__ pic32_wdt_bootstatus (struct pic32_wdt*) ; 
 int /*<<< orphan*/  pic32_wdt_get_timeout_secs (struct pic32_wdt*,struct device*) ; 
 scalar_t__ pic32_wdt_is_win_enabled (struct pic32_wdt*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct watchdog_device*) ; 
 int /*<<< orphan*/  watchdog_set_drvdata (struct watchdog_device*,struct pic32_wdt*) ; 
 int /*<<< orphan*/  watchdog_set_nowayout (struct watchdog_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pic32_wdt_drv_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	int ret;
	struct watchdog_device *wdd = &pic32_wdd;
	struct pic32_wdt *wdt;

	wdt = devm_kzalloc(dev, sizeof(*wdt), GFP_KERNEL);
	if (!wdt)
		return -ENOMEM;

	wdt->regs = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(wdt->regs))
		return PTR_ERR(wdt->regs);

	wdt->rst_base = devm_ioremap(dev, PIC32_BASE_RESET, 0x10);
	if (!wdt->rst_base)
		return -ENOMEM;

	wdt->clk = devm_clk_get(dev, NULL);
	if (IS_ERR(wdt->clk)) {
		dev_err(dev, "clk not found\n");
		return PTR_ERR(wdt->clk);
	}

	ret = clk_prepare_enable(wdt->clk);
	if (ret) {
		dev_err(dev, "clk enable failed\n");
		return ret;
	}
	ret = devm_add_action_or_reset(dev, pic32_clk_disable_unprepare,
				       wdt->clk);
	if (ret)
		return ret;

	if (pic32_wdt_is_win_enabled(wdt)) {
		dev_err(dev, "windowed-clear mode is not supported.\n");
		return -ENODEV;
	}

	wdd->timeout = pic32_wdt_get_timeout_secs(wdt, dev);
	if (!wdd->timeout) {
		dev_err(dev, "failed to read watchdog register timeout\n");
		return -EINVAL;
	}

	dev_info(dev, "timeout %d\n", wdd->timeout);

	wdd->bootstatus = pic32_wdt_bootstatus(wdt) ? WDIOF_CARDRESET : 0;

	watchdog_set_nowayout(wdd, WATCHDOG_NOWAYOUT);
	watchdog_set_drvdata(wdd, wdt);

	ret = devm_watchdog_register_device(dev, wdd);
	if (ret)
		return ret;

	platform_set_drvdata(pdev, wdd);

	return 0;
}
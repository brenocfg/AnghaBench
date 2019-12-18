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
struct pic32_dmt {int /*<<< orphan*/  clk; int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WATCHDOG_NOWAYOUT ; 
 int /*<<< orphan*/  WDIOF_CARDRESET ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ) ; 
 int devm_add_action_or_reset (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,int /*<<< orphan*/ *) ; 
 struct pic32_dmt* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int devm_watchdog_register_device (struct device*,struct watchdog_device*) ; 
 int /*<<< orphan*/  pic32_clk_disable_unprepare ; 
 scalar_t__ pic32_dmt_bootstatus (struct pic32_dmt*) ; 
 int /*<<< orphan*/  pic32_dmt_get_timeout_secs (struct pic32_dmt*) ; 
 struct watchdog_device pic32_dmt_wdd ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct watchdog_device*) ; 
 int /*<<< orphan*/  watchdog_set_drvdata (struct watchdog_device*,struct pic32_dmt*) ; 
 int /*<<< orphan*/  watchdog_set_nowayout (struct watchdog_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pic32_dmt_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	int ret;
	struct pic32_dmt *dmt;
	struct watchdog_device *wdd = &pic32_dmt_wdd;

	dmt = devm_kzalloc(dev, sizeof(*dmt), GFP_KERNEL);
	if (!dmt)
		return -ENOMEM;

	dmt->regs = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(dmt->regs))
		return PTR_ERR(dmt->regs);

	dmt->clk = devm_clk_get(dev, NULL);
	if (IS_ERR(dmt->clk)) {
		dev_err(dev, "clk not found\n");
		return PTR_ERR(dmt->clk);
	}

	ret = clk_prepare_enable(dmt->clk);
	if (ret)
		return ret;
	ret = devm_add_action_or_reset(dev, pic32_clk_disable_unprepare,
				       dmt->clk);
	if (ret)
		return ret;

	wdd->timeout = pic32_dmt_get_timeout_secs(dmt);
	if (!wdd->timeout) {
		dev_err(dev, "failed to read watchdog register timeout\n");
		return -EINVAL;
	}

	dev_info(dev, "timeout %d\n", wdd->timeout);

	wdd->bootstatus = pic32_dmt_bootstatus(dmt) ? WDIOF_CARDRESET : 0;

	watchdog_set_nowayout(wdd, WATCHDOG_NOWAYOUT);
	watchdog_set_drvdata(wdd, dmt);

	ret = devm_watchdog_register_device(dev, wdd);
	if (ret)
		return ret;

	platform_set_drvdata(pdev, wdd);
	return 0;
}
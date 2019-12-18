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
struct TYPE_6__ {int /*<<< orphan*/  timeout; int /*<<< orphan*/  status; struct device* parent; int /*<<< orphan*/  bootstatus; } ;

/* Variables and functions */
 int COUNT_ENAB ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WDIOF_CARDRESET ; 
 int /*<<< orphan*/  WDOG_HW_RUNNING ; 
 int WDOG_RESET ; 
 int /*<<< orphan*/  WDTIM_CTRL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WDTIM_RES (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ) ; 
 int devm_add_action_or_reset (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int devm_watchdog_register_device (struct device*,TYPE_1__*) ; 
 int /*<<< orphan*/  heartbeat ; 
 int /*<<< orphan*/  nowayout ; 
 int /*<<< orphan*/  pnx4008_clk_disable_unprepare ; 
 TYPE_1__ pnx4008_wdd ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  watchdog_init_timeout (TYPE_1__*,int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  watchdog_set_nowayout (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  watchdog_set_restart_priority (TYPE_1__*,int) ; 
 int /*<<< orphan*/  wdt_base ; 
 int /*<<< orphan*/  wdt_clk ; 

__attribute__((used)) static int pnx4008_wdt_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	int ret = 0;

	watchdog_init_timeout(&pnx4008_wdd, heartbeat, dev);

	wdt_base = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(wdt_base))
		return PTR_ERR(wdt_base);

	wdt_clk = devm_clk_get(dev, NULL);
	if (IS_ERR(wdt_clk))
		return PTR_ERR(wdt_clk);

	ret = clk_prepare_enable(wdt_clk);
	if (ret)
		return ret;
	ret = devm_add_action_or_reset(dev, pnx4008_clk_disable_unprepare,
				       wdt_clk);
	if (ret)
		return ret;

	pnx4008_wdd.bootstatus = (readl(WDTIM_RES(wdt_base)) & WDOG_RESET) ?
			WDIOF_CARDRESET : 0;
	pnx4008_wdd.parent = dev;
	watchdog_set_nowayout(&pnx4008_wdd, nowayout);
	watchdog_set_restart_priority(&pnx4008_wdd, 128);

	if (readl(WDTIM_CTRL(wdt_base)) & COUNT_ENAB)
		set_bit(WDOG_HW_RUNNING, &pnx4008_wdd.status);

	ret = devm_watchdog_register_device(dev, &pnx4008_wdd);
	if (ret < 0)
		return ret;

	dev_info(dev, "heartbeat %d sec\n", pnx4008_wdd.timeout);

	return 0;
}
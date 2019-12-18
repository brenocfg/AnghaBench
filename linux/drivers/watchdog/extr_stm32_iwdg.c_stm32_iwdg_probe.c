#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct watchdog_device {int max_hw_heartbeat_ms; int /*<<< orphan*/  min_timeout; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * info; struct device* parent; } ;
struct stm32_iwdg {int rate; TYPE_1__* data; struct watchdog_device wdd; int /*<<< orphan*/  regs; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct TYPE_2__ {int max_prescaler; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_UP (int,int) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PR_MIN ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int RLR_MAX ; 
 int RLR_MIN ; 
 int /*<<< orphan*/  WATCHDOG_NOWAYOUT ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct stm32_iwdg* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int devm_watchdog_register_device (struct device*,struct watchdog_device*) ; 
 TYPE_1__* of_device_get_match_data (struct device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct stm32_iwdg*) ; 
 int stm32_iwdg_clk_init (struct platform_device*,struct stm32_iwdg*) ; 
 int /*<<< orphan*/  stm32_iwdg_info ; 
 int /*<<< orphan*/  stm32_iwdg_ops ; 
 int /*<<< orphan*/  watchdog_init_timeout (struct watchdog_device*,int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  watchdog_set_drvdata (struct watchdog_device*,struct stm32_iwdg*) ; 
 int /*<<< orphan*/  watchdog_set_nowayout (struct watchdog_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stm32_iwdg_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct watchdog_device *wdd;
	struct stm32_iwdg *wdt;
	int ret;

	wdt = devm_kzalloc(dev, sizeof(*wdt), GFP_KERNEL);
	if (!wdt)
		return -ENOMEM;

	wdt->data = of_device_get_match_data(&pdev->dev);
	if (!wdt->data)
		return -ENODEV;

	/* This is the timer base. */
	wdt->regs = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(wdt->regs)) {
		dev_err(dev, "Could not get resource\n");
		return PTR_ERR(wdt->regs);
	}

	ret = stm32_iwdg_clk_init(pdev, wdt);
	if (ret)
		return ret;

	/* Initialize struct watchdog_device. */
	wdd = &wdt->wdd;
	wdd->parent = dev;
	wdd->info = &stm32_iwdg_info;
	wdd->ops = &stm32_iwdg_ops;
	wdd->min_timeout = DIV_ROUND_UP((RLR_MIN + 1) * PR_MIN, wdt->rate);
	wdd->max_hw_heartbeat_ms = ((RLR_MAX + 1) * wdt->data->max_prescaler *
				    1000) / wdt->rate;

	watchdog_set_drvdata(wdd, wdt);
	watchdog_set_nowayout(wdd, WATCHDOG_NOWAYOUT);
	watchdog_init_timeout(wdd, 0, dev);

	ret = devm_watchdog_register_device(dev, wdd);
	if (ret)
		return ret;

	platform_set_drvdata(pdev, wdt);

	return 0;
}
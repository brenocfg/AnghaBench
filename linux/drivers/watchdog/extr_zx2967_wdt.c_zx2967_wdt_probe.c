#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  timeout; struct device* parent; int /*<<< orphan*/  min_timeout; int /*<<< orphan*/  max_timeout; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * info; } ;
struct zx2967_wdt {TYPE_1__ wdt_device; struct reset_control* clock; struct reset_control* reg_base; } ;
struct reset_control {int dummy; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct reset_control*) ; 
 int PTR_ERR (struct reset_control*) ; 
 int /*<<< orphan*/  WATCHDOG_NOWAYOUT ; 
 int /*<<< orphan*/  ZX2967_WDT_CLK_FREQ ; 
 int /*<<< orphan*/  ZX2967_WDT_DEFAULT_TIMEOUT ; 
 int /*<<< orphan*/  ZX2967_WDT_MAX_TIMEOUT ; 
 int /*<<< orphan*/  ZX2967_WDT_MIN_TIMEOUT ; 
 int clk_prepare_enable (struct reset_control*) ; 
 int /*<<< orphan*/  clk_set_rate (struct reset_control*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int devm_add_action_or_reset (struct device*,int /*<<< orphan*/ ,struct reset_control*) ; 
 struct reset_control* devm_clk_get (struct device*,int /*<<< orphan*/ *) ; 
 struct zx2967_wdt* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct reset_control* devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct reset_control* devm_reset_control_get_exclusive (struct device*,int /*<<< orphan*/ *) ; 
 int devm_watchdog_register_device (struct device*,TYPE_1__*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct zx2967_wdt*) ; 
 int /*<<< orphan*/  reset_control_assert (struct reset_control*) ; 
 int /*<<< orphan*/  reset_control_deassert (struct reset_control*) ; 
 int /*<<< orphan*/  watchdog_init_timeout (TYPE_1__*,int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  watchdog_set_drvdata (TYPE_1__*,struct zx2967_wdt*) ; 
 int /*<<< orphan*/  watchdog_set_nowayout (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zx2967_clk_disable_unprepare ; 
 int /*<<< orphan*/  zx2967_wdt_ident ; 
 int /*<<< orphan*/  zx2967_wdt_ops ; 
 int /*<<< orphan*/  zx2967_wdt_reset_sysctrl (struct device*) ; 

__attribute__((used)) static int zx2967_wdt_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct zx2967_wdt *wdt;
	int ret;
	struct reset_control *rstc;

	wdt = devm_kzalloc(dev, sizeof(*wdt), GFP_KERNEL);
	if (!wdt)
		return -ENOMEM;

	platform_set_drvdata(pdev, wdt);

	wdt->wdt_device.info = &zx2967_wdt_ident;
	wdt->wdt_device.ops = &zx2967_wdt_ops;
	wdt->wdt_device.timeout = ZX2967_WDT_DEFAULT_TIMEOUT;
	wdt->wdt_device.max_timeout = ZX2967_WDT_MAX_TIMEOUT;
	wdt->wdt_device.min_timeout = ZX2967_WDT_MIN_TIMEOUT;
	wdt->wdt_device.parent = dev;

	wdt->reg_base = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(wdt->reg_base))
		return PTR_ERR(wdt->reg_base);

	zx2967_wdt_reset_sysctrl(dev);

	wdt->clock = devm_clk_get(dev, NULL);
	if (IS_ERR(wdt->clock)) {
		dev_err(dev, "failed to find watchdog clock source\n");
		return PTR_ERR(wdt->clock);
	}

	ret = clk_prepare_enable(wdt->clock);
	if (ret < 0) {
		dev_err(dev, "failed to enable clock\n");
		return ret;
	}
	ret = devm_add_action_or_reset(dev, zx2967_clk_disable_unprepare,
				       wdt->clock);
	if (ret)
		return ret;
	clk_set_rate(wdt->clock, ZX2967_WDT_CLK_FREQ);

	rstc = devm_reset_control_get_exclusive(dev, NULL);
	if (IS_ERR(rstc)) {
		dev_err(dev, "failed to get rstc");
		return PTR_ERR(rstc);
	}

	reset_control_assert(rstc);
	reset_control_deassert(rstc);

	watchdog_set_drvdata(&wdt->wdt_device, wdt);
	watchdog_init_timeout(&wdt->wdt_device,
			ZX2967_WDT_DEFAULT_TIMEOUT, dev);
	watchdog_set_nowayout(&wdt->wdt_device, WATCHDOG_NOWAYOUT);

	ret = devm_watchdog_register_device(dev, &wdt->wdt_device);
	if (ret)
		return ret;

	dev_info(dev, "watchdog enabled (timeout=%d sec, nowayout=%d)",
		 wdt->wdt_device.timeout, WATCHDOG_NOWAYOUT);

	return 0;
}
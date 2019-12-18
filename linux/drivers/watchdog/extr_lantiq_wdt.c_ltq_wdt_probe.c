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
typedef  int u32 ;
struct watchdog_device {int min_timeout; int max_timeout; int timeout; int bootstatus; int /*<<< orphan*/  status; struct device* parent; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * info; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct ltq_wdt_priv {int clk_rate; struct watchdog_device wdt; int /*<<< orphan*/  membase; } ;
struct ltq_wdt_hw {int (* bootstatus_get ) (struct device*) ;} ;
struct clk {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int LTQ_WDT_CR_MAX_TIMEOUT ; 
 int LTQ_WDT_DIVIDER ; 
 int /*<<< orphan*/  LTQ_WDT_SR ; 
 int LTQ_WDT_SR_EN ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WDOG_HW_RUNNING ; 
 struct clk* clk_get_io () ; 
 int clk_get_rate (struct clk*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct ltq_wdt_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int devm_watchdog_register_device (struct device*,struct watchdog_device*) ; 
 int /*<<< orphan*/  ltq_wdt_info ; 
 int /*<<< orphan*/  ltq_wdt_ops ; 
 int ltq_wdt_r32 (struct ltq_wdt_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ltq_wdt_start (struct watchdog_device*) ; 
 int /*<<< orphan*/  nowayout ; 
 struct ltq_wdt_hw* of_device_get_match_data (struct device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub1 (struct device*) ; 
 int /*<<< orphan*/  watchdog_init_timeout (struct watchdog_device*,int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  watchdog_set_nowayout (struct watchdog_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ltq_wdt_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct ltq_wdt_priv *priv;
	struct watchdog_device *wdt;
	struct clk *clk;
	const struct ltq_wdt_hw *ltq_wdt_hw;
	int ret;
	u32 status;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->membase = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(priv->membase))
		return PTR_ERR(priv->membase);

	/* we do not need to enable the clock as it is always running */
	clk = clk_get_io();
	priv->clk_rate = clk_get_rate(clk) / LTQ_WDT_DIVIDER;
	if (!priv->clk_rate) {
		dev_err(dev, "clock rate less than divider %i\n",
			LTQ_WDT_DIVIDER);
		return -EINVAL;
	}

	wdt = &priv->wdt;
	wdt->info		= &ltq_wdt_info;
	wdt->ops		= &ltq_wdt_ops;
	wdt->min_timeout	= 1;
	wdt->max_timeout	= LTQ_WDT_CR_MAX_TIMEOUT / priv->clk_rate;
	wdt->timeout		= wdt->max_timeout;
	wdt->parent		= dev;

	ltq_wdt_hw = of_device_get_match_data(dev);
	if (ltq_wdt_hw && ltq_wdt_hw->bootstatus_get) {
		ret = ltq_wdt_hw->bootstatus_get(dev);
		if (ret >= 0)
			wdt->bootstatus = ret;
	}

	watchdog_set_nowayout(wdt, nowayout);
	watchdog_init_timeout(wdt, 0, dev);

	status = ltq_wdt_r32(priv, LTQ_WDT_SR);
	if (status & LTQ_WDT_SR_EN) {
		/*
		 * If the watchdog is already running overwrite it with our
		 * new settings. Stop is not needed as the start call will
		 * replace all settings anyway.
		 */
		ltq_wdt_start(wdt);
		set_bit(WDOG_HW_RUNNING, &wdt->status);
	}

	return devm_watchdog_register_device(dev, wdt);
}
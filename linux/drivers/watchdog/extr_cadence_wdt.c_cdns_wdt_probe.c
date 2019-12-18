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
struct watchdog_device {int /*<<< orphan*/  timeout; struct device* parent; int /*<<< orphan*/  max_timeout; int /*<<< orphan*/  min_timeout; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * info; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {int /*<<< orphan*/  name; struct device dev; } ;
struct cdns_wdt {int /*<<< orphan*/  regs; int /*<<< orphan*/  io_lock; int /*<<< orphan*/  ctrl_clksel; int /*<<< orphan*/  prescaler; int /*<<< orphan*/  clk; int /*<<< orphan*/  rst; struct watchdog_device cdns_wdt_device; } ;

/* Variables and functions */
 unsigned long CDNS_WDT_CLK_75MHZ ; 
 int /*<<< orphan*/  CDNS_WDT_DEFAULT_TIMEOUT ; 
 int /*<<< orphan*/  CDNS_WDT_MAX_TIMEOUT ; 
 int /*<<< orphan*/  CDNS_WDT_MIN_TIMEOUT ; 
 int /*<<< orphan*/  CDNS_WDT_PRESCALE_4096 ; 
 int /*<<< orphan*/  CDNS_WDT_PRESCALE_512 ; 
 int /*<<< orphan*/  CDNS_WDT_PRESCALE_SELECT_4096 ; 
 int /*<<< orphan*/  CDNS_WDT_PRESCALE_SELECT_512 ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdns_clk_disable_unprepare ; 
 int /*<<< orphan*/  cdns_wdt_info ; 
 int /*<<< orphan*/  cdns_wdt_irq_handler ; 
 int /*<<< orphan*/  cdns_wdt_ops ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int devm_add_action_or_reset (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,int /*<<< orphan*/ *) ; 
 struct cdns_wdt* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int devm_request_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct platform_device*) ; 
 int devm_watchdog_register_device (struct device*,struct watchdog_device*) ; 
 scalar_t__ nowayout ; 
 int /*<<< orphan*/  of_property_read_bool (int /*<<< orphan*/ ,char*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct cdns_wdt*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  watchdog_init_timeout (struct watchdog_device*,int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  watchdog_set_drvdata (struct watchdog_device*,struct cdns_wdt*) ; 
 int /*<<< orphan*/  watchdog_set_nowayout (struct watchdog_device*,scalar_t__) ; 
 int /*<<< orphan*/  watchdog_stop_on_reboot (struct watchdog_device*) ; 
 int /*<<< orphan*/  watchdog_stop_on_unregister (struct watchdog_device*) ; 
 int /*<<< orphan*/  wdt_timeout ; 

__attribute__((used)) static int cdns_wdt_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	int ret, irq;
	unsigned long clock_f;
	struct cdns_wdt *wdt;
	struct watchdog_device *cdns_wdt_device;

	wdt = devm_kzalloc(dev, sizeof(*wdt), GFP_KERNEL);
	if (!wdt)
		return -ENOMEM;

	cdns_wdt_device = &wdt->cdns_wdt_device;
	cdns_wdt_device->info = &cdns_wdt_info;
	cdns_wdt_device->ops = &cdns_wdt_ops;
	cdns_wdt_device->timeout = CDNS_WDT_DEFAULT_TIMEOUT;
	cdns_wdt_device->min_timeout = CDNS_WDT_MIN_TIMEOUT;
	cdns_wdt_device->max_timeout = CDNS_WDT_MAX_TIMEOUT;

	wdt->regs = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(wdt->regs))
		return PTR_ERR(wdt->regs);

	/* Register the interrupt */
	wdt->rst = of_property_read_bool(dev->of_node, "reset-on-timeout");
	irq = platform_get_irq(pdev, 0);
	if (!wdt->rst && irq >= 0) {
		ret = devm_request_irq(dev, irq, cdns_wdt_irq_handler, 0,
				       pdev->name, pdev);
		if (ret) {
			dev_err(dev,
				"cannot register interrupt handler err=%d\n",
				ret);
			return ret;
		}
	}

	/* Initialize the members of cdns_wdt structure */
	cdns_wdt_device->parent = dev;

	watchdog_init_timeout(cdns_wdt_device, wdt_timeout, dev);
	watchdog_set_nowayout(cdns_wdt_device, nowayout);
	watchdog_stop_on_reboot(cdns_wdt_device);
	watchdog_set_drvdata(cdns_wdt_device, wdt);

	wdt->clk = devm_clk_get(dev, NULL);
	if (IS_ERR(wdt->clk)) {
		dev_err(dev, "input clock not found\n");
		return PTR_ERR(wdt->clk);
	}

	ret = clk_prepare_enable(wdt->clk);
	if (ret) {
		dev_err(dev, "unable to enable clock\n");
		return ret;
	}
	ret = devm_add_action_or_reset(dev, cdns_clk_disable_unprepare,
				       wdt->clk);
	if (ret)
		return ret;

	clock_f = clk_get_rate(wdt->clk);
	if (clock_f <= CDNS_WDT_CLK_75MHZ) {
		wdt->prescaler = CDNS_WDT_PRESCALE_512;
		wdt->ctrl_clksel = CDNS_WDT_PRESCALE_SELECT_512;
	} else {
		wdt->prescaler = CDNS_WDT_PRESCALE_4096;
		wdt->ctrl_clksel = CDNS_WDT_PRESCALE_SELECT_4096;
	}

	spin_lock_init(&wdt->io_lock);

	watchdog_stop_on_reboot(cdns_wdt_device);
	watchdog_stop_on_unregister(cdns_wdt_device);
	ret = devm_watchdog_register_device(dev, cdns_wdt_device);
	if (ret)
		return ret;
	platform_set_drvdata(pdev, wdt);

	dev_info(dev, "Xilinx Watchdog Timer at %p with timeout %ds%s\n",
		 wdt->regs, cdns_wdt_device->timeout,
		 nowayout ? ", nowayout" : "");

	return 0;
}
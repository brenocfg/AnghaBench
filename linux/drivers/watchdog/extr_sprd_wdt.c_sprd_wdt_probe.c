#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* timeout; void* max_timeout; int /*<<< orphan*/  min_timeout; struct device* parent; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * info; } ;
struct sprd_wdt {scalar_t__ irq; TYPE_1__ wdd; void* rtc_enable; void* enable; void* base; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQF_NO_SUSPEND ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 void* SPRD_WDT_MAX_TIMEOUT ; 
 int /*<<< orphan*/  SPRD_WDT_MIN_TIMEOUT ; 
 int /*<<< orphan*/  WATCHDOG_NOWAYOUT ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int devm_add_action_or_reset (struct device*,int /*<<< orphan*/  (*) (struct sprd_wdt*),struct sprd_wdt*) ; 
 void* devm_clk_get (struct device*,char*) ; 
 struct sprd_wdt* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 void* devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int devm_request_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,void*) ; 
 int devm_watchdog_register_device (struct device*,TYPE_1__*) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct sprd_wdt*) ; 
 int /*<<< orphan*/  sprd_wdt_disable (struct sprd_wdt*) ; 
 int sprd_wdt_enable (struct sprd_wdt*) ; 
 int /*<<< orphan*/  sprd_wdt_info ; 
 int /*<<< orphan*/  sprd_wdt_isr ; 
 int /*<<< orphan*/  sprd_wdt_ops ; 
 int /*<<< orphan*/  watchdog_init_timeout (TYPE_1__*,int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  watchdog_set_nowayout (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sprd_wdt_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct sprd_wdt *wdt;
	int ret;

	wdt = devm_kzalloc(dev, sizeof(*wdt), GFP_KERNEL);
	if (!wdt)
		return -ENOMEM;

	wdt->base = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(wdt->base))
		return PTR_ERR(wdt->base);

	wdt->enable = devm_clk_get(dev, "enable");
	if (IS_ERR(wdt->enable)) {
		dev_err(dev, "can't get the enable clock\n");
		return PTR_ERR(wdt->enable);
	}

	wdt->rtc_enable = devm_clk_get(dev, "rtc_enable");
	if (IS_ERR(wdt->rtc_enable)) {
		dev_err(dev, "can't get the rtc enable clock\n");
		return PTR_ERR(wdt->rtc_enable);
	}

	wdt->irq = platform_get_irq(pdev, 0);
	if (wdt->irq < 0)
		return wdt->irq;

	ret = devm_request_irq(dev, wdt->irq, sprd_wdt_isr, IRQF_NO_SUSPEND,
			       "sprd-wdt", (void *)wdt);
	if (ret) {
		dev_err(dev, "failed to register irq\n");
		return ret;
	}

	wdt->wdd.info = &sprd_wdt_info;
	wdt->wdd.ops = &sprd_wdt_ops;
	wdt->wdd.parent = dev;
	wdt->wdd.min_timeout = SPRD_WDT_MIN_TIMEOUT;
	wdt->wdd.max_timeout = SPRD_WDT_MAX_TIMEOUT;
	wdt->wdd.timeout = SPRD_WDT_MAX_TIMEOUT;

	ret = sprd_wdt_enable(wdt);
	if (ret) {
		dev_err(dev, "failed to enable wdt\n");
		return ret;
	}
	ret = devm_add_action_or_reset(dev, sprd_wdt_disable, wdt);
	if (ret) {
		dev_err(dev, "Failed to add wdt disable action\n");
		return ret;
	}

	watchdog_set_nowayout(&wdt->wdd, WATCHDOG_NOWAYOUT);
	watchdog_init_timeout(&wdt->wdd, 0, dev);

	ret = devm_watchdog_register_device(dev, &wdt->wdd);
	if (ret) {
		sprd_wdt_disable(wdt);
		return ret;
	}
	platform_set_drvdata(pdev, wdt);

	return 0;
}
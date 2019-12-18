#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct TYPE_3__ {int min_timeout; int max_timeout; unsigned int timeout; struct device* parent; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * info; } ;
struct ftwdt010_wdt {int has_irq; TYPE_1__ wdd; scalar_t__ base; struct device* dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ FTWDT010_WDCR ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 unsigned int WDCR_ENABLE ; 
 int WDT_CLOCK ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 struct ftwdt010_wdt* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int devm_request_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct ftwdt010_wdt*) ; 
 int devm_watchdog_register_device (struct device*,TYPE_1__*) ; 
 int /*<<< orphan*/  ftwdt010_wdt_info ; 
 int /*<<< orphan*/  ftwdt010_wdt_interrupt ; 
 int /*<<< orphan*/  ftwdt010_wdt_ops ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct ftwdt010_wdt*) ; 
 unsigned int readw (scalar_t__) ; 
 int /*<<< orphan*/  watchdog_init_timeout (TYPE_1__*,int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static int ftwdt010_wdt_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct ftwdt010_wdt *gwdt;
	unsigned int reg;
	int irq;
	int ret;

	gwdt = devm_kzalloc(dev, sizeof(*gwdt), GFP_KERNEL);
	if (!gwdt)
		return -ENOMEM;

	gwdt->base = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(gwdt->base))
		return PTR_ERR(gwdt->base);

	gwdt->dev = dev;
	gwdt->wdd.info = &ftwdt010_wdt_info;
	gwdt->wdd.ops = &ftwdt010_wdt_ops;
	gwdt->wdd.min_timeout = 1;
	gwdt->wdd.max_timeout = 0xFFFFFFFF / WDT_CLOCK;
	gwdt->wdd.parent = dev;

	/*
	 * If 'timeout-sec' unspecified in devicetree, assume a 13 second
	 * default.
	 */
	gwdt->wdd.timeout = 13U;
	watchdog_init_timeout(&gwdt->wdd, 0, dev);

	reg = readw(gwdt->base + FTWDT010_WDCR);
	if (reg & WDCR_ENABLE) {
		/* Watchdog was enabled by the bootloader, disable it. */
		reg &= ~WDCR_ENABLE;
		writel(reg, gwdt->base + FTWDT010_WDCR);
	}

	irq = platform_get_irq(pdev, 0);
	if (irq) {
		ret = devm_request_irq(dev, irq, ftwdt010_wdt_interrupt, 0,
				       "watchdog bark", gwdt);
		if (ret)
			return ret;
		gwdt->has_irq = true;
	}

	ret = devm_watchdog_register_device(dev, &gwdt->wdd);
	if (ret)
		return ret;

	/* Set up platform driver data */
	platform_set_drvdata(pdev, gwdt);
	dev_info(dev, "FTWDT010 watchdog driver enabled\n");

	return 0;
}
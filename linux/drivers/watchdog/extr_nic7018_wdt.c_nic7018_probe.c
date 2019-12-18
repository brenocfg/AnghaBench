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
struct watchdog_device {struct device* parent; int /*<<< orphan*/  timeout; int /*<<< orphan*/  max_timeout; int /*<<< orphan*/  min_timeout; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * info; } ;
struct resource {scalar_t__ start; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct nic7018_wdt {scalar_t__ io_base; struct watchdog_device wdd; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_IO ; 
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 int /*<<< orphan*/  LOCK ; 
 int /*<<< orphan*/  UNLOCK ; 
 int /*<<< orphan*/  WDT_DEFAULT_TIMEOUT ; 
 int /*<<< orphan*/  WDT_MAX_TIMEOUT ; 
 int /*<<< orphan*/  WDT_MIN_TIMEOUT ; 
 scalar_t__ WDT_REG_LOCK ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct nic7018_wdt* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_request_region (struct device*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nic7018_wdd_info ; 
 int /*<<< orphan*/  nic7018_wdd_ops ; 
 int /*<<< orphan*/  nowayout ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct nic7018_wdt*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  timeout ; 
 int /*<<< orphan*/  watchdog_init_timeout (struct watchdog_device*,int /*<<< orphan*/ ,struct device*) ; 
 int watchdog_register_device (struct watchdog_device*) ; 
 int /*<<< orphan*/  watchdog_set_drvdata (struct watchdog_device*,struct nic7018_wdt*) ; 
 int /*<<< orphan*/  watchdog_set_nowayout (struct watchdog_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nic7018_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct watchdog_device *wdd;
	struct nic7018_wdt *wdt;
	struct resource *io_rc;
	int ret;

	wdt = devm_kzalloc(dev, sizeof(*wdt), GFP_KERNEL);
	if (!wdt)
		return -ENOMEM;

	platform_set_drvdata(pdev, wdt);

	io_rc = platform_get_resource(pdev, IORESOURCE_IO, 0);
	if (!io_rc) {
		dev_err(dev, "missing IO resources\n");
		return -EINVAL;
	}

	if (!devm_request_region(dev, io_rc->start, resource_size(io_rc),
				 KBUILD_MODNAME)) {
		dev_err(dev, "failed to get IO region\n");
		return -EBUSY;
	}

	wdt->io_base = io_rc->start;
	wdd = &wdt->wdd;
	wdd->info = &nic7018_wdd_info;
	wdd->ops = &nic7018_wdd_ops;
	wdd->min_timeout = WDT_MIN_TIMEOUT;
	wdd->max_timeout = WDT_MAX_TIMEOUT;
	wdd->timeout = WDT_DEFAULT_TIMEOUT;
	wdd->parent = dev;

	watchdog_set_drvdata(wdd, wdt);
	watchdog_set_nowayout(wdd, nowayout);
	watchdog_init_timeout(wdd, timeout, dev);

	/* Unlock WDT register */
	outb(UNLOCK, wdt->io_base + WDT_REG_LOCK);

	ret = watchdog_register_device(wdd);
	if (ret) {
		outb(LOCK, wdt->io_base + WDT_REG_LOCK);
		return ret;
	}

	dev_dbg(dev, "io_base=0x%04X, timeout=%d, nowayout=%d\n",
		wdt->io_base, timeout, nowayout);
	return 0;
}
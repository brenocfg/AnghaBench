#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {void* timeout; struct device* parent; int /*<<< orphan*/  min_timeout; void* max_timeout; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * info; } ;
struct sunxi_wdt_dev {TYPE_1__ wdt_dev; int /*<<< orphan*/  wdt_base; int /*<<< orphan*/  wdt_regs; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 void* WDT_MAX_TIMEOUT ; 
 int /*<<< orphan*/  WDT_MIN_TIMEOUT ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,void*,int /*<<< orphan*/ ) ; 
 struct sunxi_wdt_dev* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int devm_watchdog_register_device (struct device*,TYPE_1__*) ; 
 int /*<<< orphan*/  nowayout ; 
 int /*<<< orphan*/  of_device_get_match_data (struct device*) ; 
 int /*<<< orphan*/  sunxi_wdt_info ; 
 int /*<<< orphan*/  sunxi_wdt_ops ; 
 int /*<<< orphan*/  sunxi_wdt_stop (TYPE_1__*) ; 
 int /*<<< orphan*/  timeout ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  watchdog_init_timeout (TYPE_1__*,int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  watchdog_set_drvdata (TYPE_1__*,struct sunxi_wdt_dev*) ; 
 int /*<<< orphan*/  watchdog_set_nowayout (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  watchdog_set_restart_priority (TYPE_1__*,int) ; 
 int /*<<< orphan*/  watchdog_stop_on_reboot (TYPE_1__*) ; 

__attribute__((used)) static int sunxi_wdt_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct sunxi_wdt_dev *sunxi_wdt;
	int err;

	sunxi_wdt = devm_kzalloc(dev, sizeof(*sunxi_wdt), GFP_KERNEL);
	if (!sunxi_wdt)
		return -EINVAL;

	sunxi_wdt->wdt_regs = of_device_get_match_data(dev);
	if (!sunxi_wdt->wdt_regs)
		return -ENODEV;

	sunxi_wdt->wdt_base = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(sunxi_wdt->wdt_base))
		return PTR_ERR(sunxi_wdt->wdt_base);

	sunxi_wdt->wdt_dev.info = &sunxi_wdt_info;
	sunxi_wdt->wdt_dev.ops = &sunxi_wdt_ops;
	sunxi_wdt->wdt_dev.timeout = WDT_MAX_TIMEOUT;
	sunxi_wdt->wdt_dev.max_timeout = WDT_MAX_TIMEOUT;
	sunxi_wdt->wdt_dev.min_timeout = WDT_MIN_TIMEOUT;
	sunxi_wdt->wdt_dev.parent = dev;

	watchdog_init_timeout(&sunxi_wdt->wdt_dev, timeout, dev);
	watchdog_set_nowayout(&sunxi_wdt->wdt_dev, nowayout);
	watchdog_set_restart_priority(&sunxi_wdt->wdt_dev, 128);

	watchdog_set_drvdata(&sunxi_wdt->wdt_dev, sunxi_wdt);

	sunxi_wdt_stop(&sunxi_wdt->wdt_dev);

	watchdog_stop_on_reboot(&sunxi_wdt->wdt_dev);
	err = devm_watchdog_register_device(dev, &sunxi_wdt->wdt_dev);
	if (unlikely(err))
		return err;

	dev_info(dev, "Watchdog enabled (timeout=%d sec, nowayout=%d)",
		 sunxi_wdt->wdt_dev.timeout, nowayout);

	return 0;
}
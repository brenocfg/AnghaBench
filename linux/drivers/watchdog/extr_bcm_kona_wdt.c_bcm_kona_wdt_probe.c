#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct bcm_kona_wdt {int /*<<< orphan*/  resolution; int /*<<< orphan*/  base; int /*<<< orphan*/  lock; } ;
struct TYPE_7__ {struct device* parent; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SECWDOG_DEFAULT_RESOLUTION ; 
 int /*<<< orphan*/  bcm_kona_wdt_debug_init (struct platform_device*) ; 
 int bcm_kona_wdt_set_resolution_reg (struct bcm_kona_wdt*) ; 
 int bcm_kona_wdt_set_timeout_reg (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__ bcm_kona_wdt_wdd ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct bcm_kona_wdt* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int devm_watchdog_register_device (struct device*,TYPE_1__*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct bcm_kona_wdt*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  watchdog_set_drvdata (TYPE_1__*,struct bcm_kona_wdt*) ; 
 int /*<<< orphan*/  watchdog_stop_on_reboot (TYPE_1__*) ; 
 int /*<<< orphan*/  watchdog_stop_on_unregister (TYPE_1__*) ; 

__attribute__((used)) static int bcm_kona_wdt_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct bcm_kona_wdt *wdt;
	int ret;

	wdt = devm_kzalloc(dev, sizeof(*wdt), GFP_KERNEL);
	if (!wdt)
		return -ENOMEM;

	spin_lock_init(&wdt->lock);

	wdt->base = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(wdt->base))
		return -ENODEV;

	wdt->resolution = SECWDOG_DEFAULT_RESOLUTION;
	ret = bcm_kona_wdt_set_resolution_reg(wdt);
	if (ret) {
		dev_err(dev, "Failed to set resolution (error: %d)", ret);
		return ret;
	}

	platform_set_drvdata(pdev, wdt);
	watchdog_set_drvdata(&bcm_kona_wdt_wdd, wdt);
	bcm_kona_wdt_wdd.parent = dev;

	ret = bcm_kona_wdt_set_timeout_reg(&bcm_kona_wdt_wdd, 0);
	if (ret) {
		dev_err(dev, "Failed set watchdog timeout");
		return ret;
	}

	watchdog_stop_on_reboot(&bcm_kona_wdt_wdd);
	watchdog_stop_on_unregister(&bcm_kona_wdt_wdd);
	ret = devm_watchdog_register_device(dev, &bcm_kona_wdt_wdd);
	if (ret)
		return ret;

	bcm_kona_wdt_debug_init(pdev);
	dev_dbg(dev, "Broadcom Kona Watchdog Timer");

	return 0;
}
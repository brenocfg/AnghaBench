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
struct device {int /*<<< orphan*/  parent; } ;
struct platform_device {struct device dev; } ;
struct bcm2835_wdt {int /*<<< orphan*/  base; int /*<<< orphan*/  lock; } ;
struct bcm2835_pm {int /*<<< orphan*/  base; } ;
struct TYPE_8__ {int /*<<< orphan*/  status; struct device* parent; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WDOG_HW_RUNNING ; 
 int /*<<< orphan*/ * bcm2835_power_off ; 
 struct bcm2835_wdt* bcm2835_power_off_wdt ; 
 scalar_t__ bcm2835_wdt_is_running (struct bcm2835_wdt*) ; 
 TYPE_1__ bcm2835_wdt_wdd ; 
 struct bcm2835_pm* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 struct bcm2835_wdt* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_watchdog_register_device (struct device*,TYPE_1__*) ; 
 int /*<<< orphan*/  heartbeat ; 
 int /*<<< orphan*/  nowayout ; 
 int /*<<< orphan*/ * pm_power_off ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  watchdog_init_timeout (TYPE_1__*,int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  watchdog_set_drvdata (TYPE_1__*,struct bcm2835_wdt*) ; 
 int /*<<< orphan*/  watchdog_set_nowayout (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  watchdog_set_restart_priority (TYPE_1__*,int) ; 
 int /*<<< orphan*/  watchdog_stop_on_reboot (TYPE_1__*) ; 

__attribute__((used)) static int bcm2835_wdt_probe(struct platform_device *pdev)
{
	struct bcm2835_pm *pm = dev_get_drvdata(pdev->dev.parent);
	struct device *dev = &pdev->dev;
	struct bcm2835_wdt *wdt;
	int err;

	wdt = devm_kzalloc(dev, sizeof(struct bcm2835_wdt), GFP_KERNEL);
	if (!wdt)
		return -ENOMEM;

	spin_lock_init(&wdt->lock);

	wdt->base = pm->base;

	watchdog_set_drvdata(&bcm2835_wdt_wdd, wdt);
	watchdog_init_timeout(&bcm2835_wdt_wdd, heartbeat, dev);
	watchdog_set_nowayout(&bcm2835_wdt_wdd, nowayout);
	bcm2835_wdt_wdd.parent = dev;
	if (bcm2835_wdt_is_running(wdt)) {
		/*
		 * The currently active timeout value (set by the
		 * bootloader) may be different from the module
		 * heartbeat parameter or the value in device
		 * tree. But we just need to set WDOG_HW_RUNNING,
		 * because then the framework will "immediately" ping
		 * the device, updating the timeout.
		 */
		set_bit(WDOG_HW_RUNNING, &bcm2835_wdt_wdd.status);
	}

	watchdog_set_restart_priority(&bcm2835_wdt_wdd, 128);

	watchdog_stop_on_reboot(&bcm2835_wdt_wdd);
	err = devm_watchdog_register_device(dev, &bcm2835_wdt_wdd);
	if (err)
		return err;

	if (pm_power_off == NULL) {
		pm_power_off = bcm2835_power_off;
		bcm2835_power_off_wdt = wdt;
	}

	dev_info(dev, "Broadcom BCM2835 watchdog timer");
	return 0;
}
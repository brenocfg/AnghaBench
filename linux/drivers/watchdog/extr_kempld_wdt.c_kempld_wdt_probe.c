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
typedef  int u8 ;
struct watchdog_device {int /*<<< orphan*/  timeout; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * info; struct device* parent; } ;
struct device {int /*<<< orphan*/  parent; } ;
struct platform_device {struct device dev; } ;
struct kempld_wdt_data {struct watchdog_device wdd; struct kempld_device_data* pld; } ;
struct kempld_device_data {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KEMPLD_WDT_CFG ; 
 int KEMPLD_WDT_CFG_ENABLE ; 
 int KEMPLD_WDT_CFG_ENABLE_LOCK ; 
 int KEMPLD_WDT_CFG_GLOBAL_LOCK ; 
 struct kempld_device_data* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 struct kempld_wdt_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_watchdog_register_device (struct device*,struct watchdog_device*) ; 
 int /*<<< orphan*/  kempld_get_mutex (struct kempld_device_data*) ; 
 int kempld_read8 (struct kempld_device_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kempld_release_mutex (struct kempld_device_data*) ; 
 int /*<<< orphan*/  kempld_wdt_info ; 
 int /*<<< orphan*/  kempld_wdt_ops ; 
 int kempld_wdt_probe_stages (struct watchdog_device*) ; 
 int /*<<< orphan*/  kempld_wdt_set_pretimeout (struct watchdog_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kempld_wdt_set_timeout (struct watchdog_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kempld_wdt_update_timeouts (struct kempld_wdt_data*) ; 
 int nowayout ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct kempld_wdt_data*) ; 
 int /*<<< orphan*/  pretimeout ; 
 int /*<<< orphan*/  timeout ; 
 int /*<<< orphan*/  watchdog_set_drvdata (struct watchdog_device*,struct kempld_wdt_data*) ; 
 int /*<<< orphan*/  watchdog_set_nowayout (struct watchdog_device*,int) ; 
 int /*<<< orphan*/  watchdog_stop_on_reboot (struct watchdog_device*) ; 
 int /*<<< orphan*/  watchdog_stop_on_unregister (struct watchdog_device*) ; 

__attribute__((used)) static int kempld_wdt_probe(struct platform_device *pdev)
{
	struct kempld_device_data *pld = dev_get_drvdata(pdev->dev.parent);
	struct kempld_wdt_data *wdt_data;
	struct device *dev = &pdev->dev;
	struct watchdog_device *wdd;
	u8 status;
	int ret = 0;

	wdt_data = devm_kzalloc(dev, sizeof(*wdt_data), GFP_KERNEL);
	if (!wdt_data)
		return -ENOMEM;

	wdt_data->pld = pld;
	wdd = &wdt_data->wdd;
	wdd->parent = dev;

	kempld_get_mutex(pld);
	status = kempld_read8(pld, KEMPLD_WDT_CFG);
	kempld_release_mutex(pld);

	/* Enable nowayout if watchdog is already locked */
	if (status & (KEMPLD_WDT_CFG_ENABLE_LOCK |
			KEMPLD_WDT_CFG_GLOBAL_LOCK)) {
		if (!nowayout)
			dev_warn(dev,
				 "Forcing nowayout - watchdog lock enabled!\n");
		nowayout = true;
	}

	wdd->info = &kempld_wdt_info;
	wdd->ops = &kempld_wdt_ops;

	watchdog_set_drvdata(wdd, wdt_data);
	watchdog_set_nowayout(wdd, nowayout);

	ret = kempld_wdt_probe_stages(wdd);
	if (ret)
		return ret;

	kempld_wdt_set_timeout(wdd, timeout);
	kempld_wdt_set_pretimeout(wdd, pretimeout);

	/* Check if watchdog is already enabled */
	if (status & KEMPLD_WDT_CFG_ENABLE) {
		/* Get current watchdog settings */
		kempld_wdt_update_timeouts(wdt_data);
		dev_info(dev, "Watchdog was already enabled\n");
	}

	platform_set_drvdata(pdev, wdt_data);
	watchdog_stop_on_reboot(wdd);
	watchdog_stop_on_unregister(wdd);
	ret = devm_watchdog_register_device(dev, wdd);
	if (ret)
		return ret;

	dev_info(dev, "Watchdog registered with %ds timeout\n", wdd->timeout);

	return 0;
}
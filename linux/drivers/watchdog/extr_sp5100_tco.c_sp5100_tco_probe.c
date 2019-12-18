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
struct watchdog_device {int min_timeout; int max_timeout; int /*<<< orphan*/  timeout; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * info; struct device* parent; } ;
struct sp5100_tco {struct watchdog_device wdd; int /*<<< orphan*/  tco_reg_layout; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WATCHDOG_HEARTBEAT ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sp5100_tco* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_watchdog_register_device (struct device*,struct watchdog_device*) ; 
 int /*<<< orphan*/  heartbeat ; 
 int /*<<< orphan*/  nowayout ; 
 int /*<<< orphan*/  sp5100_tco_pci ; 
 int sp5100_tco_setupdevice (struct device*,struct watchdog_device*) ; 
 int /*<<< orphan*/  sp5100_tco_wdt_info ; 
 int /*<<< orphan*/  sp5100_tco_wdt_ops ; 
 int /*<<< orphan*/  tco_reg_layout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  watchdog_init_timeout (struct watchdog_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  watchdog_set_drvdata (struct watchdog_device*,struct sp5100_tco*) ; 
 int /*<<< orphan*/  watchdog_set_nowayout (struct watchdog_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  watchdog_stop_on_reboot (struct watchdog_device*) ; 
 int /*<<< orphan*/  watchdog_stop_on_unregister (struct watchdog_device*) ; 

__attribute__((used)) static int sp5100_tco_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct watchdog_device *wdd;
	struct sp5100_tco *tco;
	int ret;

	tco = devm_kzalloc(dev, sizeof(*tco), GFP_KERNEL);
	if (!tco)
		return -ENOMEM;

	tco->tco_reg_layout = tco_reg_layout(sp5100_tco_pci);

	wdd = &tco->wdd;
	wdd->parent = dev;
	wdd->info = &sp5100_tco_wdt_info;
	wdd->ops = &sp5100_tco_wdt_ops;
	wdd->timeout = WATCHDOG_HEARTBEAT;
	wdd->min_timeout = 1;
	wdd->max_timeout = 0xffff;

	watchdog_init_timeout(wdd, heartbeat, NULL);
	watchdog_set_nowayout(wdd, nowayout);
	watchdog_stop_on_reboot(wdd);
	watchdog_stop_on_unregister(wdd);
	watchdog_set_drvdata(wdd, tco);

	ret = sp5100_tco_setupdevice(dev, wdd);
	if (ret)
		return ret;

	ret = devm_watchdog_register_device(dev, wdd);
	if (ret)
		return ret;

	/* Show module parameters */
	dev_info(dev, "initialized. heartbeat=%d sec (nowayout=%d)\n",
		 wdd->timeout, nowayout);

	return 0;
}
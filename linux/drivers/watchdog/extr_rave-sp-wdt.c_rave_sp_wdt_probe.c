#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  timeout ;
struct watchdog_device {int max_timeout; int timeout; int max_hw_heartbeat_ms; int /*<<< orphan*/  status; int /*<<< orphan*/  min_timeout; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * info; struct device* parent; } ;
struct TYPE_4__ {int /*<<< orphan*/  notifier_call; } ;
struct rave_sp_wdt {TYPE_2__ reboot_notifier; TYPE_1__* variant; struct watchdog_device wdd; int /*<<< orphan*/  sp; } ;
struct device {int /*<<< orphan*/  parent; } ;
struct platform_device {struct device dev; } ;
typedef  void nvmem_cell ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_3__ {int max_timeout; int /*<<< orphan*/  min_timeout; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ERR (void*) ; 
 int /*<<< orphan*/  WATCHDOG_NOWAYOUT_INIT_STATUS ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct rave_sp_wdt* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_register_reboot_notifier (struct device*,TYPE_2__*) ; 
 int devm_watchdog_register_device (struct device*,struct watchdog_device*) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (size_t,int) ; 
 void* nvmem_cell_get (struct device*,char*) ; 
 int /*<<< orphan*/  nvmem_cell_put (void*) ; 
 void* nvmem_cell_read (void*,size_t*) ; 
 TYPE_1__* of_device_get_match_data (struct device*) ; 
 int /*<<< orphan*/  rave_sp_wdt_info ; 
 int /*<<< orphan*/  rave_sp_wdt_ops ; 
 int /*<<< orphan*/  rave_sp_wdt_reboot_notifier ; 
 int rave_sp_wdt_start (struct watchdog_device*) ; 
 int /*<<< orphan*/  rave_sp_wdt_stop (struct watchdog_device*) ; 
 int /*<<< orphan*/  watchdog_init_timeout (struct watchdog_device*,int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  watchdog_set_restart_priority (struct watchdog_device*,int) ; 
 int /*<<< orphan*/  watchdog_stop_on_unregister (struct watchdog_device*) ; 

__attribute__((used)) static int rave_sp_wdt_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct watchdog_device *wdd;
	struct rave_sp_wdt *sp_wd;
	struct nvmem_cell *cell;
	__le16 timeout = 0;
	int ret;

	sp_wd = devm_kzalloc(dev, sizeof(*sp_wd), GFP_KERNEL);
	if (!sp_wd)
		return -ENOMEM;

	sp_wd->variant = of_device_get_match_data(dev);
	sp_wd->sp      = dev_get_drvdata(dev->parent);

	wdd              = &sp_wd->wdd;
	wdd->parent      = dev;
	wdd->info        = &rave_sp_wdt_info;
	wdd->ops         = &rave_sp_wdt_ops;
	wdd->min_timeout = sp_wd->variant->min_timeout;
	wdd->max_timeout = sp_wd->variant->max_timeout;
	wdd->status      = WATCHDOG_NOWAYOUT_INIT_STATUS;
	wdd->timeout     = 60;

	cell = nvmem_cell_get(dev, "wdt-timeout");
	if (!IS_ERR(cell)) {
		size_t len;
		void *value = nvmem_cell_read(cell, &len);

		if (!IS_ERR(value)) {
			memcpy(&timeout, value, min(len, sizeof(timeout)));
			kfree(value);
		}
		nvmem_cell_put(cell);
	}
	watchdog_init_timeout(wdd, le16_to_cpu(timeout), dev);
	watchdog_set_restart_priority(wdd, 255);
	watchdog_stop_on_unregister(wdd);

	sp_wd->reboot_notifier.notifier_call = rave_sp_wdt_reboot_notifier;
	ret = devm_register_reboot_notifier(dev, &sp_wd->reboot_notifier);
	if (ret) {
		dev_err(dev, "Failed to register reboot notifier\n");
		return ret;
	}

	/*
	 * We don't know if watchdog is running now. To be sure, let's
	 * start it and depend on watchdog core to ping it
	 */
	wdd->max_hw_heartbeat_ms = wdd->max_timeout * 1000;
	ret = rave_sp_wdt_start(wdd);
	if (ret) {
		dev_err(dev, "Watchdog didn't start\n");
		return ret;
	}

	ret = devm_watchdog_register_device(dev, wdd);
	if (ret) {
		rave_sp_wdt_stop(wdd);
		return ret;
	}

	return 0;
}
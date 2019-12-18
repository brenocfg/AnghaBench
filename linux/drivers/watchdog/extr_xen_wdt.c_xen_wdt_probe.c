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
struct sched_watchdog {int /*<<< orphan*/  id; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  timeout; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOSYS ; 
 int HYPERVISOR_sched_op (int /*<<< orphan*/ ,struct sched_watchdog*) ; 
 int /*<<< orphan*/  SCHEDOP_watchdog ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int devm_watchdog_register_device (struct device*,TYPE_1__*) ; 
 int /*<<< orphan*/  nowayout ; 
 int /*<<< orphan*/  timeout ; 
 int /*<<< orphan*/  watchdog_init_timeout (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  watchdog_set_nowayout (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  watchdog_stop_on_reboot (TYPE_1__*) ; 
 int /*<<< orphan*/  watchdog_stop_on_unregister (TYPE_1__*) ; 
 TYPE_1__ xen_wdt_dev ; 

__attribute__((used)) static int xen_wdt_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct sched_watchdog wd = { .id = ~0 };
	int ret = HYPERVISOR_sched_op(SCHEDOP_watchdog, &wd);

	if (ret == -ENOSYS) {
		dev_err(dev, "watchdog not supported by hypervisor\n");
		return -ENODEV;
	}

	if (ret != -EINVAL) {
		dev_err(dev, "unexpected hypervisor error (%d)\n", ret);
		return -ENODEV;
	}

	watchdog_init_timeout(&xen_wdt_dev, timeout, NULL);
	watchdog_set_nowayout(&xen_wdt_dev, nowayout);
	watchdog_stop_on_reboot(&xen_wdt_dev);
	watchdog_stop_on_unregister(&xen_wdt_dev);

	ret = devm_watchdog_register_device(dev, &xen_wdt_dev);
	if (ret)
		return ret;

	dev_info(dev, "initialized (timeout=%ds, nowayout=%d)\n",
		 xen_wdt_dev.timeout, nowayout);

	return 0;
}
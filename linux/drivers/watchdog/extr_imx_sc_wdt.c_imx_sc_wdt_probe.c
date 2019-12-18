#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct watchdog_device {int min_timeout; int /*<<< orphan*/  timeout; struct device* parent; int /*<<< orphan*/  max_timeout; int /*<<< orphan*/ * ops; TYPE_2__* info; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  notifier_call; } ;
struct imx_sc_wdt_device {TYPE_1__ wdt_notifier; struct watchdog_device wdd; } ;
struct TYPE_5__ {int /*<<< orphan*/  options; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_TIMEOUT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MAX_TIMEOUT ; 
 int /*<<< orphan*/  SC_IRQ_GROUP_WDOG ; 
 int /*<<< orphan*/  SC_IRQ_WDOG ; 
 int /*<<< orphan*/  WDIOF_PRETIMEOUT ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 int devm_add_action_or_reset (struct device*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 struct imx_sc_wdt_device* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_watchdog_register_device (struct device*,struct watchdog_device*) ; 
 int /*<<< orphan*/  imx_sc_wdt_action ; 
 TYPE_2__ imx_sc_wdt_info ; 
 int /*<<< orphan*/  imx_sc_wdt_notify ; 
 int /*<<< orphan*/  imx_sc_wdt_ops ; 
 int imx_scu_irq_group_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int imx_scu_irq_register_notifier (TYPE_1__*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct imx_sc_wdt_device*) ; 
 int /*<<< orphan*/  watchdog_init_timeout (struct watchdog_device*,int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  watchdog_stop_on_reboot (struct watchdog_device*) ; 
 int /*<<< orphan*/  watchdog_stop_on_unregister (struct watchdog_device*) ; 

__attribute__((used)) static int imx_sc_wdt_probe(struct platform_device *pdev)
{
	struct imx_sc_wdt_device *imx_sc_wdd;
	struct watchdog_device *wdog;
	struct device *dev = &pdev->dev;
	int ret;

	imx_sc_wdd = devm_kzalloc(dev, sizeof(*imx_sc_wdd), GFP_KERNEL);
	if (!imx_sc_wdd)
		return -ENOMEM;

	platform_set_drvdata(pdev, imx_sc_wdd);

	wdog = &imx_sc_wdd->wdd;
	wdog->info = &imx_sc_wdt_info;
	wdog->ops = &imx_sc_wdt_ops;
	wdog->min_timeout = 1;
	wdog->max_timeout = MAX_TIMEOUT;
	wdog->parent = dev;
	wdog->timeout = DEFAULT_TIMEOUT;

	watchdog_init_timeout(wdog, 0, dev);
	watchdog_stop_on_reboot(wdog);
	watchdog_stop_on_unregister(wdog);

	ret = devm_watchdog_register_device(dev, wdog);
	if (ret)
		return ret;

	ret = imx_scu_irq_group_enable(SC_IRQ_GROUP_WDOG,
				       SC_IRQ_WDOG,
				       true);
	if (ret) {
		dev_warn(dev, "Enable irq failed, pretimeout NOT supported\n");
		return 0;
	}

	imx_sc_wdd->wdt_notifier.notifier_call = imx_sc_wdt_notify;
	ret = imx_scu_irq_register_notifier(&imx_sc_wdd->wdt_notifier);
	if (ret) {
		imx_scu_irq_group_enable(SC_IRQ_GROUP_WDOG,
					 SC_IRQ_WDOG,
					 false);
		dev_warn(dev,
			 "Register irq notifier failed, pretimeout NOT supported\n");
		return 0;
	}

	ret = devm_add_action_or_reset(dev, imx_sc_wdt_action,
				       &imx_sc_wdd->wdt_notifier);
	if (!ret)
		imx_sc_wdt_info.options |= WDIOF_PRETIMEOUT;
	else
		dev_warn(dev, "Add action failed, pretimeout NOT supported\n");

	return 0;
}
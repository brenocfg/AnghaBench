#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct TYPE_6__ {int min_timeout; int max_timeout; int timeout; int /*<<< orphan*/  status; struct device* parent; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * info; } ;
struct npcm_wdt {TYPE_1__ wdd; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WDOG_HW_RUNNING ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 struct npcm_wdt* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int devm_request_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct npcm_wdt*) ; 
 int devm_watchdog_register_device (struct device*,TYPE_1__*) ; 
 scalar_t__ npcm_is_running (TYPE_1__*) ; 
 int /*<<< orphan*/  npcm_wdt_info ; 
 int /*<<< orphan*/  npcm_wdt_interrupt ; 
 int /*<<< orphan*/  npcm_wdt_ops ; 
 int /*<<< orphan*/  npcm_wdt_set_timeout (TYPE_1__*,int) ; 
 int /*<<< orphan*/  npcm_wdt_start (TYPE_1__*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  watchdog_init_timeout (TYPE_1__*,int /*<<< orphan*/ ,struct device*) ; 

__attribute__((used)) static int npcm_wdt_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct npcm_wdt *wdt;
	int irq;
	int ret;

	wdt = devm_kzalloc(dev, sizeof(*wdt), GFP_KERNEL);
	if (!wdt)
		return -ENOMEM;

	wdt->reg = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(wdt->reg))
		return PTR_ERR(wdt->reg);

	irq = platform_get_irq(pdev, 0);
	if (irq < 0)
		return irq;

	wdt->wdd.info = &npcm_wdt_info;
	wdt->wdd.ops = &npcm_wdt_ops;
	wdt->wdd.min_timeout = 1;
	wdt->wdd.max_timeout = 2750;
	wdt->wdd.parent = dev;

	wdt->wdd.timeout = 86;
	watchdog_init_timeout(&wdt->wdd, 0, dev);

	/* Ensure timeout is able to be represented by the hardware */
	npcm_wdt_set_timeout(&wdt->wdd, wdt->wdd.timeout);

	if (npcm_is_running(&wdt->wdd)) {
		/* Restart with the default or device-tree specified timeout */
		npcm_wdt_start(&wdt->wdd);
		set_bit(WDOG_HW_RUNNING, &wdt->wdd.status);
	}

	ret = devm_request_irq(dev, irq, npcm_wdt_interrupt, 0, "watchdog",
			       wdt);
	if (ret)
		return ret;

	ret = devm_watchdog_register_device(dev, &wdt->wdd);
	if (ret)
		return ret;

	dev_info(dev, "NPCM watchdog driver enabled\n");

	return 0;
}
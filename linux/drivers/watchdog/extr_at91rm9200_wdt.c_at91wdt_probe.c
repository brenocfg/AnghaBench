#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct device {int /*<<< orphan*/  of_node; struct device* parent; } ;
struct platform_device {struct device dev; } ;
struct TYPE_3__ {struct device* parent; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  at91rm9200_restart_nb ; 
 TYPE_1__ at91wdt_miscdev ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 int misc_register (TYPE_1__*) ; 
 scalar_t__ nowayout ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,char*) ; 
 int register_restart_handler (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_st ; 
 int /*<<< orphan*/  syscon_node_to_regmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wdt_time ; 

__attribute__((used)) static int at91wdt_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device *parent;
	int res;

	if (at91wdt_miscdev.parent)
		return -EBUSY;
	at91wdt_miscdev.parent = &pdev->dev;

	parent = dev->parent;
	if (!parent) {
		dev_err(dev, "no parent\n");
		return -ENODEV;
	}

	regmap_st = syscon_node_to_regmap(parent->of_node);
	if (IS_ERR(regmap_st))
		return -ENODEV;

	res = misc_register(&at91wdt_miscdev);
	if (res)
		return res;

	res = register_restart_handler(&at91rm9200_restart_nb);
	if (res)
		dev_warn(dev, "failed to register restart handler\n");

	pr_info("AT91 Watchdog Timer enabled (%d seconds%s)\n",
		wdt_time, nowayout ? ", nowayout" : "");
	return 0;
}
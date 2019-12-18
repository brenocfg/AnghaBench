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
struct watchdog_device {struct device* parent; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * info; int /*<<< orphan*/  timeout; } ;
struct device {int /*<<< orphan*/  parent; } ;
struct platform_device {struct device dev; } ;
struct da9055_wdt_data {struct watchdog_device wdt; struct da9055* da9055; } ;
struct da9055 {struct device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA9055_DEF_TIMEOUT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  da9055_wdt_info ; 
 int /*<<< orphan*/  da9055_wdt_ops ; 
 int da9055_wdt_stop (struct watchdog_device*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct da9055* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct da9055_wdt_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_watchdog_register_device (struct device*,struct watchdog_device*) ; 
 int /*<<< orphan*/  nowayout ; 
 int /*<<< orphan*/  watchdog_set_drvdata (struct watchdog_device*,struct da9055_wdt_data*) ; 
 int /*<<< orphan*/  watchdog_set_nowayout (struct watchdog_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int da9055_wdt_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct da9055 *da9055 = dev_get_drvdata(dev->parent);
	struct da9055_wdt_data *driver_data;
	struct watchdog_device *da9055_wdt;
	int ret;

	driver_data = devm_kzalloc(dev, sizeof(*driver_data), GFP_KERNEL);
	if (!driver_data)
		return -ENOMEM;

	driver_data->da9055 = da9055;

	da9055_wdt = &driver_data->wdt;

	da9055_wdt->timeout = DA9055_DEF_TIMEOUT;
	da9055_wdt->info = &da9055_wdt_info;
	da9055_wdt->ops = &da9055_wdt_ops;
	da9055_wdt->parent = dev;
	watchdog_set_nowayout(da9055_wdt, nowayout);
	watchdog_set_drvdata(da9055_wdt, driver_data);

	ret = da9055_wdt_stop(da9055_wdt);
	if (ret < 0) {
		dev_err(dev, "Failed to stop watchdog, %d\n", ret);
		return ret;
	}

	ret = devm_watchdog_register_device(dev, &driver_data->wdt);
	if (ret != 0)
		dev_err(da9055->dev, "watchdog_register_device() failed: %d\n",
			ret);

	return ret;
}
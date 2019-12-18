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
struct da9052_wdt_data {struct watchdog_device wdt; struct da9052* da9052; } ;
struct da9052 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA9052_CONTROLD_TWDSCALE ; 
 int /*<<< orphan*/  DA9052_CONTROL_D_REG ; 
 int /*<<< orphan*/  DA9052_DEF_TIMEOUT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int da9052_reg_update (struct da9052*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  da9052_wdt_info ; 
 int /*<<< orphan*/  da9052_wdt_ops ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct da9052* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct da9052_wdt_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_watchdog_register_device (struct device*,struct watchdog_device*) ; 
 int /*<<< orphan*/  watchdog_set_drvdata (struct watchdog_device*,struct da9052_wdt_data*) ; 

__attribute__((used)) static int da9052_wdt_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct da9052 *da9052 = dev_get_drvdata(dev->parent);
	struct da9052_wdt_data *driver_data;
	struct watchdog_device *da9052_wdt;
	int ret;

	driver_data = devm_kzalloc(dev, sizeof(*driver_data), GFP_KERNEL);
	if (!driver_data)
		return -ENOMEM;
	driver_data->da9052 = da9052;

	da9052_wdt = &driver_data->wdt;

	da9052_wdt->timeout = DA9052_DEF_TIMEOUT;
	da9052_wdt->info = &da9052_wdt_info;
	da9052_wdt->ops = &da9052_wdt_ops;
	da9052_wdt->parent = dev;
	watchdog_set_drvdata(da9052_wdt, driver_data);

	ret = da9052_reg_update(da9052, DA9052_CONTROL_D_REG,
				DA9052_CONTROLD_TWDSCALE, 0);
	if (ret < 0) {
		dev_err(dev, "Failed to disable watchdog bits, %d\n", ret);
		return ret;
	}

	return devm_watchdog_register_device(dev, &driver_data->wdt);
}
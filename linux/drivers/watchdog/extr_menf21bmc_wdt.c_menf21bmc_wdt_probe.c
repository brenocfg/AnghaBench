#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct device {int /*<<< orphan*/  parent; } ;
struct platform_device {struct device dev; } ;
struct TYPE_5__ {struct device* parent; int /*<<< orphan*/  max_timeout; int /*<<< orphan*/  min_timeout; int /*<<< orphan*/ * info; int /*<<< orphan*/ * ops; } ;
struct menf21bmc_wdt {TYPE_1__ wdt; struct i2c_client* i2c_client; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMC_CMD_WD_TIME ; 
 int /*<<< orphan*/  BMC_WD_TIMEOUT_MAX ; 
 int /*<<< orphan*/  BMC_WD_TIMEOUT_MIN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 struct menf21bmc_wdt* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_watchdog_register_device (struct device*,TYPE_1__*) ; 
 int i2c_smbus_read_word_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  menf21bmc_wdt_info ; 
 int /*<<< orphan*/  menf21bmc_wdt_ops ; 
 int menf21bmc_wdt_set_bootstatus (struct menf21bmc_wdt*) ; 
 int /*<<< orphan*/  nowayout ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct menf21bmc_wdt*) ; 
 struct i2c_client* to_i2c_client (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  watchdog_init_timeout (TYPE_1__*,int,struct device*) ; 
 int /*<<< orphan*/  watchdog_set_drvdata (TYPE_1__*,struct menf21bmc_wdt*) ; 
 int /*<<< orphan*/  watchdog_set_nowayout (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int menf21bmc_wdt_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	int ret, bmc_timeout;
	struct menf21bmc_wdt *drv_data;
	struct i2c_client *i2c_client = to_i2c_client(dev->parent);

	drv_data = devm_kzalloc(dev, sizeof(struct menf21bmc_wdt), GFP_KERNEL);
	if (!drv_data)
		return -ENOMEM;

	drv_data->wdt.ops = &menf21bmc_wdt_ops;
	drv_data->wdt.info = &menf21bmc_wdt_info;
	drv_data->wdt.min_timeout = BMC_WD_TIMEOUT_MIN;
	drv_data->wdt.max_timeout = BMC_WD_TIMEOUT_MAX;
	drv_data->wdt.parent = dev;
	drv_data->i2c_client = i2c_client;

	/*
	 * Get the current wdt timeout value from the BMC because
	 * the BMC will save the value set before if the system restarts.
	 */
	bmc_timeout = i2c_smbus_read_word_data(drv_data->i2c_client,
					       BMC_CMD_WD_TIME);
	if (bmc_timeout < 0) {
		dev_err(dev, "failed to get current WDT timeout\n");
		return bmc_timeout;
	}

	watchdog_init_timeout(&drv_data->wdt, bmc_timeout / 10, dev);
	watchdog_set_nowayout(&drv_data->wdt, nowayout);
	watchdog_set_drvdata(&drv_data->wdt, drv_data);
	platform_set_drvdata(pdev, drv_data);

	ret = menf21bmc_wdt_set_bootstatus(drv_data);
	if (ret < 0) {
		dev_err(dev, "failed to set Watchdog bootstatus\n");
		return ret;
	}

	ret = devm_watchdog_register_device(dev, &drv_data->wdt);
	if (ret)
		return ret;

	dev_info(dev, "MEN 14F021P00 BMC Watchdog device enabled\n");

	return 0;
}
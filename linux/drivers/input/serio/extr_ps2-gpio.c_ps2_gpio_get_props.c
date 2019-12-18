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
struct ps2_gpio_data {int /*<<< orphan*/  write_enable; void* gpio_clk; void* gpio_data; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOD_IN ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  device_property_read_bool (struct device*,char*) ; 
 void* devm_gpiod_get (struct device*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ps2_gpio_get_props(struct device *dev,
				 struct ps2_gpio_data *drvdata)
{
	drvdata->gpio_data = devm_gpiod_get(dev, "data", GPIOD_IN);
	if (IS_ERR(drvdata->gpio_data)) {
		dev_err(dev, "failed to request data gpio: %ld",
			PTR_ERR(drvdata->gpio_data));
		return PTR_ERR(drvdata->gpio_data);
	}

	drvdata->gpio_clk = devm_gpiod_get(dev, "clk", GPIOD_IN);
	if (IS_ERR(drvdata->gpio_clk)) {
		dev_err(dev, "failed to request clock gpio: %ld",
			PTR_ERR(drvdata->gpio_clk));
		return PTR_ERR(drvdata->gpio_clk);
	}

	drvdata->write_enable = device_property_read_bool(dev,
				"write-enable");

	return 0;
}
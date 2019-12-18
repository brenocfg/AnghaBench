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
struct sx9500_data {struct gpio_desc* gpiod_rst; } ;
struct device {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  irq; struct device dev; } ;
struct gpio_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOD_IN ; 
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 scalar_t__ IS_ERR (struct gpio_desc*) ; 
 int /*<<< orphan*/  acpi_sx9500_gpios ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 int devm_acpi_dev_add_driver_gpios (struct device*,int /*<<< orphan*/ ) ; 
 void* devm_gpiod_get (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_to_irq (struct gpio_desc*) ; 

__attribute__((used)) static void sx9500_gpio_probe(struct i2c_client *client,
			      struct sx9500_data *data)
{
	struct gpio_desc *gpiod_int;
	struct device *dev;
	int ret;

	if (!client)
		return;

	dev = &client->dev;

	ret = devm_acpi_dev_add_driver_gpios(dev, acpi_sx9500_gpios);
	if (ret)
		dev_dbg(dev, "Unable to add GPIO mapping table\n");

	if (client->irq <= 0) {
		gpiod_int = devm_gpiod_get(dev, "interrupt", GPIOD_IN);
		if (IS_ERR(gpiod_int))
			dev_err(dev, "gpio get irq failed\n");
		else
			client->irq = gpiod_to_irq(gpiod_int);
	}

	data->gpiod_rst = devm_gpiod_get(dev, "reset", GPIOD_OUT_HIGH);
	if (IS_ERR(data->gpiod_rst)) {
		dev_warn(dev, "gpio get reset pin failed\n");
		data->gpiod_rst = NULL;
	}
}
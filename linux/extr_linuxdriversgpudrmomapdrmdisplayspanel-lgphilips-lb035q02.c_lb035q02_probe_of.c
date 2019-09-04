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
struct spi_device {int /*<<< orphan*/  dev; } ;
struct panel_drv_data {struct gpio_desc* enable_gpio; } ;
struct gpio_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (struct gpio_desc*) ; 
 int PTR_ERR (struct gpio_desc*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct panel_drv_data* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 struct gpio_desc* devm_gpiod_get (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lb035q02_probe_of(struct spi_device *spi)
{
	struct panel_drv_data *ddata = dev_get_drvdata(&spi->dev);
	struct gpio_desc *gpio;

	gpio = devm_gpiod_get(&spi->dev, "enable", GPIOD_OUT_LOW);
	if (IS_ERR(gpio)) {
		dev_err(&spi->dev, "failed to parse enable gpio\n");
		return PTR_ERR(gpio);
	}

	ddata->enable_gpio = gpio;

	return 0;
}
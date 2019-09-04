#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct surface3_ts_data {struct gpio_desc** gpiod_rst; TYPE_1__* spi; } ;
struct gpio_desc {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (struct gpio_desc*) ; 
 int PTR_ERR (struct gpio_desc*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,int) ; 
 struct gpio_desc* devm_gpiod_get_index (struct device*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int surface3_spi_get_gpio_config(struct surface3_ts_data *data)
{
	int error;
	struct device *dev;
	struct gpio_desc *gpiod;
	int i;

	dev = &data->spi->dev;

	/* Get the reset lines GPIO pin number */
	for (i = 0; i < 2; i++) {
		gpiod = devm_gpiod_get_index(dev, NULL, i, GPIOD_OUT_LOW);
		if (IS_ERR(gpiod)) {
			error = PTR_ERR(gpiod);
			if (error != -EPROBE_DEFER)
				dev_err(dev,
					"Failed to get power GPIO %d: %d\n",
					i,
					error);
			return error;
		}

		data->gpiod_rst[i] = gpiod;
	}

	return 0;
}
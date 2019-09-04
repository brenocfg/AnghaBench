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
struct gpio_desc {int dummy; } ;
struct goodix_ts_data {struct gpio_desc* gpiod_rst; struct gpio_desc* gpiod_int; TYPE_1__* client; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GOODIX_GPIO_INT_NAME ; 
 int /*<<< orphan*/  GOODIX_GPIO_RST_NAME ; 
 int /*<<< orphan*/  GPIOD_IN ; 
 scalar_t__ IS_ERR (struct gpio_desc*) ; 
 int PTR_ERR (struct gpio_desc*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,int) ; 
 struct gpio_desc* devm_gpiod_get_optional (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int goodix_get_gpio_config(struct goodix_ts_data *ts)
{
	int error;
	struct device *dev;
	struct gpio_desc *gpiod;

	if (!ts->client)
		return -EINVAL;
	dev = &ts->client->dev;

	/* Get the interrupt GPIO pin number */
	gpiod = devm_gpiod_get_optional(dev, GOODIX_GPIO_INT_NAME, GPIOD_IN);
	if (IS_ERR(gpiod)) {
		error = PTR_ERR(gpiod);
		if (error != -EPROBE_DEFER)
			dev_dbg(dev, "Failed to get %s GPIO: %d\n",
				GOODIX_GPIO_INT_NAME, error);
		return error;
	}

	ts->gpiod_int = gpiod;

	/* Get the reset line GPIO pin number */
	gpiod = devm_gpiod_get_optional(dev, GOODIX_GPIO_RST_NAME, GPIOD_IN);
	if (IS_ERR(gpiod)) {
		error = PTR_ERR(gpiod);
		if (error != -EPROBE_DEFER)
			dev_dbg(dev, "Failed to get %s GPIO: %d\n",
				GOODIX_GPIO_RST_NAME, error);
		return error;
	}

	ts->gpiod_rst = gpiod;

	return 0;
}
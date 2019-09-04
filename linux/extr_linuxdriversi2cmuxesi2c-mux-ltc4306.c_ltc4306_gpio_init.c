#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int base; int can_sleep; int /*<<< orphan*/  owner; int /*<<< orphan*/  set_config; int /*<<< orphan*/  set; int /*<<< orphan*/  get; int /*<<< orphan*/  direction_output; int /*<<< orphan*/  direction_input; int /*<<< orphan*/  get_direction; struct device* parent; scalar_t__ ngpio; int /*<<< orphan*/  label; } ;
struct ltc4306 {TYPE_2__ gpiochip; int /*<<< orphan*/  regmap; TYPE_1__* chip; } ;
struct device {int dummy; } ;
struct TYPE_3__ {scalar_t__ num_gpios; } ;

/* Variables and functions */
 int /*<<< orphan*/  LTC_GPIO_ALL_INPUT ; 
 int /*<<< orphan*/  LTC_REG_MODE ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int devm_gpiochip_add_data (struct device*,TYPE_2__*,struct ltc4306*) ; 
 int /*<<< orphan*/  ltc4306_gpio_direction_input ; 
 int /*<<< orphan*/  ltc4306_gpio_direction_output ; 
 int /*<<< orphan*/  ltc4306_gpio_get ; 
 int /*<<< orphan*/  ltc4306_gpio_get_direction ; 
 int /*<<< orphan*/  ltc4306_gpio_set ; 
 int /*<<< orphan*/  ltc4306_gpio_set_config ; 
 struct device* regmap_get_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ltc4306_gpio_init(struct ltc4306 *data)
{
	struct device *dev = regmap_get_device(data->regmap);

	if (!data->chip->num_gpios)
		return 0;

	data->gpiochip.label = dev_name(dev);
	data->gpiochip.base = -1;
	data->gpiochip.ngpio = data->chip->num_gpios;
	data->gpiochip.parent = dev;
	data->gpiochip.can_sleep = true;
	data->gpiochip.get_direction = ltc4306_gpio_get_direction;
	data->gpiochip.direction_input = ltc4306_gpio_direction_input;
	data->gpiochip.direction_output = ltc4306_gpio_direction_output;
	data->gpiochip.get = ltc4306_gpio_get;
	data->gpiochip.set = ltc4306_gpio_set;
	data->gpiochip.set_config = ltc4306_gpio_set_config;
	data->gpiochip.owner = THIS_MODULE;

	/* gpiolib assumes all GPIOs default input */
	regmap_write(data->regmap, LTC_REG_MODE, LTC_GPIO_ALL_INPUT);

	return devm_gpiochip_add_data(dev, &data->gpiochip, data);
}
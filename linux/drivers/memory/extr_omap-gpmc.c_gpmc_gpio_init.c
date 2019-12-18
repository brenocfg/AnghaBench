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
struct TYPE_2__ {int base; int /*<<< orphan*/  get; int /*<<< orphan*/  set; int /*<<< orphan*/  direction_output; int /*<<< orphan*/  direction_input; int /*<<< orphan*/  get_direction; int /*<<< orphan*/  ngpio; int /*<<< orphan*/  label; int /*<<< orphan*/  owner; int /*<<< orphan*/  parent; } ;
struct gpmc_device {int /*<<< orphan*/  dev; TYPE_1__ gpio_chip; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_NAME ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int devm_gpiochip_add_data (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gpmc_gpio_direction_input ; 
 int /*<<< orphan*/  gpmc_gpio_direction_output ; 
 int /*<<< orphan*/  gpmc_gpio_get ; 
 int /*<<< orphan*/  gpmc_gpio_get_direction ; 
 int /*<<< orphan*/  gpmc_gpio_set ; 
 int /*<<< orphan*/  gpmc_nr_waitpins ; 

__attribute__((used)) static int gpmc_gpio_init(struct gpmc_device *gpmc)
{
	int ret;

	gpmc->gpio_chip.parent = gpmc->dev;
	gpmc->gpio_chip.owner = THIS_MODULE;
	gpmc->gpio_chip.label = DEVICE_NAME;
	gpmc->gpio_chip.ngpio = gpmc_nr_waitpins;
	gpmc->gpio_chip.get_direction = gpmc_gpio_get_direction;
	gpmc->gpio_chip.direction_input = gpmc_gpio_direction_input;
	gpmc->gpio_chip.direction_output = gpmc_gpio_direction_output;
	gpmc->gpio_chip.set = gpmc_gpio_set;
	gpmc->gpio_chip.get = gpmc_gpio_get;
	gpmc->gpio_chip.base = -1;

	ret = devm_gpiochip_add_data(gpmc->dev, &gpmc->gpio_chip, NULL);
	if (ret < 0) {
		dev_err(gpmc->dev, "could not register gpio chip: %d\n", ret);
		return ret;
	}

	return 0;
}
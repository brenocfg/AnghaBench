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
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct htcpld_data {struct htcpld_chip* chip; } ;
struct htcpld_core_platform_data {struct htcpld_chip_platform_data* chip; } ;
struct htcpld_chip_platform_data {int /*<<< orphan*/  addr; int /*<<< orphan*/  num_gpios; int /*<<< orphan*/  gpio_in_base; int /*<<< orphan*/  gpio_out_base; } ;
struct gpio_chip {char* label; int /*<<< orphan*/  ngpio; int /*<<< orphan*/  base; int /*<<< orphan*/  to_irq; int /*<<< orphan*/ * direction_output; int /*<<< orphan*/ * direction_input; int /*<<< orphan*/ * set; void* get; void* owner; struct device* parent; } ;
struct htcpld_chip {struct gpio_chip chip_out; struct gpio_chip chip_in; } ;

/* Variables and functions */
 void* THIS_MODULE ; 
 struct htcpld_core_platform_data* dev_get_platdata (struct device*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int /*<<< orphan*/ ,int) ; 
 int gpiochip_add_data (struct gpio_chip*,struct htcpld_chip*) ; 
 int /*<<< orphan*/  gpiochip_remove (struct gpio_chip*) ; 
 void* htcpld_chip_get ; 
 int /*<<< orphan*/ * htcpld_chip_set ; 
 int /*<<< orphan*/  htcpld_chip_to_irq ; 
 int /*<<< orphan*/ * htcpld_direction_input ; 
 int /*<<< orphan*/ * htcpld_direction_output ; 
 struct htcpld_data* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int htcpld_register_chip_gpio(
		struct platform_device *pdev,
		int chip_index)
{
	struct htcpld_data *htcpld;
	struct device *dev = &pdev->dev;
	struct htcpld_core_platform_data *pdata;
	struct htcpld_chip *chip;
	struct htcpld_chip_platform_data *plat_chip_data;
	struct gpio_chip *gpio_chip;
	int ret = 0;

	/* Get the platform and driver data */
	pdata = dev_get_platdata(dev);
	htcpld = platform_get_drvdata(pdev);
	chip = &htcpld->chip[chip_index];
	plat_chip_data = &pdata->chip[chip_index];

	/* Setup the GPIO chips */
	gpio_chip = &(chip->chip_out);
	gpio_chip->label           = "htcpld-out";
	gpio_chip->parent             = dev;
	gpio_chip->owner           = THIS_MODULE;
	gpio_chip->get             = htcpld_chip_get;
	gpio_chip->set             = htcpld_chip_set;
	gpio_chip->direction_input = NULL;
	gpio_chip->direction_output = htcpld_direction_output;
	gpio_chip->base            = plat_chip_data->gpio_out_base;
	gpio_chip->ngpio           = plat_chip_data->num_gpios;

	gpio_chip = &(chip->chip_in);
	gpio_chip->label           = "htcpld-in";
	gpio_chip->parent             = dev;
	gpio_chip->owner           = THIS_MODULE;
	gpio_chip->get             = htcpld_chip_get;
	gpio_chip->set             = NULL;
	gpio_chip->direction_input = htcpld_direction_input;
	gpio_chip->direction_output = NULL;
	gpio_chip->to_irq          = htcpld_chip_to_irq;
	gpio_chip->base            = plat_chip_data->gpio_in_base;
	gpio_chip->ngpio           = plat_chip_data->num_gpios;

	/* Add the GPIO chips */
	ret = gpiochip_add_data(&(chip->chip_out), chip);
	if (ret) {
		dev_warn(dev, "Unable to register output GPIOs for 0x%x: %d\n",
			 plat_chip_data->addr, ret);
		return ret;
	}

	ret = gpiochip_add_data(&(chip->chip_in), chip);
	if (ret) {
		dev_warn(dev, "Unable to register input GPIOs for 0x%x: %d\n",
			 plat_chip_data->addr, ret);
		gpiochip_remove(&(chip->chip_out));
		return ret;
	}

	return 0;
}
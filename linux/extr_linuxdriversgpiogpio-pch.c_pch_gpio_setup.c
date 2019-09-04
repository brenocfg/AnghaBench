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
struct gpio_chip {int base; int can_sleep; int /*<<< orphan*/  to_irq; int /*<<< orphan*/  ngpio; int /*<<< orphan*/ * dbg_show; int /*<<< orphan*/  set; int /*<<< orphan*/  direction_output; int /*<<< orphan*/  get; int /*<<< orphan*/  direction_input; int /*<<< orphan*/  owner; int /*<<< orphan*/  parent; int /*<<< orphan*/  label; } ;
struct pch_gpio {size_t ioh; int /*<<< orphan*/  dev; struct gpio_chip gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gpio_pins ; 
 int /*<<< orphan*/  pch_gpio_direction_input ; 
 int /*<<< orphan*/  pch_gpio_direction_output ; 
 int /*<<< orphan*/  pch_gpio_get ; 
 int /*<<< orphan*/  pch_gpio_set ; 
 int /*<<< orphan*/  pch_gpio_to_irq ; 

__attribute__((used)) static void pch_gpio_setup(struct pch_gpio *chip)
{
	struct gpio_chip *gpio = &chip->gpio;

	gpio->label = dev_name(chip->dev);
	gpio->parent = chip->dev;
	gpio->owner = THIS_MODULE;
	gpio->direction_input = pch_gpio_direction_input;
	gpio->get = pch_gpio_get;
	gpio->direction_output = pch_gpio_direction_output;
	gpio->set = pch_gpio_set;
	gpio->dbg_show = NULL;
	gpio->base = -1;
	gpio->ngpio = gpio_pins[chip->ioh];
	gpio->can_sleep = false;
	gpio->to_irq = pch_gpio_to_irq;
}
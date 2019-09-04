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
struct gpio_chip {int base; int ngpio; int can_sleep; int /*<<< orphan*/  to_irq; int /*<<< orphan*/ * dbg_show; int /*<<< orphan*/  set; int /*<<< orphan*/  direction_output; int /*<<< orphan*/  get; int /*<<< orphan*/  direction_input; int /*<<< orphan*/  owner; int /*<<< orphan*/  label; } ;
struct ioh_gpio {int /*<<< orphan*/  dev; struct gpio_chip gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioh_gpio_direction_input ; 
 int /*<<< orphan*/  ioh_gpio_direction_output ; 
 int /*<<< orphan*/  ioh_gpio_get ; 
 int /*<<< orphan*/  ioh_gpio_set ; 
 int /*<<< orphan*/  ioh_gpio_to_irq ; 

__attribute__((used)) static void ioh_gpio_setup(struct ioh_gpio *chip, int num_port)
{
	struct gpio_chip *gpio = &chip->gpio;

	gpio->label = dev_name(chip->dev);
	gpio->owner = THIS_MODULE;
	gpio->direction_input = ioh_gpio_direction_input;
	gpio->get = ioh_gpio_get;
	gpio->direction_output = ioh_gpio_direction_output;
	gpio->set = ioh_gpio_set;
	gpio->dbg_show = NULL;
	gpio->base = -1;
	gpio->ngpio = num_port;
	gpio->can_sleep = false;
	gpio->to_irq = ioh_gpio_to_irq;
}
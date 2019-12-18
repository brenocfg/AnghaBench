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
struct gpio_chip {int base; int can_sleep; int /*<<< orphan*/  to_irq; int /*<<< orphan*/  ngpio; int /*<<< orphan*/ * dbg_show; int /*<<< orphan*/  set; int /*<<< orphan*/  direction_output; int /*<<< orphan*/  get; int /*<<< orphan*/  direction_input; int /*<<< orphan*/  owner; int /*<<< orphan*/  label; } ;
struct gsta_gpio {int /*<<< orphan*/  dev; struct gpio_chip gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  GSTA_NR_GPIO ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gsta_gpio_direction_input ; 
 int /*<<< orphan*/  gsta_gpio_direction_output ; 
 int /*<<< orphan*/  gsta_gpio_get ; 
 int /*<<< orphan*/  gsta_gpio_set ; 
 int /*<<< orphan*/  gsta_gpio_to_irq ; 

__attribute__((used)) static void gsta_gpio_setup(struct gsta_gpio *chip) /* called from probe */
{
	struct gpio_chip *gpio = &chip->gpio;

	/*
	 * ARCH_NR_GPIOS is currently 256 and dynamic allocation starts
	 * from the end. However, for compatibility, we need the first
	 * ConneXt device to start from gpio 0: it's the main chipset
	 * on most boards so documents and drivers assume gpio0..gpio127
	 */
	static int gpio_base;

	gpio->label = dev_name(chip->dev);
	gpio->owner = THIS_MODULE;
	gpio->direction_input = gsta_gpio_direction_input;
	gpio->get = gsta_gpio_get;
	gpio->direction_output = gsta_gpio_direction_output;
	gpio->set = gsta_gpio_set;
	gpio->dbg_show = NULL;
	gpio->base = gpio_base;
	gpio->ngpio = GSTA_NR_GPIO;
	gpio->can_sleep = false;
	gpio->to_irq = gsta_gpio_to_irq;

	/*
	 * After the first device, turn to dynamic gpio numbers.
	 * For example, with ARCH_NR_GPIOS = 256 we can fit two cards
	 */
	if (!gpio_base)
		gpio_base = -1;
}
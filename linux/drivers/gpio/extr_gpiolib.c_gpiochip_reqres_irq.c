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
struct gpio_chip {TYPE_1__* gpiodev; } ;
struct TYPE_2__ {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  chip_err (struct gpio_chip*,char*,unsigned int) ; 
 int gpiochip_lock_as_irq (struct gpio_chip*,unsigned int) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

int gpiochip_reqres_irq(struct gpio_chip *chip, unsigned int offset)
{
	int ret;

	if (!try_module_get(chip->gpiodev->owner))
		return -ENODEV;

	ret = gpiochip_lock_as_irq(chip, offset);
	if (ret) {
		chip_err(chip, "unable to lock HW IRQ %u for IRQ\n", offset);
		module_put(chip->gpiodev->owner);
		return ret;
	}
	return 0;
}
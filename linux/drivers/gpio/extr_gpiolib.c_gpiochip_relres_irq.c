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
 int /*<<< orphan*/  gpiochip_unlock_as_irq (struct gpio_chip*,unsigned int) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 

void gpiochip_relres_irq(struct gpio_chip *chip, unsigned int offset)
{
	gpiochip_unlock_as_irq(chip, offset);
	module_put(chip->gpiodev->owner);
}
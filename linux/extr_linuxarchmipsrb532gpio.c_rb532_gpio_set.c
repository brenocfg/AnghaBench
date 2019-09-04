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
struct rb532_gpio_chip {scalar_t__ regbase; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 scalar_t__ GPIOD ; 
 struct rb532_gpio_chip* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  rb532_set_bit (int,unsigned int,scalar_t__) ; 

__attribute__((used)) static void rb532_gpio_set(struct gpio_chip *chip,
				unsigned offset, int value)
{
	struct rb532_gpio_chip	*gpch;

	gpch = gpiochip_get_data(chip);
	rb532_set_bit(value, offset, gpch->regbase + GPIOD);
}
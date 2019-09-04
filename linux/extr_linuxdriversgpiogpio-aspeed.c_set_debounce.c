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
struct gpio_chip {int dummy; } ;
struct aspeed_gpio {int dummy; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 int disable_debounce (struct gpio_chip*,unsigned int) ; 
 int enable_debounce (struct gpio_chip*,unsigned int,unsigned long) ; 
 struct aspeed_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  have_debounce (struct aspeed_gpio*,unsigned int) ; 

__attribute__((used)) static int set_debounce(struct gpio_chip *chip, unsigned int offset,
				    unsigned long usecs)
{
	struct aspeed_gpio *gpio = gpiochip_get_data(chip);

	if (!have_debounce(gpio, offset))
		return -ENOTSUPP;

	if (usecs)
		return enable_debounce(chip, offset, usecs);

	return disable_debounce(chip, offset);
}
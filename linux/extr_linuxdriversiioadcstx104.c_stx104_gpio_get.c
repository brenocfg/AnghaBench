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
struct stx104_gpio {int /*<<< orphan*/  base; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 int EINVAL ; 
 struct stx104_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int inb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stx104_gpio_get(struct gpio_chip *chip, unsigned int offset)
{
	struct stx104_gpio *const stx104gpio = gpiochip_get_data(chip);

	if (offset >= 4)
		return -EINVAL;

	return !!(inb(stx104gpio->base) & BIT(offset));
}
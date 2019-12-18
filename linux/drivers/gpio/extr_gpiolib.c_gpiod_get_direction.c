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
struct gpio_desc {int /*<<< orphan*/  flags; } ;
struct gpio_chip {int (* get_direction ) (struct gpio_chip*,unsigned int) ;} ;

/* Variables and functions */
 int ENOTSUPP ; 
 int /*<<< orphan*/  FLAG_IS_OUT ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 unsigned int gpio_chip_hwgpio (struct gpio_desc*) ; 
 struct gpio_chip* gpiod_to_chip (struct gpio_desc*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub1 (struct gpio_chip*,unsigned int) ; 

int gpiod_get_direction(struct gpio_desc *desc)
{
	struct gpio_chip *chip;
	unsigned offset;
	int ret;

	chip = gpiod_to_chip(desc);
	offset = gpio_chip_hwgpio(desc);

	if (!chip->get_direction)
		return -ENOTSUPP;

	ret = chip->get_direction(chip, offset);
	if (ret > 0) {
		/* GPIOF_DIR_IN, or other positive */
		ret = 1;
		clear_bit(FLAG_IS_OUT, &desc->flags);
	}
	if (ret == 0) {
		/* GPIOF_DIR_OUT */
		set_bit(FLAG_IS_OUT, &desc->flags);
	}
	return ret;
}
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
struct tb10x_gpio {int dummy; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 int /*<<< orphan*/  OFFSET_TO_REG_DDR ; 
 unsigned int TB10X_GPIO_DIR_OUT ; 
 struct tb10x_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  tb10x_gpio_set (struct gpio_chip*,unsigned int,int) ; 
 int /*<<< orphan*/  tb10x_set_bits (struct tb10x_gpio*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int tb10x_gpio_direction_out(struct gpio_chip *chip,
					unsigned offset, int value)
{
	struct tb10x_gpio *tb10x_gpio = gpiochip_get_data(chip);
	int mask = BIT(offset);
	int val = TB10X_GPIO_DIR_OUT << offset;

	tb10x_gpio_set(chip, offset, value);
	tb10x_set_bits(tb10x_gpio, OFFSET_TO_REG_DDR, mask, val);

	return 0;
}
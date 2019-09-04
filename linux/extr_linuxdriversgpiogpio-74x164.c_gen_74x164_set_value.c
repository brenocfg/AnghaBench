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
typedef  size_t u8 ;
struct gpio_chip {int dummy; } ;
struct gen_74x164_chip {int registers; int* buffer; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __gen_74x164_write_config (struct gen_74x164_chip*) ; 
 struct gen_74x164_chip* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gen_74x164_set_value(struct gpio_chip *gc,
		unsigned offset, int val)
{
	struct gen_74x164_chip *chip = gpiochip_get_data(gc);
	u8 bank = chip->registers - 1 - offset / 8;
	u8 pin = offset % 8;

	mutex_lock(&chip->lock);
	if (val)
		chip->buffer[bank] |= (1 << pin);
	else
		chip->buffer[bank] &= ~(1 << pin);

	__gen_74x164_write_config(chip);
	mutex_unlock(&chip->lock);
}
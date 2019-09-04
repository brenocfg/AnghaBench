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
struct gen_74x164_chip {int registers; size_t* buffer; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 struct gen_74x164_chip* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gen_74x164_get_value(struct gpio_chip *gc, unsigned offset)
{
	struct gen_74x164_chip *chip = gpiochip_get_data(gc);
	u8 bank = chip->registers - 1 - offset / 8;
	u8 pin = offset % 8;
	int ret;

	mutex_lock(&chip->lock);
	ret = (chip->buffer[bank] >> pin) & 0x1;
	mutex_unlock(&chip->lock);

	return ret;
}
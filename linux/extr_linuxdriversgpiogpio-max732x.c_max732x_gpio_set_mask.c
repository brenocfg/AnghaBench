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
typedef  int uint8_t ;
struct max732x_chip {int* reg_out; int /*<<< orphan*/  lock; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 struct max732x_chip* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  is_group_a (struct max732x_chip*,unsigned int) ; 
 int max732x_writeb (struct max732x_chip*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void max732x_gpio_set_mask(struct gpio_chip *gc, unsigned off, int mask,
				  int val)
{
	struct max732x_chip *chip = gpiochip_get_data(gc);
	uint8_t reg_out;
	int ret;

	mutex_lock(&chip->lock);

	reg_out = (off > 7) ? chip->reg_out[1] : chip->reg_out[0];
	reg_out = (reg_out & ~mask) | (val & mask);

	ret = max732x_writeb(chip, is_group_a(chip, off), reg_out);
	if (ret < 0)
		goto out;

	/* update the shadow register then */
	if (off > 7)
		chip->reg_out[1] = reg_out;
	else
		chip->reg_out[0] = reg_out;
out:
	mutex_unlock(&chip->lock);
}
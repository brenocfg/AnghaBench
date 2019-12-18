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
struct sch311x_gpio_block {int /*<<< orphan*/  lock; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __sch311x_gpio_set (struct sch311x_gpio_block*,unsigned int,int) ; 
 struct sch311x_gpio_block* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sch311x_gpio_set(struct gpio_chip *chip, unsigned offset,
			     int value)
{
	struct sch311x_gpio_block *block = gpiochip_get_data(chip);

	spin_lock(&block->lock);
	__sch311x_gpio_set(block, offset, value);
	spin_unlock(&block->lock);
}
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
struct rdc321x_gpio {int /*<<< orphan*/  lock; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 struct rdc321x_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  rdc_gpio_set_value_impl (struct gpio_chip*,unsigned int,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rdc_gpio_set_value(struct gpio_chip *chip,
				unsigned gpio, int value)
{
	struct rdc321x_gpio *gpch;

	gpch = gpiochip_get_data(chip);
	spin_lock(&gpch->lock);
	rdc_gpio_set_value_impl(chip, gpio, value);
	spin_unlock(&gpch->lock);
}
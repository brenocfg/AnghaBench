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
typedef  int /*<<< orphan*/  u32 ;
struct zevio_gpio {int /*<<< orphan*/  lock; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZEVIO_GPIO_BIT (unsigned int) ; 
 int /*<<< orphan*/  ZEVIO_GPIO_DIRECTION ; 
 struct zevio_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zevio_gpio_port_get (struct zevio_gpio*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zevio_gpio_port_set (struct zevio_gpio*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zevio_gpio_direction_input(struct gpio_chip *chip, unsigned pin)
{
	struct zevio_gpio *controller = gpiochip_get_data(chip);
	u32 val;

	spin_lock(&controller->lock);

	val = zevio_gpio_port_get(controller, pin, ZEVIO_GPIO_DIRECTION);
	val |= BIT(ZEVIO_GPIO_BIT(pin));
	zevio_gpio_port_set(controller, pin, ZEVIO_GPIO_DIRECTION, val);

	spin_unlock(&controller->lock);

	return 0;
}
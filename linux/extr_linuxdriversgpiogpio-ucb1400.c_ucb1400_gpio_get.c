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
struct ucb1400_gpio {int /*<<< orphan*/  ac97; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 struct ucb1400_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  ucb1400_gpio_get_value (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int ucb1400_gpio_get(struct gpio_chip *gc, unsigned off)
{
	struct ucb1400_gpio *gpio;

	gpio = gpiochip_get_data(gc);
	return !!ucb1400_gpio_get_value(gpio->ac97, off);
}
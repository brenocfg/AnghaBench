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
struct ingenic_gpio_chip {int dummy; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 struct ingenic_gpio_chip* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  ingenic_gpio_set_value (struct ingenic_gpio_chip*,unsigned int,int) ; 

__attribute__((used)) static void ingenic_gpio_set(struct gpio_chip *gc,
		unsigned int offset, int value)
{
	struct ingenic_gpio_chip *jzgc = gpiochip_get_data(gc);

	ingenic_gpio_set_value(jzgc, offset, value);
}
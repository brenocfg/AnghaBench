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
 scalar_t__ ingenic_gpio_get_value (struct ingenic_gpio_chip*,unsigned int) ; 

__attribute__((used)) static int ingenic_gpio_get(struct gpio_chip *gc, unsigned int offset)
{
	struct ingenic_gpio_chip *jzgc = gpiochip_get_data(gc);

	return (int) ingenic_gpio_get_value(jzgc, offset);
}
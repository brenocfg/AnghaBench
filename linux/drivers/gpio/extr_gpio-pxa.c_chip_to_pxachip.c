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
struct pxa_gpio_chip {int dummy; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 struct pxa_gpio_chip* gpiochip_get_data (struct gpio_chip*) ; 

__attribute__((used)) static inline struct pxa_gpio_chip *chip_to_pxachip(struct gpio_chip *c)
{
	struct pxa_gpio_chip *pxa_chip = gpiochip_get_data(c);

	return pxa_chip;
}
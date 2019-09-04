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
struct lpc18xx_gpio_chip {unsigned int base; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 struct lpc18xx_gpio_chip* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  writeb (int,unsigned int) ; 

__attribute__((used)) static void lpc18xx_gpio_set(struct gpio_chip *chip, unsigned offset, int value)
{
	struct lpc18xx_gpio_chip *gc = gpiochip_get_data(chip);
	writeb(value ? 1 : 0, gc->base + offset);
}
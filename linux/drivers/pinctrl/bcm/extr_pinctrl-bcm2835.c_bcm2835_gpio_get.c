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
struct gpio_chip {int dummy; } ;
struct bcm2835_pinctrl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPLEV0 ; 
 int bcm2835_gpio_get_bit (struct bcm2835_pinctrl*,int /*<<< orphan*/ ,unsigned int) ; 
 struct bcm2835_pinctrl* gpiochip_get_data (struct gpio_chip*) ; 

__attribute__((used)) static int bcm2835_gpio_get(struct gpio_chip *chip, unsigned offset)
{
	struct bcm2835_pinctrl *pc = gpiochip_get_data(chip);

	return bcm2835_gpio_get_bit(pc, GPLEV0, offset);
}
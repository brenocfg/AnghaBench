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
 int /*<<< orphan*/  GPCLR0 ; 
 int /*<<< orphan*/  GPSET0 ; 
 int /*<<< orphan*/  bcm2835_gpio_set_bit (struct bcm2835_pinctrl*,int /*<<< orphan*/ ,unsigned int) ; 
 struct bcm2835_pinctrl* gpiochip_get_data (struct gpio_chip*) ; 

__attribute__((used)) static void bcm2835_gpio_set(struct gpio_chip *chip, unsigned offset, int value)
{
	struct bcm2835_pinctrl *pc = gpiochip_get_data(chip);

	bcm2835_gpio_set_bit(pc, value ? GPSET0 : GPCLR0, offset);
}
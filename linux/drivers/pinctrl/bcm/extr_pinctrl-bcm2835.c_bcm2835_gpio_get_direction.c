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
typedef  enum bcm2835_fsel { ____Placeholder_bcm2835_fsel } bcm2835_fsel ;

/* Variables and functions */
 int BCM2835_FSEL_GPIO_IN ; 
 int BCM2835_FSEL_GPIO_OUT ; 
 int EINVAL ; 
 int bcm2835_pinctrl_fsel_get (struct bcm2835_pinctrl*,unsigned int) ; 
 struct bcm2835_pinctrl* gpiochip_get_data (struct gpio_chip*) ; 

__attribute__((used)) static int bcm2835_gpio_get_direction(struct gpio_chip *chip, unsigned int offset)
{
	struct bcm2835_pinctrl *pc = gpiochip_get_data(chip);
	enum bcm2835_fsel fsel = bcm2835_pinctrl_fsel_get(pc, offset);

	/* Alternative function doesn't clearly provide a direction */
	if (fsel > BCM2835_FSEL_GPIO_OUT)
		return -EINVAL;

	return (fsel == BCM2835_FSEL_GPIO_IN);
}
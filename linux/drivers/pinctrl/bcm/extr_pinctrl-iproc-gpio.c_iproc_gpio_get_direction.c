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
struct iproc_gpio {scalar_t__ base; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 int /*<<< orphan*/  IPROC_GPIO_OUT_EN_OFFSET ; 
 unsigned int IPROC_GPIO_REG (unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int IPROC_GPIO_SHIFT (unsigned int) ; 
 struct iproc_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static int iproc_gpio_get_direction(struct gpio_chip *gc, unsigned int gpio)
{
	struct iproc_gpio *chip = gpiochip_get_data(gc);
	unsigned int offset = IPROC_GPIO_REG(gpio, IPROC_GPIO_OUT_EN_OFFSET);
	unsigned int shift = IPROC_GPIO_SHIFT(gpio);

	return !(readl(chip->base + offset) & BIT(shift));
}
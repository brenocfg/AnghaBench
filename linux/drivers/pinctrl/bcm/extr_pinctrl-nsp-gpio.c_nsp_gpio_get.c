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
struct nsp_gpio {scalar_t__ base; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 scalar_t__ NSP_GPIO_DATA_IN ; 
 struct nsp_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static int nsp_gpio_get(struct gpio_chip *gc, unsigned gpio)
{
	struct nsp_gpio *chip = gpiochip_get_data(gc);

	return !!(readl(chip->base + NSP_GPIO_DATA_IN) & BIT(gpio));
}
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
struct mb86s70_gpio_chip {scalar_t__ base; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int OFFSET (unsigned int) ; 
 scalar_t__ PDR (unsigned int) ; 
 struct mb86s70_gpio_chip* gpiochip_get_data (struct gpio_chip*) ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static int mb86s70_gpio_get(struct gpio_chip *gc, unsigned gpio)
{
	struct mb86s70_gpio_chip *gchip = gpiochip_get_data(gc);

	return !!(readl(gchip->base + PDR(gpio)) & OFFSET(gpio));
}
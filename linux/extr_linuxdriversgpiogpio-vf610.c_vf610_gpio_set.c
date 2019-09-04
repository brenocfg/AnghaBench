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
struct vf610_gpio_port {scalar_t__ gpio_base; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 unsigned long BIT (unsigned int) ; 
 scalar_t__ GPIO_PCOR ; 
 scalar_t__ GPIO_PSOR ; 
 struct vf610_gpio_port* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  vf610_gpio_writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static void vf610_gpio_set(struct gpio_chip *gc, unsigned int gpio, int val)
{
	struct vf610_gpio_port *port = gpiochip_get_data(gc);
	unsigned long mask = BIT(gpio);

	if (val)
		vf610_gpio_writel(mask, port->gpio_base + GPIO_PSOR);
	else
		vf610_gpio_writel(mask, port->gpio_base + GPIO_PCOR);
}
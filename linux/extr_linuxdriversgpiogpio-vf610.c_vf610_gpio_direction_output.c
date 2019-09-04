#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vf610_gpio_port {scalar_t__ gpio_base; TYPE_1__* sdata; } ;
struct gpio_chip {unsigned int base; } ;
struct TYPE_2__ {scalar_t__ have_paddr; } ;

/* Variables and functions */
 unsigned long BIT (unsigned int) ; 
 scalar_t__ GPIO_PDDR ; 
 struct vf610_gpio_port* gpiochip_get_data (struct gpio_chip*) ; 
 int pinctrl_gpio_direction_output (unsigned int) ; 
 int /*<<< orphan*/  vf610_gpio_set (struct gpio_chip*,unsigned int,int) ; 
 int /*<<< orphan*/  vf610_gpio_writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static int vf610_gpio_direction_output(struct gpio_chip *chip, unsigned gpio,
				       int value)
{
	struct vf610_gpio_port *port = gpiochip_get_data(chip);
	unsigned long mask = BIT(gpio);

	if (port->sdata && port->sdata->have_paddr)
		vf610_gpio_writel(mask, port->gpio_base + GPIO_PDDR);

	vf610_gpio_set(chip, gpio, value);

	return pinctrl_gpio_direction_output(chip->base + gpio);
}
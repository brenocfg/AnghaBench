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
struct mxc_gpio_port {int /*<<< orphan*/  domain; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 struct mxc_gpio_port* gpiochip_get_data (struct gpio_chip*) ; 
 int irq_find_mapping (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int mxc_gpio_to_irq(struct gpio_chip *gc, unsigned offset)
{
	struct mxc_gpio_port *port = gpiochip_get_data(gc);

	return irq_find_mapping(port->domain, offset);
}
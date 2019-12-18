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
struct gpio_chip {unsigned int ngpio; } ;
struct dwapb_gpio_port {struct gpio_chip gc; } ;
struct dwapb_gpio {int /*<<< orphan*/ * domain; struct dwapb_gpio_port* ports; } ;
typedef  unsigned int irq_hw_number_t ;

/* Variables and functions */
 int /*<<< orphan*/  irq_dispose_mapping (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_domain_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_find_mapping (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void dwapb_irq_teardown(struct dwapb_gpio *gpio)
{
	struct dwapb_gpio_port *port = &gpio->ports[0];
	struct gpio_chip *gc = &port->gc;
	unsigned int ngpio = gc->ngpio;
	irq_hw_number_t hwirq;

	if (!gpio->domain)
		return;

	for (hwirq = 0 ; hwirq < ngpio ; hwirq++)
		irq_dispose_mapping(irq_find_mapping(gpio->domain, hwirq));

	irq_domain_remove(gpio->domain);
	gpio->domain = NULL;
}
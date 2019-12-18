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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct vf610_gpio_port {int /*<<< orphan*/ * irqc; } ;
struct irq_data {size_t hwirq; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IRQ_TYPE_EDGE_BOTH 132 
#define  IRQ_TYPE_EDGE_FALLING 131 
#define  IRQ_TYPE_EDGE_RISING 130 
#define  IRQ_TYPE_LEVEL_HIGH 129 
#define  IRQ_TYPE_LEVEL_LOW 128 
 int IRQ_TYPE_LEVEL_MASK ; 
 int /*<<< orphan*/  PORT_INT_EITHER_EDGE ; 
 int /*<<< orphan*/  PORT_INT_FALLING_EDGE ; 
 int /*<<< orphan*/  PORT_INT_LOGIC_ONE ; 
 int /*<<< orphan*/  PORT_INT_LOGIC_ZERO ; 
 int /*<<< orphan*/  PORT_INT_RISING_EDGE ; 
 struct vf610_gpio_port* gpiochip_get_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_edge_irq ; 
 int /*<<< orphan*/  handle_level_irq ; 
 int /*<<< orphan*/  irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  irq_set_handler_locked (struct irq_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vf610_gpio_irq_set_type(struct irq_data *d, u32 type)
{
	struct vf610_gpio_port *port =
		gpiochip_get_data(irq_data_get_irq_chip_data(d));
	u8 irqc;

	switch (type) {
	case IRQ_TYPE_EDGE_RISING:
		irqc = PORT_INT_RISING_EDGE;
		break;
	case IRQ_TYPE_EDGE_FALLING:
		irqc = PORT_INT_FALLING_EDGE;
		break;
	case IRQ_TYPE_EDGE_BOTH:
		irqc = PORT_INT_EITHER_EDGE;
		break;
	case IRQ_TYPE_LEVEL_LOW:
		irqc = PORT_INT_LOGIC_ZERO;
		break;
	case IRQ_TYPE_LEVEL_HIGH:
		irqc = PORT_INT_LOGIC_ONE;
		break;
	default:
		return -EINVAL;
	}

	port->irqc[d->hwirq] = irqc;

	if (type & IRQ_TYPE_LEVEL_MASK)
		irq_set_handler_locked(d, handle_level_irq);
	else
		irq_set_handler_locked(d, handle_edge_irq);

	return 0;
}
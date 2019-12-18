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
struct irq_data {int irq; } ;
struct gpio_chip {int /*<<< orphan*/  (* get ) (struct gpio_chip*,int) ;int /*<<< orphan*/  (* direction_input ) (struct gpio_chip*,int) ;} ;
struct ep93xx_gpio {int dummy; } ;
typedef  int /*<<< orphan*/  irq_flow_handler_t ;

/* Variables and functions */
 int BIT (int) ; 
 int EINVAL ; 
#define  IRQ_TYPE_EDGE_BOTH 132 
#define  IRQ_TYPE_EDGE_FALLING 131 
#define  IRQ_TYPE_EDGE_RISING 130 
#define  IRQ_TYPE_LEVEL_HIGH 129 
#define  IRQ_TYPE_LEVEL_LOW 128 
 int ep93xx_gpio_port (struct gpio_chip*) ; 
 int /*<<< orphan*/  ep93xx_gpio_update_int_params (struct ep93xx_gpio*,int) ; 
 int* gpio_int_enabled ; 
 int* gpio_int_type1 ; 
 int* gpio_int_type2 ; 
 struct ep93xx_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  handle_edge_irq ; 
 int /*<<< orphan*/  handle_level_irq ; 
 struct gpio_chip* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  irq_set_handler_locked (struct irq_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct gpio_chip*,int) ; 
 int /*<<< orphan*/  stub2 (struct gpio_chip*,int) ; 

__attribute__((used)) static int ep93xx_gpio_irq_type(struct irq_data *d, unsigned int type)
{
	struct gpio_chip *gc = irq_data_get_irq_chip_data(d);
	struct ep93xx_gpio *epg = gpiochip_get_data(gc);
	int port = ep93xx_gpio_port(gc);
	int offset = d->irq & 7;
	int port_mask = BIT(offset);
	irq_flow_handler_t handler;

	gc->direction_input(gc, offset);

	switch (type) {
	case IRQ_TYPE_EDGE_RISING:
		gpio_int_type1[port] |= port_mask;
		gpio_int_type2[port] |= port_mask;
		handler = handle_edge_irq;
		break;
	case IRQ_TYPE_EDGE_FALLING:
		gpio_int_type1[port] |= port_mask;
		gpio_int_type2[port] &= ~port_mask;
		handler = handle_edge_irq;
		break;
	case IRQ_TYPE_LEVEL_HIGH:
		gpio_int_type1[port] &= ~port_mask;
		gpio_int_type2[port] |= port_mask;
		handler = handle_level_irq;
		break;
	case IRQ_TYPE_LEVEL_LOW:
		gpio_int_type1[port] &= ~port_mask;
		gpio_int_type2[port] &= ~port_mask;
		handler = handle_level_irq;
		break;
	case IRQ_TYPE_EDGE_BOTH:
		gpio_int_type1[port] |= port_mask;
		/* set initial polarity based on current input level */
		if (gc->get(gc, offset))
			gpio_int_type2[port] &= ~port_mask; /* falling */
		else
			gpio_int_type2[port] |= port_mask; /* rising */
		handler = handle_edge_irq;
		break;
	default:
		return -EINVAL;
	}

	irq_set_handler_locked(d, handler);

	gpio_int_enabled[port] |= port_mask;

	ep93xx_gpio_update_int_params(epg, port);

	return 0;
}
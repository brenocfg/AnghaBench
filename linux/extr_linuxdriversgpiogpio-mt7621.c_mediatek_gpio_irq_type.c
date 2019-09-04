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
typedef  int u32 ;
struct mtk_gc {int rising; int falling; int hlevel; int llevel; } ;
struct irq_data {int hwirq; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
#define  IRQ_TYPE_EDGE_BOTH 132 
#define  IRQ_TYPE_EDGE_FALLING 131 
#define  IRQ_TYPE_EDGE_RISING 130 
#define  IRQ_TYPE_LEVEL_HIGH 129 
#define  IRQ_TYPE_LEVEL_LOW 128 
 unsigned int IRQ_TYPE_PROBE ; 
 unsigned int IRQ_TYPE_SENSE_MASK ; 
 struct gpio_chip* irq_data_get_irq_chip_data (struct irq_data*) ; 
 struct mtk_gc* to_mediatek_gpio (struct gpio_chip*) ; 

__attribute__((used)) static int
mediatek_gpio_irq_type(struct irq_data *d, unsigned int type)
{
	struct gpio_chip *gc = irq_data_get_irq_chip_data(d);
	struct mtk_gc *rg = to_mediatek_gpio(gc);
	int pin = d->hwirq;
	u32 mask = BIT(pin);

	if (type == IRQ_TYPE_PROBE) {
		if ((rg->rising | rg->falling |
		     rg->hlevel | rg->llevel) & mask)
			return 0;

		type = IRQ_TYPE_EDGE_RISING | IRQ_TYPE_EDGE_FALLING;
	}

	rg->rising &= ~mask;
	rg->falling &= ~mask;
	rg->hlevel &= ~mask;
	rg->llevel &= ~mask;

	switch (type & IRQ_TYPE_SENSE_MASK) {
	case IRQ_TYPE_EDGE_BOTH:
		rg->rising |= mask;
		rg->falling |= mask;
		break;
	case IRQ_TYPE_EDGE_RISING:
		rg->rising |= mask;
		break;
	case IRQ_TYPE_EDGE_FALLING:
		rg->falling |= mask;
		break;
	case IRQ_TYPE_LEVEL_HIGH:
		rg->hlevel |= mask;
		break;
	case IRQ_TYPE_LEVEL_LOW:
		rg->llevel |= mask;
		break;
	}

	return 0;
}
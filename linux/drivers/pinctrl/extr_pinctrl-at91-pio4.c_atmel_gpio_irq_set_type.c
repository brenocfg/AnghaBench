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
struct irq_data {size_t hwirq; } ;
struct atmel_pioctrl {struct atmel_pin** pins; } ;
struct atmel_pin {int /*<<< orphan*/  bank; int /*<<< orphan*/  line; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATMEL_PIO_CFGR ; 
 unsigned int ATMEL_PIO_CFGR_EVTSEL_BOTH ; 
 unsigned int ATMEL_PIO_CFGR_EVTSEL_FALLING ; 
 unsigned int ATMEL_PIO_CFGR_EVTSEL_HIGH ; 
 unsigned int ATMEL_PIO_CFGR_EVTSEL_LOW ; 
 unsigned int ATMEL_PIO_CFGR_EVTSEL_MASK ; 
 unsigned int ATMEL_PIO_CFGR_EVTSEL_RISING ; 
 int /*<<< orphan*/  ATMEL_PIO_MSKR ; 
 unsigned int BIT (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
#define  IRQ_TYPE_EDGE_BOTH 133 
#define  IRQ_TYPE_EDGE_FALLING 132 
#define  IRQ_TYPE_EDGE_RISING 131 
#define  IRQ_TYPE_LEVEL_HIGH 130 
#define  IRQ_TYPE_LEVEL_LOW 129 
#define  IRQ_TYPE_NONE 128 
 unsigned int atmel_gpio_read (struct atmel_pioctrl*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atmel_gpio_write (struct atmel_pioctrl*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  handle_edge_irq ; 
 int /*<<< orphan*/  handle_level_irq ; 
 struct atmel_pioctrl* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  irq_set_handler_locked (struct irq_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atmel_gpio_irq_set_type(struct irq_data *d, unsigned type)
{
	struct atmel_pioctrl *atmel_pioctrl = irq_data_get_irq_chip_data(d);
	struct atmel_pin *pin = atmel_pioctrl->pins[d->hwirq];
	unsigned reg;

	atmel_gpio_write(atmel_pioctrl, pin->bank, ATMEL_PIO_MSKR,
			 BIT(pin->line));
	reg = atmel_gpio_read(atmel_pioctrl, pin->bank, ATMEL_PIO_CFGR);
	reg &= (~ATMEL_PIO_CFGR_EVTSEL_MASK);

	switch (type) {
	case IRQ_TYPE_EDGE_RISING:
		irq_set_handler_locked(d, handle_edge_irq);
		reg |= ATMEL_PIO_CFGR_EVTSEL_RISING;
		break;
	case IRQ_TYPE_EDGE_FALLING:
		irq_set_handler_locked(d, handle_edge_irq);
		reg |= ATMEL_PIO_CFGR_EVTSEL_FALLING;
		break;
	case IRQ_TYPE_EDGE_BOTH:
		irq_set_handler_locked(d, handle_edge_irq);
		reg |= ATMEL_PIO_CFGR_EVTSEL_BOTH;
		break;
	case IRQ_TYPE_LEVEL_LOW:
		irq_set_handler_locked(d, handle_level_irq);
		reg |= ATMEL_PIO_CFGR_EVTSEL_LOW;
		break;
	case IRQ_TYPE_LEVEL_HIGH:
		irq_set_handler_locked(d, handle_level_irq);
		reg |= ATMEL_PIO_CFGR_EVTSEL_HIGH;
		break;
	case IRQ_TYPE_NONE:
	default:
		return -EINVAL;
	}

	atmel_gpio_write(atmel_pioctrl, pin->bank, ATMEL_PIO_CFGR, reg);

	return 0;
}
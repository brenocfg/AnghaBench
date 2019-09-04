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
typedef  int /*<<< orphan*/  u32 ;
struct lpc32xx_irq_chip {int dummy; } ;
struct irq_data {int /*<<< orphan*/  hwirq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
#define  IRQ_TYPE_EDGE_FALLING 131 
#define  IRQ_TYPE_EDGE_RISING 130 
#define  IRQ_TYPE_LEVEL_HIGH 129 
#define  IRQ_TYPE_LEVEL_LOW 128 
 int /*<<< orphan*/  LPC32XX_INTC_POL ; 
 int /*<<< orphan*/  LPC32XX_INTC_TYPE ; 
 int /*<<< orphan*/  handle_edge_irq ; 
 int /*<<< orphan*/  handle_level_irq ; 
 struct lpc32xx_irq_chip* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  irq_set_handler_locked (struct irq_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irqd_set_trigger_type (struct irq_data*,unsigned int) ; 
 int /*<<< orphan*/  lpc32xx_ic_read (struct lpc32xx_irq_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpc32xx_ic_write (struct lpc32xx_irq_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,unsigned int) ; 

__attribute__((used)) static int lpc32xx_irq_set_type(struct irq_data *d, unsigned int type)
{
	struct lpc32xx_irq_chip *ic = irq_data_get_irq_chip_data(d);
	u32 val, mask = BIT(d->hwirq);
	bool high, edge;

	switch (type) {
	case IRQ_TYPE_EDGE_RISING:
		edge = true;
		high = true;
		break;
	case IRQ_TYPE_EDGE_FALLING:
		edge = true;
		high = false;
		break;
	case IRQ_TYPE_LEVEL_HIGH:
		edge = false;
		high = true;
		break;
	case IRQ_TYPE_LEVEL_LOW:
		edge = false;
		high = false;
		break;
	default:
		pr_info("unsupported irq type %d\n", type);
		return -EINVAL;
	}

	irqd_set_trigger_type(d, type);

	val = lpc32xx_ic_read(ic, LPC32XX_INTC_POL);
	if (high)
		val |= mask;
	else
		val &= ~mask;
	lpc32xx_ic_write(ic, LPC32XX_INTC_POL, val);

	val = lpc32xx_ic_read(ic, LPC32XX_INTC_TYPE);
	if (edge) {
		val |= mask;
		irq_set_handler_locked(d, handle_edge_irq);
	} else {
		val &= ~mask;
		irq_set_handler_locked(d, handle_level_irq);
	}
	lpc32xx_ic_write(ic, LPC32XX_INTC_TYPE, val);

	return 0;
}
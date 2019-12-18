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
struct irq_data {int /*<<< orphan*/  mask; } ;
struct irq_chip_generic {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IRQ_TYPE_EDGE_FALLING 131 
#define  IRQ_TYPE_EDGE_RISING 130 
#define  IRQ_TYPE_LEVEL_HIGH 129 
#define  IRQ_TYPE_LEVEL_LOW 128 
 int /*<<< orphan*/  LS_REG_INTC_EDGE ; 
 int /*<<< orphan*/  LS_REG_INTC_POL ; 
 struct irq_chip_generic* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int irq_setup_alt_chip (struct irq_data*,unsigned int) ; 
 int /*<<< orphan*/  irqd_set_trigger_type (struct irq_data*,unsigned int) ; 
 int /*<<< orphan*/  ls_intc_set_bit (struct irq_chip_generic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ls_intc_set_type(struct irq_data *data, unsigned int type)
{
	struct irq_chip_generic *gc = irq_data_get_irq_chip_data(data);
	u32 mask = data->mask;

	switch (type) {
	case IRQ_TYPE_LEVEL_HIGH:
		ls_intc_set_bit(gc, LS_REG_INTC_EDGE, mask, false);
		ls_intc_set_bit(gc, LS_REG_INTC_POL, mask, true);
		break;
	case IRQ_TYPE_LEVEL_LOW:
		ls_intc_set_bit(gc, LS_REG_INTC_EDGE, mask, false);
		ls_intc_set_bit(gc, LS_REG_INTC_POL, mask, false);
		break;
	case IRQ_TYPE_EDGE_RISING:
		ls_intc_set_bit(gc, LS_REG_INTC_EDGE, mask, true);
		ls_intc_set_bit(gc, LS_REG_INTC_POL, mask, true);
		break;
	case IRQ_TYPE_EDGE_FALLING:
		ls_intc_set_bit(gc, LS_REG_INTC_EDGE, mask, true);
		ls_intc_set_bit(gc, LS_REG_INTC_POL, mask, false);
		break;
	default:
		return -EINVAL;
	}

	irqd_set_trigger_type(data, type);
	return irq_setup_alt_chip(data, type);
}
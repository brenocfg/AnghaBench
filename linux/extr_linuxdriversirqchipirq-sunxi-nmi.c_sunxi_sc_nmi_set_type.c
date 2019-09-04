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
typedef  unsigned int u32 ;
struct irq_data {int /*<<< orphan*/  irq; } ;
struct TYPE_2__ {unsigned int type; } ;
struct irq_chip_type {unsigned int type; TYPE_1__ regs; } ;
struct irq_chip_generic {unsigned int num_ct; struct irq_chip_type* chip_types; } ;

/* Variables and functions */
 int EBADR ; 
 unsigned int IRQF_TRIGGER_MASK ; 
 int IRQ_SET_MASK_OK ; 
#define  IRQ_TYPE_EDGE_FALLING 132 
#define  IRQ_TYPE_EDGE_RISING 131 
#define  IRQ_TYPE_LEVEL_HIGH 130 
#define  IRQ_TYPE_LEVEL_LOW 129 
#define  IRQ_TYPE_NONE 128 
 unsigned int SUNXI_NMI_SRC_TYPE_MASK ; 
 unsigned int SUNXI_SRC_TYPE_EDGE_FALLING ; 
 unsigned int SUNXI_SRC_TYPE_EDGE_RISING ; 
 unsigned int SUNXI_SRC_TYPE_LEVEL_HIGH ; 
 unsigned int SUNXI_SRC_TYPE_LEVEL_LOW ; 
 struct irq_chip_generic* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  irq_gc_lock (struct irq_chip_generic*) ; 
 int /*<<< orphan*/  irq_gc_unlock (struct irq_chip_generic*) ; 
 int /*<<< orphan*/  irq_setup_alt_chip (struct irq_data*,unsigned int) ; 
 int /*<<< orphan*/  irqd_set_trigger_type (struct irq_data*,unsigned int) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 unsigned int sunxi_sc_nmi_read (struct irq_chip_generic*,unsigned int) ; 
 int /*<<< orphan*/  sunxi_sc_nmi_write (struct irq_chip_generic*,unsigned int,unsigned int) ; 

__attribute__((used)) static int sunxi_sc_nmi_set_type(struct irq_data *data, unsigned int flow_type)
{
	struct irq_chip_generic *gc = irq_data_get_irq_chip_data(data);
	struct irq_chip_type *ct = gc->chip_types;
	u32 src_type_reg;
	u32 ctrl_off = ct->regs.type;
	unsigned int src_type;
	unsigned int i;

	irq_gc_lock(gc);

	switch (flow_type & IRQF_TRIGGER_MASK) {
	case IRQ_TYPE_EDGE_FALLING:
		src_type = SUNXI_SRC_TYPE_EDGE_FALLING;
		break;
	case IRQ_TYPE_EDGE_RISING:
		src_type = SUNXI_SRC_TYPE_EDGE_RISING;
		break;
	case IRQ_TYPE_LEVEL_HIGH:
		src_type = SUNXI_SRC_TYPE_LEVEL_HIGH;
		break;
	case IRQ_TYPE_NONE:
	case IRQ_TYPE_LEVEL_LOW:
		src_type = SUNXI_SRC_TYPE_LEVEL_LOW;
		break;
	default:
		irq_gc_unlock(gc);
		pr_err("Cannot assign multiple trigger modes to IRQ %d.\n",
			data->irq);
		return -EBADR;
	}

	irqd_set_trigger_type(data, flow_type);
	irq_setup_alt_chip(data, flow_type);

	for (i = 0; i < gc->num_ct; i++, ct++)
		if (ct->type & flow_type)
			ctrl_off = ct->regs.type;

	src_type_reg = sunxi_sc_nmi_read(gc, ctrl_off);
	src_type_reg &= ~SUNXI_NMI_SRC_TYPE_MASK;
	src_type_reg |= src_type;
	sunxi_sc_nmi_write(gc, ctrl_off, src_type_reg);

	irq_gc_unlock(gc);

	return IRQ_SET_MASK_OK;
}
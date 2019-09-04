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
struct irq_domain {struct evic_chip_data* host_data; } ;
struct irq_data {int dummy; } ;
struct evic_chip_data {int* irq_types; } ;
typedef  size_t irq_hw_number_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_REG_MASK (size_t,int,int) ; 
 int IRQ_TYPE_SENSE_MASK ; 
 int PIC32_CLR (scalar_t__) ; 
 int /*<<< orphan*/  PIC32_INT_PRI (int,int /*<<< orphan*/ ) ; 
 scalar_t__ REG_IEC_OFFSET ; 
 scalar_t__ REG_IFS_OFFSET ; 
 int evic_base ; 
 struct irq_data* irq_domain_get_irq_data (struct irq_domain*,unsigned int) ; 
 int irq_map_generic_chip (struct irq_domain*,unsigned int,size_t) ; 
 int /*<<< orphan*/  irq_setup_alt_chip (struct irq_data*,int) ; 
 int /*<<< orphan*/  irqd_set_trigger_type (struct irq_data*,int) ; 
 int /*<<< orphan*/  pic32_set_irq_priority (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,int) ; 

__attribute__((used)) static int pic32_irq_domain_map(struct irq_domain *d, unsigned int virq,
				irq_hw_number_t hw)
{
	struct evic_chip_data *priv = d->host_data;
	struct irq_data *data;
	int ret;
	u32 iecclr, ifsclr;
	u32 reg, mask;

	ret = irq_map_generic_chip(d, virq, hw);
	if (ret)
		return ret;

	/*
	 * Piggyback on xlate function to move to an alternate chip as necessary
	 * at time of mapping instead of allowing the flow handler/chip to be
	 * changed later. This requires all interrupts to be configured through
	 * DT.
	 */
	if (priv->irq_types[hw] & IRQ_TYPE_SENSE_MASK) {
		data = irq_domain_get_irq_data(d, virq);
		irqd_set_trigger_type(data, priv->irq_types[hw]);
		irq_setup_alt_chip(data, priv->irq_types[hw]);
	}

	IRQ_REG_MASK(hw, reg, mask);

	iecclr = PIC32_CLR(REG_IEC_OFFSET + reg * 0x10);
	ifsclr = PIC32_CLR(REG_IFS_OFFSET + reg * 0x10);

	/* mask and clear flag */
	writel(mask, evic_base + iecclr);
	writel(mask, evic_base + ifsclr);

	/* default priority is required */
	pic32_set_irq_priority(hw, PIC32_INT_PRI(2, 0));

	return ret;
}
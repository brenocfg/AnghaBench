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
struct gsc_asic {unsigned int* global_irq; int /*<<< orphan*/  name; scalar_t__ hpa; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBPRINTK (char*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ OFFSET_IRR ; 
 int __ffs (unsigned long) ; 
 int /*<<< orphan*/  generic_handle_irq (unsigned int) ; 
 unsigned long gsc_readl (scalar_t__) ; 

irqreturn_t gsc_asic_intr(int gsc_asic_irq, void *dev)
{
	unsigned long irr;
	struct gsc_asic *gsc_asic = dev;

	irr = gsc_readl(gsc_asic->hpa + OFFSET_IRR);
	if (irr == 0)
		return IRQ_NONE;

	DEBPRINTK("%s intr, mask=0x%x\n", gsc_asic->name, irr);

	do {
		int local_irq = __ffs(irr);
		unsigned int irq = gsc_asic->global_irq[local_irq];
		generic_handle_irq(irq);
		irr &= ~(1 << local_irq);
	} while (irr);

	return IRQ_HANDLED;
}
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
typedef  int u32 ;
struct irq_data {unsigned int irq; } ;
struct TYPE_2__ {scalar_t__ ack; } ;

/* Variables and functions */
 unsigned int IRQ_TYPE_EDGE_FALLING ; 
 unsigned int MCFINT_VECBASE ; 
 unsigned int MCFINT_VECMAX ; 
 int /*<<< orphan*/  MCFSIM_PITR ; 
 TYPE_1__* intc_irqmap ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int intc_irq_set_type(struct irq_data *d, unsigned int type)
{
	unsigned int irq = d->irq;

	if ((irq >= MCFINT_VECBASE) && (irq <= MCFINT_VECMAX)) {
		irq -= MCFINT_VECBASE;
		if (intc_irqmap[irq].ack) {
			u32 v;
			v = readl(MCFSIM_PITR);
			if (type == IRQ_TYPE_EDGE_FALLING)
				v &= ~(0x1 << (32 - irq));
			else
				v |= (0x1 << (32 - irq));
			writel(v, MCFSIM_PITR);
		}
	}
	return 0;
}
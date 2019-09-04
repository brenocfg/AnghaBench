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
struct intc_irqpin_priv {int shared_irq_mask; int /*<<< orphan*/ * irq; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  INTC_IRQPIN_REG_SOURCE ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  intc_irqpin_irq_handler (int,int /*<<< orphan*/ *) ; 
 unsigned int intc_irqpin_read (struct intc_irqpin_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t intc_irqpin_shared_irq_handler(int irq, void *dev_id)
{
	struct intc_irqpin_priv *p = dev_id;
	unsigned int reg_source = intc_irqpin_read(p, INTC_IRQPIN_REG_SOURCE);
	irqreturn_t status = IRQ_NONE;
	int k;

	for (k = 0; k < 8; k++) {
		if (reg_source & BIT(7 - k)) {
			if (BIT(k) & p->shared_irq_mask)
				continue;

			status |= intc_irqpin_irq_handler(irq, &p->irq[k]);
		}
	}

	return status;
}
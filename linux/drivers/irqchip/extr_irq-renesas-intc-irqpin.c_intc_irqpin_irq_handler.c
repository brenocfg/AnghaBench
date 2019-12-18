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
struct intc_irqpin_priv {int dummy; } ;
struct intc_irqpin_irq {int /*<<< orphan*/  domain_irq; int /*<<< orphan*/  hw_irq; struct intc_irqpin_priv* p; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  INTC_IRQPIN_REG_SOURCE ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  generic_handle_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intc_irqpin_dbg (struct intc_irqpin_irq*,char*) ; 
 unsigned long intc_irqpin_hwirq_mask (struct intc_irqpin_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long intc_irqpin_read (struct intc_irqpin_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intc_irqpin_write (struct intc_irqpin_priv*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static irqreturn_t intc_irqpin_irq_handler(int irq, void *dev_id)
{
	struct intc_irqpin_irq *i = dev_id;
	struct intc_irqpin_priv *p = i->p;
	unsigned long bit;

	intc_irqpin_dbg(i, "demux1");
	bit = intc_irqpin_hwirq_mask(p, INTC_IRQPIN_REG_SOURCE, i->hw_irq);

	if (intc_irqpin_read(p, INTC_IRQPIN_REG_SOURCE) & bit) {
		intc_irqpin_write(p, INTC_IRQPIN_REG_SOURCE, ~bit);
		intc_irqpin_dbg(i, "demux2");
		generic_handle_irq(i->domain_irq);
		return IRQ_HANDLED;
	}
	return IRQ_NONE;
}
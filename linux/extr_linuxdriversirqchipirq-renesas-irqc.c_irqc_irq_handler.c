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
struct irqc_priv {int /*<<< orphan*/  irq_domain; scalar_t__ iomem; } ;
struct irqc_irq {int /*<<< orphan*/  hw_irq; struct irqc_priv* p; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 scalar_t__ DETECT_STATUS ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  generic_handle_irq (int /*<<< orphan*/ ) ; 
 int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int /*<<< orphan*/  irq_find_mapping (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irqc_dbg (struct irqc_irq*,char*) ; 

__attribute__((used)) static irqreturn_t irqc_irq_handler(int irq, void *dev_id)
{
	struct irqc_irq *i = dev_id;
	struct irqc_priv *p = i->p;
	u32 bit = BIT(i->hw_irq);

	irqc_dbg(i, "demux1");

	if (ioread32(p->iomem + DETECT_STATUS) & bit) {
		iowrite32(bit, p->iomem + DETECT_STATUS);
		irqc_dbg(i, "demux2");
		generic_handle_irq(irq_find_mapping(p->irq_domain, i->hw_irq));
		return IRQ_HANDLED;
	}
	return IRQ_NONE;
}
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
struct irq_desc {int /*<<< orphan*/  lock; int /*<<< orphan*/  irq_data; } ;
struct irq_chip {int /*<<< orphan*/  (* irq_unmask ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* irq_ack ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* irq_mask ) (int /*<<< orphan*/ *) ;} ;
struct TYPE_2__ {int /*<<< orphan*/  irqhost; scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ MEDIA5200_IRQ_ENABLE ; 
 int MEDIA5200_IRQ_SHIFT ; 
 scalar_t__ MEDIA5200_IRQ_STATUS ; 
 int ffs (int) ; 
 int /*<<< orphan*/  generic_handle_irq (int) ; 
 int in_be32 (scalar_t__) ; 
 struct irq_chip* irq_desc_get_chip (struct irq_desc*) ; 
 int irq_linear_revmap (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  irqd_irq_disabled (int /*<<< orphan*/ *) ; 
 TYPE_1__ media5200_irq ; 
 int /*<<< orphan*/  raw_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void media5200_irq_cascade(struct irq_desc *desc)
{
	struct irq_chip *chip = irq_desc_get_chip(desc);
	int sub_virq, val;
	u32 status, enable;

	/* Mask off the cascaded IRQ */
	raw_spin_lock(&desc->lock);
	chip->irq_mask(&desc->irq_data);
	raw_spin_unlock(&desc->lock);

	/* Ask the FPGA for IRQ status.  If 'val' is 0, then no irqs
	 * are pending.  'ffs()' is 1 based */
	status = in_be32(media5200_irq.regs + MEDIA5200_IRQ_ENABLE);
	enable = in_be32(media5200_irq.regs + MEDIA5200_IRQ_STATUS);
	val = ffs((status & enable) >> MEDIA5200_IRQ_SHIFT);
	if (val) {
		sub_virq = irq_linear_revmap(media5200_irq.irqhost, val - 1);
		/* pr_debug("%s: virq=%i s=%.8x e=%.8x hwirq=%i subvirq=%i\n",
		 *          __func__, virq, status, enable, val - 1, sub_virq);
		 */
		generic_handle_irq(sub_virq);
	}

	/* Processing done; can reenable the cascade now */
	raw_spin_lock(&desc->lock);
	chip->irq_ack(&desc->irq_data);
	if (!irqd_irq_disabled(&desc->irq_data))
		chip->irq_unmask(&desc->irq_data);
	raw_spin_unlock(&desc->lock);
}
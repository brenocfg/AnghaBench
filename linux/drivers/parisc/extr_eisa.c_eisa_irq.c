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
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  EISA_DBG (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  eisa_in8 (int) ; 
 int /*<<< orphan*/  eisa_irq_lock ; 
 int /*<<< orphan*/  eisa_out8 (int,int) ; 
 int /*<<< orphan*/  generic_handle_irq (int) ; 
 int gsc_readb (int) ; 
 int master_mask ; 
 int slave_mask ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static irqreturn_t eisa_irq(int wax_irq, void *intr_dev)
{
	int irq = gsc_readb(0xfc01f000); /* EISA supports 16 irqs */
	unsigned long flags;

	spin_lock_irqsave(&eisa_irq_lock, flags);
	/* read IRR command */
	eisa_out8(0x0a, 0x20);
	eisa_out8(0x0a, 0xa0);

	EISA_DBG("irq IAR %02x 8259-1 irr %02x 8259-2 irr %02x\n",
		   irq, eisa_in8(0x20), eisa_in8(0xa0));

	/* read ISR command */
	eisa_out8(0x0a, 0x20);
	eisa_out8(0x0a, 0xa0);
	EISA_DBG("irq 8259-1 isr %02x imr %02x 8259-2 isr %02x imr %02x\n",
		 eisa_in8(0x20), eisa_in8(0x21), eisa_in8(0xa0), eisa_in8(0xa1));

	irq &= 0xf;

	/* mask irq and write eoi */
	if (irq & 8) {
		slave_mask |= (1 << (irq&7));
		eisa_out8(slave_mask, 0xa1);
		eisa_out8(0x60 | (irq&7),0xa0);/* 'Specific EOI' to slave */
		eisa_out8(0x62, 0x20);	/* 'Specific EOI' to master-IRQ2 */

	} else {
		master_mask |= (1 << (irq&7));
		eisa_out8(master_mask, 0x21);
		eisa_out8(0x60|irq, 0x20);	/* 'Specific EOI' to master */
	}
	spin_unlock_irqrestore(&eisa_irq_lock, flags);

	generic_handle_irq(irq);

	spin_lock_irqsave(&eisa_irq_lock, flags);
	/* unmask */
        if (irq & 8) {
		slave_mask &= ~(1 << (irq&7));
		eisa_out8(slave_mask, 0xa1);
	} else {
		master_mask &= ~(1 << (irq&7));
		eisa_out8(master_mask, 0x21);
	}
	spin_unlock_irqrestore(&eisa_irq_lock, flags);
	return IRQ_HANDLED;
}
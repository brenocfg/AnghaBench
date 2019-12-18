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
struct irq_data {unsigned int irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  EISA_DBG (char*,unsigned int) ; 
 unsigned int eisa_in8 (int) ; 
 int /*<<< orphan*/  eisa_irq_lock ; 
 int /*<<< orphan*/  eisa_out8 (int,int) ; 
 int master_mask ; 
 int slave_mask ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void eisa_unmask_irq(struct irq_data *d)
{
	unsigned int irq = d->irq;
	unsigned long flags;
	EISA_DBG("enable irq %d\n", irq);

	spin_lock_irqsave(&eisa_irq_lock, flags);
        if (irq & 8) {
		slave_mask &= ~(1 << (irq&7));
		eisa_out8(slave_mask, 0xa1);
	} else {
		master_mask &= ~(1 << (irq&7));
		eisa_out8(master_mask, 0x21);
	}
	spin_unlock_irqrestore(&eisa_irq_lock, flags);
	EISA_DBG("pic0 mask %02x\n", eisa_in8(0x21));
	EISA_DBG("pic1 mask %02x\n", eisa_in8(0xa1));
}
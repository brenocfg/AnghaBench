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
struct irq_bucket {size_t pil; struct irq_bucket* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned int NR_IRQS ; 
 size_t SUN4D_MAX_IRQ ; 
 struct irq_bucket** irq_map ; 
 int /*<<< orphan*/  irq_map_lock ; 
 struct irq_bucket* irq_table ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void irq_unlink(unsigned int irq)
{
	struct irq_bucket *p, **pnext;
	unsigned long flags;

	BUG_ON(irq >= NR_IRQS);

	spin_lock_irqsave(&irq_map_lock, flags);

	p = &irq_table[irq];
	BUG_ON(p->pil >= SUN4D_MAX_IRQ);
	pnext = &irq_map[p->pil];
	while (*pnext != p)
		pnext = &(*pnext)->next;
	*pnext = p->next;

	spin_unlock_irqrestore(&irq_map_lock, flags);
}
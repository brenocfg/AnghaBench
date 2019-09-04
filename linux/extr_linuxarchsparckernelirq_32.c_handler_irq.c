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
struct pt_regs {int dummy; } ;
struct irq_bucket {int /*<<< orphan*/  irq; struct irq_bucket* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  generic_handle_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_enter () ; 
 int /*<<< orphan*/  irq_exit () ; 
 struct irq_bucket** irq_map ; 
 struct pt_regs* set_irq_regs (struct pt_regs*) ; 

void handler_irq(unsigned int pil, struct pt_regs *regs)
{
	struct pt_regs *old_regs;
	struct irq_bucket *p;

	BUG_ON(pil > 15);
	old_regs = set_irq_regs(regs);
	irq_enter();

	p = irq_map[pil];
	while (p) {
		struct irq_bucket *next = p->next;

		generic_handle_irq(p->irq);
		p = next;
	}
	irq_exit();
	set_irq_regs(old_regs);
}
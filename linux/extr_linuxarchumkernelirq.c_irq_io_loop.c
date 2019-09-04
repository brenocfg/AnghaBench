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
struct uml_pt_regs {int dummy; } ;
struct irq_fd {int active; int pending; int /*<<< orphan*/  purge; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_IRQ (int /*<<< orphan*/ ,struct uml_pt_regs*) ; 

__attribute__((used)) static void irq_io_loop(struct irq_fd *irq, struct uml_pt_regs *regs)
{
/*
 * irq->active guards against reentry
 * irq->pending accumulates pending requests
 * if pending is raised the irq_handler is re-run
 * until pending is cleared
 */
	if (irq->active) {
		irq->active = false;
		do {
			irq->pending = false;
			do_IRQ(irq->irq, regs);
		} while (irq->pending && (!irq->purge));
		if (!irq->purge)
			irq->active = true;
	} else {
		irq->pending = true;
	}
}
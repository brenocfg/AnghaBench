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
struct qe_ic {int /*<<< orphan*/  irqhost; int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 unsigned int NO_IRQ ; 
 int /*<<< orphan*/  QEIC_CIVEC ; 
 unsigned int irq_linear_revmap (int /*<<< orphan*/ ,int) ; 
 int qe_ic_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

unsigned int qe_ic_get_low_irq(struct qe_ic *qe_ic)
{
	int irq;

	BUG_ON(qe_ic == NULL);

	/* get the interrupt source vector. */
	irq = qe_ic_read(qe_ic->regs, QEIC_CIVEC) >> 26;

	if (irq == 0)
		return NO_IRQ;

	return irq_linear_revmap(qe_ic->irqhost, irq);
}
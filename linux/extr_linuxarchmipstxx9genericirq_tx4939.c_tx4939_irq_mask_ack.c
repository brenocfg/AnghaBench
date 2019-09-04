#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct irq_data {unsigned int irq; } ;
struct TYPE_4__ {int /*<<< orphan*/  r; } ;
struct TYPE_6__ {TYPE_1__ edc; } ;
struct TYPE_5__ {int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 unsigned int TXX9_IRQ_BASE ; 
 scalar_t__ TXx9_IRCR_EDGE (int /*<<< orphan*/ ) ; 
 unsigned int TXx9_IRSCR_EIClrE ; 
 int /*<<< orphan*/  __raw_writel (unsigned int,int /*<<< orphan*/ *) ; 
 TYPE_3__* tx4939_ircptr ; 
 int /*<<< orphan*/  tx4939_irq_mask (struct irq_data*) ; 
 TYPE_2__* tx4939irq ; 

__attribute__((used)) static void tx4939_irq_mask_ack(struct irq_data *d)
{
	unsigned int irq_nr = d->irq - TXX9_IRQ_BASE;

	tx4939_irq_mask(d);
	if (TXx9_IRCR_EDGE(tx4939irq[irq_nr].mode)) {
		irq_nr--;
		/* clear edge detection */
		__raw_writel((TXx9_IRSCR_EIClrE | (irq_nr & 0xf))
			     << (irq_nr & 0x10),
			     &tx4939_ircptr->edc.r);
	}
}
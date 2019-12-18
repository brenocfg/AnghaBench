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
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int crb; int /*<<< orphan*/  pprb; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int MAX_MFC ; 
 int /*<<< orphan*/  dummy ; 
 int /*<<< orphan*/  parport_generic_irq (int /*<<< orphan*/ *) ; 
 TYPE_1__* pia (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** this_port ; 

__attribute__((used)) static irqreturn_t mfc3_interrupt(int irq, void *dev_id)
{
	int i;

	for( i = 0; i < MAX_MFC; i++)
		if (this_port[i] != NULL)
			if (pia(this_port[i])->crb & 128) { /* Board caused interrupt */
				dummy = pia(this_port[i])->pprb; /* clear irq bit */
				parport_generic_irq(this_port[i]);
			}
	return IRQ_HANDLED;
}
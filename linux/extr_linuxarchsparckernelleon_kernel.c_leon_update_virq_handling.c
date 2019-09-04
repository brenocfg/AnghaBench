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
typedef  int /*<<< orphan*/  irq_flow_handler_t ;

/* Variables and functions */
 unsigned long LEON_DO_ACK_HW ; 
 scalar_t__ irq_get_chip_data (unsigned int) ; 
 int /*<<< orphan*/  irq_set_chip_and_handler_name (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  irq_set_chip_data (unsigned int,void*) ; 
 int /*<<< orphan*/  leon_irq ; 

void leon_update_virq_handling(unsigned int virq,
			      irq_flow_handler_t flow_handler,
			      const char *name, int do_ack)
{
	unsigned long mask = (unsigned long)irq_get_chip_data(virq);

	mask &= ~LEON_DO_ACK_HW;
	if (do_ack)
		mask |= LEON_DO_ACK_HW;

	irq_set_chip_and_handler_name(virq, &leon_irq,
				      flow_handler, name);
	irq_set_chip_data(virq, (void *)mask);
}
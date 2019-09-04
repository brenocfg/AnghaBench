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
struct irq_desc {scalar_t__ handle_irq; } ;
typedef  int /*<<< orphan*/  irq_flow_handler_t ;

/* Variables and functions */
 unsigned long LEON_DO_ACK_HW ; 
 scalar_t__ handle_bad_irq ; 
 unsigned int irq_alloc (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  irq_set_chip_and_handler_name (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  irq_set_chip_data (unsigned int,void*) ; 
 struct irq_desc* irq_to_desc (unsigned int) ; 
 unsigned long leon_get_irqmask (unsigned int) ; 
 int /*<<< orphan*/  leon_irq ; 

unsigned int leon_build_device_irq(unsigned int real_irq,
				    irq_flow_handler_t flow_handler,
				    const char *name, int do_ack)
{
	unsigned int irq;
	unsigned long mask;
	struct irq_desc *desc;

	irq = 0;
	mask = leon_get_irqmask(real_irq);
	if (mask == 0)
		goto out;

	irq = irq_alloc(real_irq, real_irq);
	if (irq == 0)
		goto out;

	if (do_ack)
		mask |= LEON_DO_ACK_HW;

	desc = irq_to_desc(irq);
	if (!desc || !desc->handle_irq || desc->handle_irq == handle_bad_irq) {
		irq_set_chip_and_handler_name(irq, &leon_irq,
					      flow_handler, name);
		irq_set_chip_data(irq, (void *)mask);
	}

out:
	return irq;
}
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
struct irq_data {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int IRQF_TRIGGER_HIGH ; 
 unsigned int IRQF_TRIGGER_LOW ; 

__attribute__((used)) static int rda_intc_set_type(struct irq_data *data, unsigned int flow_type)
{
	/* Hardware supports only level triggered interrupts */
	if ((flow_type & (IRQF_TRIGGER_HIGH | IRQF_TRIGGER_LOW)) == flow_type)
		return 0;

	return -EINVAL;
}
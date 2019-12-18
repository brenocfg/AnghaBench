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
struct irq_desc {int dummy; } ;
struct irq_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpumask_of (unsigned int) ; 
 struct irq_data* irq_desc_get_irq_data (struct irq_desc*) ; 
 int set_affinity_irq (struct irq_data*,int /*<<< orphan*/ ,int) ; 

int xen_set_affinity_evtchn(struct irq_desc *desc, unsigned int tcpu)
{
	struct irq_data *d = irq_desc_get_irq_data(desc);

	return set_affinity_irq(d, cpumask_of(tcpu), false);
}
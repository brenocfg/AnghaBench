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
struct TYPE_2__ {int (* get_irq ) (unsigned int) ;} ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int NR_IRQS ; 
 int /*<<< orphan*/  cascade_irqaction ; 
 int /*<<< orphan*/  free_irq (unsigned int,int /*<<< orphan*/ *) ; 
 TYPE_1__* irq_cascade ; 
 int setup_irq (unsigned int,int /*<<< orphan*/ *) ; 

int cascade_irq(unsigned int irq, int (*get_irq)(unsigned int))
{
	int retval = 0;

	if (irq >= NR_IRQS)
		return -EINVAL;

	if (irq_cascade[irq].get_irq != NULL)
		free_irq(irq, NULL);

	irq_cascade[irq].get_irq = get_irq;

	if (get_irq != NULL) {
		retval = setup_irq(irq, &cascade_irqaction);
		if (retval < 0)
			irq_cascade[irq].get_irq = NULL;
	}

	return retval;
}
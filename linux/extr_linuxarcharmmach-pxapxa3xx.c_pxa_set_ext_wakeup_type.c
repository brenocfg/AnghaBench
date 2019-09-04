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
struct irq_data {int irq; } ;

/* Variables and functions */
 unsigned int IRQ_TYPE_EDGE_FALLING ; 
 unsigned int IRQ_TYPE_EDGE_RISING ; 
 int IRQ_WAKEUP0 ; 
 int PWER ; 

__attribute__((used)) static int pxa_set_ext_wakeup_type(struct irq_data *d, unsigned int flow_type)
{
	if (flow_type & IRQ_TYPE_EDGE_RISING)
		PWER |= 1 << (d->irq - IRQ_WAKEUP0);

	if (flow_type & IRQ_TYPE_EDGE_FALLING)
		PWER |= 1 << (d->irq - IRQ_WAKEUP0 + 2);

	return 0;
}
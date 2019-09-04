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
typedef  int u32 ;
struct irq_data {int hwirq; } ;

/* Variables and functions */
 int* gpc_wake_irqs ; 

__attribute__((used)) static int imx_gpc_irq_set_wake(struct irq_data *d, unsigned int on)
{
	unsigned int idx = d->hwirq / 32;
	u32 mask;

	mask = 1 << d->hwirq % 32;
	gpc_wake_irqs[idx] = on ? gpc_wake_irqs[idx] | mask :
				  gpc_wake_irqs[idx] & ~mask;

	/*
	 * Do *not* call into the parent, as the GIC doesn't have any
	 * wake-up facility...
	 */
	return 0;
}
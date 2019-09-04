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
struct TYPE_2__ {int /*<<< orphan*/  root_domain; } ;

/* Variables and functions */
 int /*<<< orphan*/  IVR ; 
 unsigned int irq_find_mapping (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned int,unsigned int) ; 
 TYPE_1__* xintc_irqc ; 
 unsigned int xintc_read (int /*<<< orphan*/ ) ; 

unsigned int xintc_get_irq(void)
{
	unsigned int hwirq, irq = -1;

	hwirq = xintc_read(IVR);
	if (hwirq != -1U)
		irq = irq_find_mapping(xintc_irqc->root_domain, hwirq);

	pr_debug("irq-xilinx: hwirq=%d, irq=%d\n", hwirq, irq);

	return irq;
}
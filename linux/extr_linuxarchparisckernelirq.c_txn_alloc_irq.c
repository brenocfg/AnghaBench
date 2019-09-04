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

/* Variables and functions */
 int CPU_IRQ_BASE ; 
 int CPU_IRQ_MAX ; 
 scalar_t__ cpu_claim_irq (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int txn_alloc_irq(unsigned int bits_wide)
{
	int irq;

	/* never return irq 0 cause that's the interval timer */
	for (irq = CPU_IRQ_BASE + 1; irq <= CPU_IRQ_MAX; irq++) {
		if (cpu_claim_irq(irq, NULL, NULL) < 0)
			continue;
		if ((irq - CPU_IRQ_BASE) >= (1 << bits_wide))
			continue;
		return irq;
	}

	/* unlikely, but be prepared */
	return -1;
}
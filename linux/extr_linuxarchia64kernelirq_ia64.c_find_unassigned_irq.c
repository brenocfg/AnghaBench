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
 int ENOSPC ; 
 int IA64_FIRST_DEVICE_VECTOR ; 
 scalar_t__ IRQ_UNUSED ; 
 int NR_IRQS ; 
 scalar_t__* irq_status ; 

__attribute__((used)) static inline int find_unassigned_irq(void)
{
	int irq;

	for (irq = IA64_FIRST_DEVICE_VECTOR; irq < NR_IRQS; irq++)
		if (irq_status[irq] == IRQ_UNUSED)
			return irq;
	return -ENOSPC;
}
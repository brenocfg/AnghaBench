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
 void ia64_teardown_msi_irq (unsigned int) ; 
 void platform_teardown_msi_irq (unsigned int) ; 

void arch_teardown_msi_irq(unsigned int irq)
{
	if (platform_teardown_msi_irq)
		return platform_teardown_msi_irq(irq);

	return ia64_teardown_msi_irq(irq);
}
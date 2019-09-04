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
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  sparc_idle () ; 
 int /*<<< orphan*/  stub1 () ; 

void arch_cpu_idle(void)
{
	if (sparc_idle)
		(*sparc_idle)();
	local_irq_enable();
}
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
 int /*<<< orphan*/  cpu_dcache_inval_all () ; 
 int /*<<< orphan*/  cpu_dcache_wb_all () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

void cpu_dcache_wbinval_all(void)
{
#ifndef CONFIG_CPU_DCACHE_WRITETHROUGH
	unsigned long flags;
	local_irq_save(flags);
#endif
	cpu_dcache_wb_all();
	cpu_dcache_inval_all();
#ifndef CONFIG_CPU_DCACHE_WRITETHROUGH
	local_irq_restore(flags);
#endif
}
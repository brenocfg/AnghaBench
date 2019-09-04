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
struct pt_regs {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int xmon_ipi(struct pt_regs *regs)
{
#ifdef CONFIG_SMP
	if (in_xmon && !cpumask_test_cpu(smp_processor_id(), &cpus_in_xmon))
		xmon_core(regs, 1);
#endif
	return 0;
}
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
struct vm_area_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  octeon_local_flush_icache () ; 

__attribute__((used)) static void octeon_flush_icache_all_cores(struct vm_area_struct *vma)
{
	extern void octeon_send_ipi_single(int cpu, unsigned int action);
#ifdef CONFIG_SMP
	int cpu;
	cpumask_t mask;
#endif

	mb();
	octeon_local_flush_icache();
#ifdef CONFIG_SMP
	preempt_disable();
	cpu = smp_processor_id();

	/*
	 * If we have a vma structure, we only need to worry about
	 * cores it has been used on
	 */
	if (vma)
		mask = *mm_cpumask(vma->vm_mm);
	else
		mask = *cpu_online_mask;
	cpumask_clear_cpu(cpu, &mask);
	for_each_cpu(cpu, &mask)
		octeon_send_ipi_single(cpu, SMP_ICACHE_FLUSH);

	preempt_enable();
#endif
}
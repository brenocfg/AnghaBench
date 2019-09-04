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
struct flush_tlb_info {unsigned long start; int /*<<< orphan*/  end; int /*<<< orphan*/ * mm; } ;
struct arch_tlbflush_unmap_batch {int /*<<< orphan*/  cpumask; } ;

/* Variables and functions */
 int /*<<< orphan*/  TLB_FLUSH_ALL ; 
 int /*<<< orphan*/  TLB_LOCAL_SHOOTDOWN ; 
 int /*<<< orphan*/  VM_WARN_ON (int /*<<< orphan*/ ) ; 
 scalar_t__ cpumask_any_but (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cpumask_clear (int /*<<< orphan*/ *) ; 
 scalar_t__ cpumask_test_cpu (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_tlb_func_local (struct flush_tlb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_tlb_others (int /*<<< orphan*/ *,struct flush_tlb_info*) ; 
 int get_cpu () ; 
 int /*<<< orphan*/  irqs_disabled () ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 scalar_t__ nr_cpu_ids ; 
 int /*<<< orphan*/  put_cpu () ; 

void arch_tlbbatch_flush(struct arch_tlbflush_unmap_batch *batch)
{
	struct flush_tlb_info info = {
		.mm = NULL,
		.start = 0UL,
		.end = TLB_FLUSH_ALL,
	};

	int cpu = get_cpu();

	if (cpumask_test_cpu(cpu, &batch->cpumask)) {
		VM_WARN_ON(irqs_disabled());
		local_irq_disable();
		flush_tlb_func_local(&info, TLB_LOCAL_SHOOTDOWN);
		local_irq_enable();
	}

	if (cpumask_any_but(&batch->cpumask, cpu) < nr_cpu_ids)
		flush_tlb_others(&batch->cpumask, &info);

	cpumask_clear(&batch->cpumask);

	put_cpu();
}
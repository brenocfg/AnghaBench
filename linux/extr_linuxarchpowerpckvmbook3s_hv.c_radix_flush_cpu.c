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
struct kvm_vcpu {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  cpu_in_guest; int /*<<< orphan*/  need_tlb_flush; } ;
struct kvm {TYPE_1__ arch; } ;

/* Variables and functions */
 int cpu_first_thread_sibling (int) ; 
 int /*<<< orphan*/  cpumask_set_cpu (int,int /*<<< orphan*/ *) ; 
 scalar_t__ cpumask_test_cpu (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_nothing ; 
 int /*<<< orphan*/  smp_call_function_single (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int threads_per_core ; 

__attribute__((used)) static void radix_flush_cpu(struct kvm *kvm, int cpu, struct kvm_vcpu *vcpu)
{
	int i;

	cpu = cpu_first_thread_sibling(cpu);
	cpumask_set_cpu(cpu, &kvm->arch.need_tlb_flush);
	/*
	 * Make sure setting of bit in need_tlb_flush precedes
	 * testing of cpu_in_guest bits.  The matching barrier on
	 * the other side is the first smp_mb() in kvmppc_run_core().
	 */
	smp_mb();
	for (i = 0; i < threads_per_core; ++i)
		if (cpumask_test_cpu(cpu + i, &kvm->arch.cpu_in_guest))
			smp_call_function_single(cpu + i, do_nothing, NULL, 1);
}
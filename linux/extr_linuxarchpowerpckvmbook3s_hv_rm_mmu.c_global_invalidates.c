#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int online_vcores; int /*<<< orphan*/  need_tlb_flush; } ;
struct kvm {TYPE_3__ arch; } ;
struct TYPE_6__ {TYPE_1__* kvm_vcore; scalar_t__ kvm_vcpu; } ;
struct TYPE_8__ {TYPE_2__ kvm_hstate; } ;
struct TYPE_5__ {int pcpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_FTR_ARCH_300 ; 
 int cpu_first_thread_sibling (int) ; 
 scalar_t__ cpu_has_feature (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_clear_cpu (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpumask_setall (int /*<<< orphan*/ *) ; 
 TYPE_4__* local_paca ; 
 int /*<<< orphan*/  smp_wmb () ; 

__attribute__((used)) static int global_invalidates(struct kvm *kvm)
{
	int global;
	int cpu;

	/*
	 * If there is only one vcore, and it's currently running,
	 * as indicated by local_paca->kvm_hstate.kvm_vcpu being set,
	 * we can use tlbiel as long as we mark all other physical
	 * cores as potentially having stale TLB entries for this lpid.
	 * Otherwise, don't use tlbiel.
	 */
	if (kvm->arch.online_vcores == 1 && local_paca->kvm_hstate.kvm_vcpu)
		global = 0;
	else
		global = 1;

	if (!global) {
		/* any other core might now have stale TLB entries... */
		smp_wmb();
		cpumask_setall(&kvm->arch.need_tlb_flush);
		cpu = local_paca->kvm_hstate.kvm_vcore->pcpu;
		/*
		 * On POWER9, threads are independent but the TLB is shared,
		 * so use the bit for the first thread to represent the core.
		 */
		if (cpu_has_feature(CPU_FTR_ARCH_300))
			cpu = cpu_first_thread_sibling(cpu);
		cpumask_clear_cpu(cpu, &kvm->arch.need_tlb_flush);
	}

	return global;
}
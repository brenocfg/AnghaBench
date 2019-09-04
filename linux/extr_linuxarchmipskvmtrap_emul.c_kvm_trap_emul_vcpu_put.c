#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct kvm_vcpu {int dummy; } ;
struct TYPE_6__ {int flags; TYPE_1__* mm; } ;
struct TYPE_5__ {int /*<<< orphan*/  pgd; } ;

/* Variables and functions */
 int PF_VCPU ; 
 int /*<<< orphan*/  TLBMISS_HANDLER_SETUP_PGD (int /*<<< orphan*/ ) ; 
 int asid_cache (int) ; 
 int asid_version_mask (int) ; 
 int /*<<< orphan*/  cpu_asid (int,TYPE_1__*) ; 
 int cpu_context (int,TYPE_1__*) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  ehb () ; 
 int /*<<< orphan*/  get_new_mmu_context (TYPE_1__*,int) ; 
 int /*<<< orphan*/  kvm_lose_fpu (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_mips_resume_mm (int) ; 
 int /*<<< orphan*/  write_c0_entryhi (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kvm_trap_emul_vcpu_put(struct kvm_vcpu *vcpu, int cpu)
{
	kvm_lose_fpu(vcpu);

	if (current->flags & PF_VCPU) {
		/* Restore normal Linux process memory map */
		if (((cpu_context(cpu, current->mm) ^ asid_cache(cpu)) &
		     asid_version_mask(cpu)))
			get_new_mmu_context(current->mm, cpu);
		write_c0_entryhi(cpu_asid(cpu, current->mm));
		TLBMISS_HANDLER_SETUP_PGD(current->mm->pgd);
		kvm_mips_resume_mm(cpu);
		ehb();
	}

	return 0;
}
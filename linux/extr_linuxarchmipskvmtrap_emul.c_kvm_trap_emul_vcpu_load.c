#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mm_struct {int /*<<< orphan*/  pgd; } ;
struct TYPE_3__ {struct mm_struct guest_user_mm; struct mm_struct guest_kernel_mm; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct TYPE_4__ {int flags; } ;

/* Variables and functions */
 scalar_t__ KVM_GUEST_KERNEL_MODE (struct kvm_vcpu*) ; 
 int PF_VCPU ; 
 int /*<<< orphan*/  TLBMISS_HANDLER_SETUP_PGD (int /*<<< orphan*/ ) ; 
 int asid_cache (int) ; 
 int asid_version_mask (int) ; 
 int /*<<< orphan*/  cpu_asid (int,struct mm_struct*) ; 
 int cpu_context (int,struct mm_struct*) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  ehb () ; 
 int /*<<< orphan*/  get_new_mmu_context (struct mm_struct*,int) ; 
 int /*<<< orphan*/  kvm_mips_suspend_mm (int) ; 
 int /*<<< orphan*/  write_c0_entryhi (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kvm_trap_emul_vcpu_load(struct kvm_vcpu *vcpu, int cpu)
{
	struct mm_struct *kern_mm = &vcpu->arch.guest_kernel_mm;
	struct mm_struct *user_mm = &vcpu->arch.guest_user_mm;
	struct mm_struct *mm;

	/*
	 * Were we in guest context? If so, restore the appropriate ASID based
	 * on the mode of the Guest (Kernel/User).
	 */
	if (current->flags & PF_VCPU) {
		mm = KVM_GUEST_KERNEL_MODE(vcpu) ? kern_mm : user_mm;
		if ((cpu_context(cpu, mm) ^ asid_cache(cpu)) &
		    asid_version_mask(cpu))
			get_new_mmu_context(mm, cpu);
		write_c0_entryhi(cpu_asid(cpu, mm));
		TLBMISS_HANDLER_SETUP_PGD(mm->pgd);
		kvm_mips_suspend_mm(cpu);
		ehb();
	}

	return 0;
}
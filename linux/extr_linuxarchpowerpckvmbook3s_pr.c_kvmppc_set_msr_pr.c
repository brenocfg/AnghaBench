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
typedef  int ulong ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int u64 ;
struct kvm_vcpu_arch {scalar_t__ magic_page_pa; scalar_t__ magic_page_ea; int /*<<< orphan*/  pending_exceptions; scalar_t__ papr_enabled; } ;
struct TYPE_3__ {int /*<<< orphan*/  halt_wakeup; } ;
struct kvm_vcpu {struct kvm_vcpu_arch arch; TYPE_1__ stat; } ;
struct TYPE_4__ {int msr_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  BOOK3S_INTERRUPT_FP_UNAVAIL ; 
 int /*<<< orphan*/  KVM_REQ_UNHALT ; 
 int MSR_DR ; 
 int MSR_FP ; 
 int MSR_HV ; 
 int MSR_IR ; 
 int MSR_ME ; 
 int MSR_POW ; 
 int MSR_PR ; 
 int MSR_SF ; 
 int /*<<< orphan*/  kvm_clear_request (int /*<<< orphan*/ ,struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_vcpu_block (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_fixup_split_real (struct kvm_vcpu*) ; 
 int kvmppc_get_msr (struct kvm_vcpu*) ; 
 scalar_t__ kvmppc_get_pc (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_handle_ext (struct kvm_vcpu*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ kvmppc_is_split_real (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_mmu_flush_segments (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_mmu_map_segment (struct kvm_vcpu*,scalar_t__) ; 
 int /*<<< orphan*/  kvmppc_mmu_pte_flush (struct kvm_vcpu*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kvmppc_recalc_shadow_msr (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_set_msr_fast (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  kvmppc_unfixup_split_real (struct kvm_vcpu*) ; 
 TYPE_2__* to_book3s (struct kvm_vcpu*) ; 

__attribute__((used)) static void kvmppc_set_msr_pr(struct kvm_vcpu *vcpu, u64 msr)
{
	ulong old_msr;

	/* For PAPR guest, make sure MSR reflects guest mode */
	if (vcpu->arch.papr_enabled)
		msr = (msr & ~MSR_HV) | MSR_ME;

#ifdef EXIT_DEBUG
	printk(KERN_INFO "KVM: Set MSR to 0x%llx\n", msr);
#endif

#ifdef CONFIG_PPC_TRANSACTIONAL_MEM
	/* We should never target guest MSR to TS=10 && PR=0,
	 * since we always fail transaction for guest privilege
	 * state.
	 */
	if (!(msr & MSR_PR) && MSR_TM_TRANSACTIONAL(msr))
		kvmppc_emulate_tabort(vcpu,
			TM_CAUSE_KVM_FAC_UNAV | TM_CAUSE_PERSISTENT);
#endif

	old_msr = kvmppc_get_msr(vcpu);
	msr &= to_book3s(vcpu)->msr_mask;
	kvmppc_set_msr_fast(vcpu, msr);
	kvmppc_recalc_shadow_msr(vcpu);

	if (msr & MSR_POW) {
		if (!vcpu->arch.pending_exceptions) {
			kvm_vcpu_block(vcpu);
			kvm_clear_request(KVM_REQ_UNHALT, vcpu);
			vcpu->stat.halt_wakeup++;

			/* Unset POW bit after we woke up */
			msr &= ~MSR_POW;
			kvmppc_set_msr_fast(vcpu, msr);
		}
	}

	if (kvmppc_is_split_real(vcpu))
		kvmppc_fixup_split_real(vcpu);
	else
		kvmppc_unfixup_split_real(vcpu);

	if ((kvmppc_get_msr(vcpu) & (MSR_PR|MSR_IR|MSR_DR)) !=
		   (old_msr & (MSR_PR|MSR_IR|MSR_DR))) {
		kvmppc_mmu_flush_segments(vcpu);
		kvmppc_mmu_map_segment(vcpu, kvmppc_get_pc(vcpu));

		/* Preload magic page segment when in kernel mode */
		if (!(msr & MSR_PR) && vcpu->arch.magic_page_pa) {
			struct kvm_vcpu_arch *a = &vcpu->arch;

			if (msr & MSR_DR)
				kvmppc_mmu_map_segment(vcpu, a->magic_page_ea);
			else
				kvmppc_mmu_map_segment(vcpu, a->magic_page_pa);
		}
	}

	/*
	 * When switching from 32 to 64-bit, we may have a stale 32-bit
	 * magic page around, we need to flush it. Typically 32-bit magic
	 * page will be instantiated when calling into RTAS. Note: We
	 * assume that such transition only happens while in kernel mode,
	 * ie, we never transition from user 32-bit to kernel 64-bit with
	 * a 32-bit magic page around.
	 */
	if (vcpu->arch.magic_page_pa &&
	    !(old_msr & MSR_PR) && !(old_msr & MSR_SF) && (msr & MSR_SF)) {
		/* going from RTAS to normal kernel code */
		kvmppc_mmu_pte_flush(vcpu, (uint32_t)vcpu->arch.magic_page_pa,
				     ~0xFFFUL);
	}

	/* Preload FPU if it's enabled */
	if (kvmppc_get_msr(vcpu) & MSR_FP)
		kvmppc_handle_ext(vcpu, BOOK3S_INTERRUPT_FP_UNAVAIL, MSR_FP);

#ifdef CONFIG_PPC_TRANSACTIONAL_MEM
	if (kvmppc_get_msr(vcpu) & MSR_TM)
		kvmppc_handle_lost_math_exts(vcpu);
#endif
}
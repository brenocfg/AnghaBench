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
struct mips_coproc {int dummy; } ;
struct TYPE_2__ {unsigned long pc; struct kvm_mips_tlb* guest_tlb; struct mips_coproc* cop0; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct kvm_mips_tlb {int /*<<< orphan*/  tlb_hi; int /*<<< orphan*/ * tlb_lo; int /*<<< orphan*/  tlb_mask; } ;
typedef  enum emulation_result { ____Placeholder_emulation_result } emulation_result ;

/* Variables and functions */
 int EMULATE_DONE ; 
 int KVM_MIPS_GUEST_TLB_SIZE ; 
 int /*<<< orphan*/  kvm_debug (char*,unsigned long,int) ; 
 int /*<<< orphan*/  kvm_mips_change_entryhi (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int kvm_read_c0_guest_index (struct mips_coproc*) ; 
 int /*<<< orphan*/  kvm_write_c0_guest_entrylo0 (struct mips_coproc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_write_c0_guest_entrylo1 (struct mips_coproc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_write_c0_guest_pagemask (struct mips_coproc*,int /*<<< orphan*/ ) ; 

enum emulation_result kvm_mips_emul_tlbr(struct kvm_vcpu *vcpu)
{
	struct mips_coproc *cop0 = vcpu->arch.cop0;
	struct kvm_mips_tlb *tlb;
	unsigned long pc = vcpu->arch.pc;
	int index;

	index = kvm_read_c0_guest_index(cop0);
	if (index < 0 || index >= KVM_MIPS_GUEST_TLB_SIZE) {
		/* UNDEFINED */
		kvm_debug("[%#lx] TLBR Index %#x out of range\n", pc, index);
		index &= KVM_MIPS_GUEST_TLB_SIZE - 1;
	}

	tlb = &vcpu->arch.guest_tlb[index];
	kvm_write_c0_guest_pagemask(cop0, tlb->tlb_mask);
	kvm_write_c0_guest_entrylo0(cop0, tlb->tlb_lo[0]);
	kvm_write_c0_guest_entrylo1(cop0, tlb->tlb_lo[1]);
	kvm_mips_change_entryhi(vcpu, tlb->tlb_hi);

	return EMULATE_DONE;
}
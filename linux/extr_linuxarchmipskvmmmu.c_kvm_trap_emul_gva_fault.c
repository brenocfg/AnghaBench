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
struct TYPE_2__ {struct kvm_mips_tlb* guest_tlb; struct mips_coproc* cop0; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct kvm_mips_tlb {int dummy; } ;
typedef  enum kvm_mips_fault_result { ____Placeholder_kvm_mips_fault_result } kvm_mips_fault_result ;

/* Variables and functions */
 unsigned long KVM_ENTRYHI_ASID ; 
 scalar_t__ KVM_GUEST_KSEG0 ; 
 scalar_t__ KVM_GUEST_KSEG23 ; 
 scalar_t__ KVM_GUEST_KSEGX (unsigned long) ; 
 int KVM_MIPS_GPA ; 
 int KVM_MIPS_GVA ; 
 int KVM_MIPS_MAPPED ; 
 int KVM_MIPS_TLB ; 
 int KVM_MIPS_TLBINV ; 
 int KVM_MIPS_TLBMOD ; 
 int /*<<< orphan*/  TLB_IS_DIRTY (struct kvm_mips_tlb,unsigned long) ; 
 int /*<<< orphan*/  TLB_IS_VALID (struct kvm_mips_tlb,unsigned long) ; 
 unsigned long VPN2_MASK ; 
 int kvm_mips_guest_tlb_lookup (struct kvm_vcpu*,unsigned long) ; 
 scalar_t__ kvm_mips_handle_kseg0_tlb_fault (unsigned long,struct kvm_vcpu*,int) ; 
 scalar_t__ kvm_mips_handle_mapped_seg_tlb_fault (struct kvm_vcpu*,struct kvm_mips_tlb*,unsigned long,int) ; 
 unsigned long kvm_read_c0_guest_entryhi (struct mips_coproc*) ; 

enum kvm_mips_fault_result kvm_trap_emul_gva_fault(struct kvm_vcpu *vcpu,
						   unsigned long gva,
						   bool write)
{
	struct mips_coproc *cop0 = vcpu->arch.cop0;
	struct kvm_mips_tlb *tlb;
	int index;

	if (KVM_GUEST_KSEGX(gva) == KVM_GUEST_KSEG0) {
		if (kvm_mips_handle_kseg0_tlb_fault(gva, vcpu, write) < 0)
			return KVM_MIPS_GPA;
	} else if ((KVM_GUEST_KSEGX(gva) < KVM_GUEST_KSEG0) ||
		   KVM_GUEST_KSEGX(gva) == KVM_GUEST_KSEG23) {
		/* Address should be in the guest TLB */
		index = kvm_mips_guest_tlb_lookup(vcpu, (gva & VPN2_MASK) |
			  (kvm_read_c0_guest_entryhi(cop0) & KVM_ENTRYHI_ASID));
		if (index < 0)
			return KVM_MIPS_TLB;
		tlb = &vcpu->arch.guest_tlb[index];

		/* Entry should be valid, and dirty for writes */
		if (!TLB_IS_VALID(*tlb, gva))
			return KVM_MIPS_TLBINV;
		if (write && !TLB_IS_DIRTY(*tlb, gva))
			return KVM_MIPS_TLBMOD;

		if (kvm_mips_handle_mapped_seg_tlb_fault(vcpu, tlb, gva, write))
			return KVM_MIPS_GPA;
	} else {
		return KVM_MIPS_GVA;
	}

	return KVM_MIPS_MAPPED;
}
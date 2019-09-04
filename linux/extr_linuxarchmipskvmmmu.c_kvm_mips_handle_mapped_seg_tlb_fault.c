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
struct TYPE_2__ {int /*<<< orphan*/  pc; } ;
struct kvm_vcpu {TYPE_1__ arch; struct kvm* kvm; } ;
struct kvm_mips_tlb {long* tlb_lo; } ;
struct kvm {int /*<<< orphan*/  mmu_lock; } ;
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 long ENTRYLO_V ; 
 unsigned long KVM_GUEST_COMMPAGE_ADDR ; 
 int KVM_GUEST_KERNEL_MODE (struct kvm_vcpu*) ; 
 int PAGE_MASK ; 
 unsigned long PAGE_SIZE ; 
 size_t TLB_LO_IDX (struct kvm_mips_tlb,unsigned long) ; 
 unsigned long VPN2_MASK ; 
 int /*<<< orphan*/  __pgprot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_debug (char*,int /*<<< orphan*/ ,long,long) ; 
 int /*<<< orphan*/  kvm_err (char*,unsigned long) ; 
 int /*<<< orphan*/  kvm_mips_gpa_pte_to_gva_mapped (int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  kvm_mips_host_tlb_inv (struct kvm_vcpu*,unsigned long,int,int) ; 
 scalar_t__ kvm_mips_map_page (struct kvm_vcpu*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kvm_mips_pte_for_gpa (struct kvm*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kvm_trap_emul_pte_for_gva (struct kvm_vcpu*,unsigned long) ; 
 int /*<<< orphan*/  mips3_tlbpfn_to_paddr (long) ; 
 int /*<<< orphan*/  pfn_pte (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int kvm_mips_handle_mapped_seg_tlb_fault(struct kvm_vcpu *vcpu,
					 struct kvm_mips_tlb *tlb,
					 unsigned long gva,
					 bool write_fault)
{
	struct kvm *kvm = vcpu->kvm;
	long tlb_lo[2];
	pte_t pte_gpa[2], *ptep_buddy, *ptep_gva;
	unsigned int idx = TLB_LO_IDX(*tlb, gva);
	bool kernel = KVM_GUEST_KERNEL_MODE(vcpu);

	tlb_lo[0] = tlb->tlb_lo[0];
	tlb_lo[1] = tlb->tlb_lo[1];

	/*
	 * The commpage address must not be mapped to anything else if the guest
	 * TLB contains entries nearby, or commpage accesses will break.
	 */
	if (!((gva ^ KVM_GUEST_COMMPAGE_ADDR) & VPN2_MASK & (PAGE_MASK << 1)))
		tlb_lo[TLB_LO_IDX(*tlb, KVM_GUEST_COMMPAGE_ADDR)] = 0;

	/* Get the GPA page table entry */
	if (kvm_mips_map_page(vcpu, mips3_tlbpfn_to_paddr(tlb_lo[idx]),
			      write_fault, &pte_gpa[idx], NULL) < 0)
		return -1;

	/* And its GVA buddy's GPA page table entry if it also exists */
	pte_gpa[!idx] = pfn_pte(0, __pgprot(0));
	if (tlb_lo[!idx] & ENTRYLO_V) {
		spin_lock(&kvm->mmu_lock);
		ptep_buddy = kvm_mips_pte_for_gpa(kvm, NULL,
					mips3_tlbpfn_to_paddr(tlb_lo[!idx]));
		if (ptep_buddy)
			pte_gpa[!idx] = *ptep_buddy;
		spin_unlock(&kvm->mmu_lock);
	}

	/* Get the GVA page table entry pair */
	ptep_gva = kvm_trap_emul_pte_for_gva(vcpu, gva & ~PAGE_SIZE);
	if (!ptep_gva) {
		kvm_err("No ptep for gva %lx\n", gva);
		return -1;
	}

	/* Copy a pair of entries from GPA page table to GVA page table */
	ptep_gva[0] = kvm_mips_gpa_pte_to_gva_mapped(pte_gpa[0], tlb_lo[0]);
	ptep_gva[1] = kvm_mips_gpa_pte_to_gva_mapped(pte_gpa[1], tlb_lo[1]);

	/* Invalidate this entry in the TLB, current guest mode ASID only */
	kvm_mips_host_tlb_inv(vcpu, gva, !kernel, kernel);

	kvm_debug("@ %#lx tlb_lo0: 0x%08lx tlb_lo1: 0x%08lx\n", vcpu->arch.pc,
		  tlb->tlb_lo[0], tlb->tlb_lo[1]);

	return 0;
}
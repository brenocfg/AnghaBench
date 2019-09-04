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
typedef  unsigned int u8 ;
typedef  unsigned int u32 ;
struct TYPE_3__ {unsigned int pkru; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct kvm_mmu {unsigned int* permissions; unsigned int pkru_mask; } ;
struct TYPE_4__ {int (* get_cpl ) (struct kvm_vcpu*) ;unsigned long (* get_rflags ) (struct kvm_vcpu*) ;} ;

/* Variables and functions */
 unsigned int PFERR_PK_MASK ; 
 unsigned int PFERR_PRESENT_MASK ; 
 int PFERR_RSVD_BIT ; 
 unsigned int PFERR_RSVD_MASK ; 
 unsigned int PT_USER_MASK ; 
 int PT_USER_SHIFT ; 
 int /*<<< orphan*/  WARN_ON (unsigned int) ; 
 unsigned long X86_EFLAGS_AC ; 
 int X86_EFLAGS_AC_BIT ; 
 TYPE_2__* kvm_x86_ops ; 
 int stub1 (struct kvm_vcpu*) ; 
 unsigned long stub2 (struct kvm_vcpu*) ; 
 scalar_t__ unlikely (unsigned int) ; 

__attribute__((used)) static inline u8 permission_fault(struct kvm_vcpu *vcpu, struct kvm_mmu *mmu,
				  unsigned pte_access, unsigned pte_pkey,
				  unsigned pfec)
{
	int cpl = kvm_x86_ops->get_cpl(vcpu);
	unsigned long rflags = kvm_x86_ops->get_rflags(vcpu);

	/*
	 * If CPL < 3, SMAP prevention are disabled if EFLAGS.AC = 1.
	 *
	 * If CPL = 3, SMAP applies to all supervisor-mode data accesses
	 * (these are implicit supervisor accesses) regardless of the value
	 * of EFLAGS.AC.
	 *
	 * This computes (cpl < 3) && (rflags & X86_EFLAGS_AC), leaving
	 * the result in X86_EFLAGS_AC. We then insert it in place of
	 * the PFERR_RSVD_MASK bit; this bit will always be zero in pfec,
	 * but it will be one in index if SMAP checks are being overridden.
	 * It is important to keep this branchless.
	 */
	unsigned long smap = (cpl - 3) & (rflags & X86_EFLAGS_AC);
	int index = (pfec >> 1) +
		    (smap >> (X86_EFLAGS_AC_BIT - PFERR_RSVD_BIT + 1));
	bool fault = (mmu->permissions[index] >> pte_access) & 1;
	u32 errcode = PFERR_PRESENT_MASK;

	WARN_ON(pfec & (PFERR_PK_MASK | PFERR_RSVD_MASK));
	if (unlikely(mmu->pkru_mask)) {
		u32 pkru_bits, offset;

		/*
		* PKRU defines 32 bits, there are 16 domains and 2
		* attribute bits per domain in pkru.  pte_pkey is the
		* index of the protection domain, so pte_pkey * 2 is
		* is the index of the first bit for the domain.
		*/
		pkru_bits = (vcpu->arch.pkru >> (pte_pkey * 2)) & 3;

		/* clear present bit, replace PFEC.RSVD with ACC_USER_MASK. */
		offset = (pfec & ~1) +
			((pte_access & PT_USER_MASK) << (PFERR_RSVD_BIT - PT_USER_SHIFT));

		pkru_bits &= mmu->pkru_mask >> offset;
		errcode |= -pkru_bits & PFERR_PK_MASK;
		fault |= (pkru_bits != 0);
	}

	return -(u32)fault & errcode;
}
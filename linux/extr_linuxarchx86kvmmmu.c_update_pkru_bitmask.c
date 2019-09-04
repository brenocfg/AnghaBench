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
struct kvm_vcpu {int dummy; } ;
struct kvm_mmu {unsigned int pkru_mask; int /*<<< orphan*/  permissions; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 unsigned int PFERR_FETCH_MASK ; 
 unsigned int PFERR_RSVD_MASK ; 
 unsigned int PFERR_USER_MASK ; 
 unsigned int PFERR_WRITE_MASK ; 
 int /*<<< orphan*/  X86_CR4_PKE ; 
 int /*<<< orphan*/  is_long_mode (struct kvm_vcpu*) ; 
 int is_write_protection (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_read_cr4_bits (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void update_pkru_bitmask(struct kvm_vcpu *vcpu, struct kvm_mmu *mmu,
				bool ept)
{
	unsigned bit;
	bool wp;

	if (ept) {
		mmu->pkru_mask = 0;
		return;
	}

	/* PKEY is enabled only if CR4.PKE and EFER.LMA are both set. */
	if (!kvm_read_cr4_bits(vcpu, X86_CR4_PKE) || !is_long_mode(vcpu)) {
		mmu->pkru_mask = 0;
		return;
	}

	wp = is_write_protection(vcpu);

	for (bit = 0; bit < ARRAY_SIZE(mmu->permissions); ++bit) {
		unsigned pfec, pkey_bits;
		bool check_pkey, check_write, ff, uf, wf, pte_user;

		pfec = bit << 1;
		ff = pfec & PFERR_FETCH_MASK;
		uf = pfec & PFERR_USER_MASK;
		wf = pfec & PFERR_WRITE_MASK;

		/* PFEC.RSVD is replaced by ACC_USER_MASK. */
		pte_user = pfec & PFERR_RSVD_MASK;

		/*
		 * Only need to check the access which is not an
		 * instruction fetch and is to a user page.
		 */
		check_pkey = (!ff && pte_user);
		/*
		 * write access is controlled by PKRU if it is a
		 * user access or CR0.WP = 1.
		 */
		check_write = check_pkey && wf && (uf || wp);

		/* PKRU.AD stops both read and write access. */
		pkey_bits = !!check_pkey;
		/* PKRU.WD stops write access. */
		pkey_bits |= (!!check_write) << 1;

		mmu->pkru_mask |= (pkey_bits & 3) << pfec;
	}
}
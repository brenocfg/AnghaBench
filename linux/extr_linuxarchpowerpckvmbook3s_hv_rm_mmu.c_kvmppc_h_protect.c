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
typedef  unsigned long u64 ;
struct revmap_entry {unsigned long guest_rpte; } ;
struct kvm_vcpu {struct kvm* kvm; } ;
struct TYPE_4__ {int /*<<< orphan*/ * rev; scalar_t__ virt; } ;
struct TYPE_3__ {int /*<<< orphan*/  mmio_update; TYPE_2__ hpt; } ;
struct kvm {TYPE_1__ arch; } ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_FTR_ARCH_300 ; 
 unsigned long HPTE_R_C ; 
 unsigned long HPTE_R_KEY_HI ; 
 unsigned long HPTE_R_KEY_LO ; 
 unsigned long HPTE_R_N ; 
 unsigned long HPTE_R_PP ; 
 unsigned long HPTE_R_PP0 ; 
 unsigned long HPTE_R_R ; 
 unsigned long HPTE_V_ABSENT ; 
 unsigned long HPTE_V_HVLOCK ; 
 unsigned long HPTE_V_VALID ; 
 unsigned long H_AVPN ; 
 long H_FUNCTION ; 
 long H_NOT_FOUND ; 
 long H_PARAMETER ; 
 long H_SUCCESS ; 
 int /*<<< orphan*/  __unlock_hpte (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  atomic64_inc (int /*<<< orphan*/ *) ; 
 unsigned long be64_to_cpu (int /*<<< orphan*/ ) ; 
 unsigned long compute_tlbie_rb (unsigned long,unsigned long,unsigned long) ; 
 scalar_t__ cpu_has_feature (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  cpu_to_be64 (unsigned long) ; 
 int /*<<< orphan*/  do_tlbies (struct kvm*,unsigned long*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  global_invalidates (struct kvm*) ; 
 scalar_t__ hpte_is_writable (unsigned long) ; 
 unsigned long hpte_make_readonly (unsigned long) ; 
 unsigned long hpte_new_to_old_v (unsigned long,unsigned long) ; 
 scalar_t__ is_mmio_hpte (unsigned long,unsigned long) ; 
 scalar_t__ kvm_is_radix (struct kvm*) ; 
 unsigned long kvmppc_hpt_npte (TYPE_2__*) ; 
 int /*<<< orphan*/  note_hpte_modification (struct kvm*,struct revmap_entry*) ; 
 struct revmap_entry* real_vmalloc_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  try_lock_hpte (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  unlock_hpte (int /*<<< orphan*/ *,unsigned long) ; 

long kvmppc_h_protect(struct kvm_vcpu *vcpu, unsigned long flags,
		      unsigned long pte_index, unsigned long avpn,
		      unsigned long va)
{
	struct kvm *kvm = vcpu->kvm;
	__be64 *hpte;
	struct revmap_entry *rev;
	unsigned long v, r, rb, mask, bits;
	u64 pte_v, pte_r;

	if (kvm_is_radix(kvm))
		return H_FUNCTION;
	if (pte_index >= kvmppc_hpt_npte(&kvm->arch.hpt))
		return H_PARAMETER;

	hpte = (__be64 *)(kvm->arch.hpt.virt + (pte_index << 4));
	while (!try_lock_hpte(hpte, HPTE_V_HVLOCK))
		cpu_relax();
	v = pte_v = be64_to_cpu(hpte[0]);
	if (cpu_has_feature(CPU_FTR_ARCH_300))
		v = hpte_new_to_old_v(v, be64_to_cpu(hpte[1]));
	if ((v & (HPTE_V_ABSENT | HPTE_V_VALID)) == 0 ||
	    ((flags & H_AVPN) && (v & ~0x7fUL) != avpn)) {
		__unlock_hpte(hpte, pte_v);
		return H_NOT_FOUND;
	}

	pte_r = be64_to_cpu(hpte[1]);
	bits = (flags << 55) & HPTE_R_PP0;
	bits |= (flags << 48) & HPTE_R_KEY_HI;
	bits |= flags & (HPTE_R_PP | HPTE_R_N | HPTE_R_KEY_LO);

	/* Update guest view of 2nd HPTE dword */
	mask = HPTE_R_PP0 | HPTE_R_PP | HPTE_R_N |
		HPTE_R_KEY_HI | HPTE_R_KEY_LO;
	rev = real_vmalloc_addr(&kvm->arch.hpt.rev[pte_index]);
	if (rev) {
		r = (rev->guest_rpte & ~mask) | bits;
		rev->guest_rpte = r;
		note_hpte_modification(kvm, rev);
	}

	/* Update HPTE */
	if (v & HPTE_V_VALID) {
		/*
		 * If the page is valid, don't let it transition from
		 * readonly to writable.  If it should be writable, we'll
		 * take a trap and let the page fault code sort it out.
		 */
		r = (pte_r & ~mask) | bits;
		if (hpte_is_writable(r) && !hpte_is_writable(pte_r))
			r = hpte_make_readonly(r);
		/* If the PTE is changing, invalidate it first */
		if (r != pte_r) {
			rb = compute_tlbie_rb(v, r, pte_index);
			hpte[0] = cpu_to_be64((pte_v & ~HPTE_V_VALID) |
					      HPTE_V_ABSENT);
			do_tlbies(kvm, &rb, 1, global_invalidates(kvm), true);
			/* Don't lose R/C bit updates done by hardware */
			r |= be64_to_cpu(hpte[1]) & (HPTE_R_R | HPTE_R_C);
			hpte[1] = cpu_to_be64(r);
		}
	}
	unlock_hpte(hpte, pte_v & ~HPTE_V_HVLOCK);
	asm volatile("ptesync" : : : "memory");
	if (is_mmio_hpte(v, pte_r))
		atomic64_inc(&kvm->arch.mmio_update);

	return H_SUCCESS;
}
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
struct revmap_entry {unsigned long guest_rpte; } ;
struct TYPE_6__ {unsigned long* gpr; } ;
struct TYPE_7__ {TYPE_2__ regs; } ;
struct kvm_vcpu {TYPE_3__ arch; struct kvm* kvm; } ;
struct TYPE_8__ {scalar_t__ virt; int /*<<< orphan*/ * rev; } ;
struct TYPE_5__ {TYPE_4__ hpt; } ;
struct kvm {TYPE_1__ arch; } ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 unsigned long HPTE_R_C ; 
 unsigned long HPTE_R_R ; 
 unsigned long HPTE_V_ABSENT ; 
 unsigned long HPTE_V_HVLOCK ; 
 unsigned long HPTE_V_VALID ; 
 long H_FUNCTION ; 
 long H_NOT_FOUND ; 
 long H_PARAMETER ; 
 long H_SUCCESS ; 
 unsigned long be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  cpu_to_be64 (unsigned long) ; 
 int /*<<< orphan*/  eieio () ; 
 scalar_t__ kvm_is_radix (struct kvm*) ; 
 unsigned long kvmppc_hpt_npte (TYPE_4__*) ; 
 int /*<<< orphan*/  kvmppc_invalidate_hpte (struct kvm*,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  kvmppc_set_dirty_from_hpte (struct kvm*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  note_hpte_modification (struct kvm*,struct revmap_entry*) ; 
 struct revmap_entry* real_vmalloc_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  try_lock_hpte (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  unlock_hpte (int /*<<< orphan*/ *,unsigned long) ; 

long kvmppc_h_clear_mod(struct kvm_vcpu *vcpu, unsigned long flags,
			unsigned long pte_index)
{
	struct kvm *kvm = vcpu->kvm;
	__be64 *hpte;
	unsigned long v, r, gr;
	struct revmap_entry *rev;
	long ret = H_NOT_FOUND;

	if (kvm_is_radix(kvm))
		return H_FUNCTION;
	if (pte_index >= kvmppc_hpt_npte(&kvm->arch.hpt))
		return H_PARAMETER;

	rev = real_vmalloc_addr(&kvm->arch.hpt.rev[pte_index]);
	hpte = (__be64 *)(kvm->arch.hpt.virt + (pte_index << 4));
	while (!try_lock_hpte(hpte, HPTE_V_HVLOCK))
		cpu_relax();
	v = be64_to_cpu(hpte[0]);
	r = be64_to_cpu(hpte[1]);
	if (!(v & (HPTE_V_VALID | HPTE_V_ABSENT)))
		goto out;

	gr = rev->guest_rpte;
	if (gr & HPTE_R_C) {
		rev->guest_rpte &= ~HPTE_R_C;
		note_hpte_modification(kvm, rev);
	}
	if (v & HPTE_V_VALID) {
		/* need to make it temporarily absent so C is stable */
		hpte[0] |= cpu_to_be64(HPTE_V_ABSENT);
		kvmppc_invalidate_hpte(kvm, hpte, pte_index);
		r = be64_to_cpu(hpte[1]);
		gr |= r & (HPTE_R_R | HPTE_R_C);
		if (r & HPTE_R_C) {
			hpte[1] = cpu_to_be64(r & ~HPTE_R_C);
			eieio();
			kvmppc_set_dirty_from_hpte(kvm, v, gr);
		}
	}
	vcpu->arch.regs.gpr[4] = gr;
	ret = H_SUCCESS;
 out:
	unlock_hpte(hpte, v & ~HPTE_V_HVLOCK);
	return ret;
}
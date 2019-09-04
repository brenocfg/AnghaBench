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
typedef  scalar_t__ u64 ;
struct kvm_vcpu {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  direct; } ;
struct kvm_mmu_page {int spt; TYPE_1__ role; } ;
typedef  int /*<<< orphan*/  gfn_t ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ cmpxchg64 (scalar_t__*,scalar_t__,scalar_t__) ; 
 scalar_t__ is_writable_pte (scalar_t__) ; 
 int /*<<< orphan*/  kvm_mmu_page_get_gfn (struct kvm_mmu_page*,scalar_t__*) ; 
 int /*<<< orphan*/  kvm_vcpu_mark_page_dirty (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
fast_pf_fix_direct_spte(struct kvm_vcpu *vcpu, struct kvm_mmu_page *sp,
			u64 *sptep, u64 old_spte, u64 new_spte)
{
	gfn_t gfn;

	WARN_ON(!sp->role.direct);

	/*
	 * Theoretically we could also set dirty bit (and flush TLB) here in
	 * order to eliminate unnecessary PML logging. See comments in
	 * set_spte. But fast_page_fault is very unlikely to happen with PML
	 * enabled, so we do not do this. This might result in the same GPA
	 * to be logged in PML buffer again when the write really happens, and
	 * eventually to be called by mark_page_dirty twice. But it's also no
	 * harm. This also avoids the TLB flush needed after setting dirty bit
	 * so non-PML cases won't be impacted.
	 *
	 * Compare with set_spte where instead shadow_dirty_mask is set.
	 */
	if (cmpxchg64(sptep, old_spte, new_spte) != old_spte)
		return false;

	if (is_writable_pte(new_spte) && !is_writable_pte(old_spte)) {
		/*
		 * The gfn of direct spte is stable since it is
		 * calculated by sp->gfn.
		 */
		gfn = kvm_mmu_page_get_gfn(sp, sptep - sp->spt);
		kvm_vcpu_mark_page_dirty(vcpu, gfn);
	}

	return true;
}
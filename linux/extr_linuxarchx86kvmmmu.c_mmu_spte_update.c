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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 scalar_t__ is_accessed_spte (int /*<<< orphan*/ ) ; 
 scalar_t__ is_dirty_spte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_shadow_present_pte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_writable_pte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_set_pfn_accessed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_set_pfn_dirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmu_spte_update_no_track (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ spte_can_locklessly_be_made_writable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spte_to_pfn (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool mmu_spte_update(u64 *sptep, u64 new_spte)
{
	bool flush = false;
	u64 old_spte = mmu_spte_update_no_track(sptep, new_spte);

	if (!is_shadow_present_pte(old_spte))
		return false;

	/*
	 * For the spte updated out of mmu-lock is safe, since
	 * we always atomically update it, see the comments in
	 * spte_has_volatile_bits().
	 */
	if (spte_can_locklessly_be_made_writable(old_spte) &&
	      !is_writable_pte(new_spte))
		flush = true;

	/*
	 * Flush TLB when accessed/dirty states are changed in the page tables,
	 * to guarantee consistency between TLB and page tables.
	 */

	if (is_accessed_spte(old_spte) && !is_accessed_spte(new_spte)) {
		flush = true;
		kvm_set_pfn_accessed(spte_to_pfn(old_spte));
	}

	if (is_dirty_spte(old_spte) && !is_dirty_spte(new_spte)) {
		flush = true;
		kvm_set_pfn_dirty(spte_to_pfn(old_spte));
	}

	return flush;
}
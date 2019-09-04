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
 int /*<<< orphan*/  clear_bit (scalar_t__,unsigned long*) ; 
 scalar_t__ ffs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_accessed_spte (int /*<<< orphan*/ ) ; 
 scalar_t__ is_writable_pte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_set_pfn_dirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_spte_for_access_track (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmu_spte_get_lockless (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmu_spte_update_no_track (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shadow_accessed_mask ; 
 scalar_t__ spte_ad_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spte_to_pfn (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool mmu_spte_age(u64 *sptep)
{
	u64 spte = mmu_spte_get_lockless(sptep);

	if (!is_accessed_spte(spte))
		return false;

	if (spte_ad_enabled(spte)) {
		clear_bit((ffs(shadow_accessed_mask) - 1),
			  (unsigned long *)sptep);
	} else {
		/*
		 * Capture the dirty status of the page, so that it doesn't get
		 * lost when the SPTE is marked for access tracking.
		 */
		if (is_writable_pte(spte))
			kvm_set_pfn_dirty(spte_to_pfn(spte));

		spte = mark_spte_for_access_track(spte);
		mmu_spte_update_no_track(sptep, spte);
	}

	return true;
}
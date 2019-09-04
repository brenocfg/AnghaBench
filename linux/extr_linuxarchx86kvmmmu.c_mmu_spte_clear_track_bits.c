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
typedef  int /*<<< orphan*/  kvm_pfn_t ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __update_clear_spte_fast (int /*<<< orphan*/ *,unsigned long long) ; 
 int /*<<< orphan*/  __update_clear_spte_slow (int /*<<< orphan*/ *,unsigned long long) ; 
 scalar_t__ is_accessed_spte (int /*<<< orphan*/ ) ; 
 scalar_t__ is_dirty_spte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_shadow_present_pte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_is_reserved_pfn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_set_pfn_accessed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_set_pfn_dirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfn_to_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spte_has_volatile_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spte_to_pfn (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mmu_spte_clear_track_bits(u64 *sptep)
{
	kvm_pfn_t pfn;
	u64 old_spte = *sptep;

	if (!spte_has_volatile_bits(old_spte))
		__update_clear_spte_fast(sptep, 0ull);
	else
		old_spte = __update_clear_spte_slow(sptep, 0ull);

	if (!is_shadow_present_pte(old_spte))
		return 0;

	pfn = spte_to_pfn(old_spte);

	/*
	 * KVM does not hold the refcount of the page used by
	 * kvm mmu, before reclaiming the page, we should
	 * unmap it from mmu first.
	 */
	WARN_ON(!kvm_is_reserved_pfn(pfn) && !page_count(pfn_to_page(pfn)));

	if (is_accessed_spte(old_spte))
		kvm_set_pfn_accessed(pfn);

	if (is_dirty_spte(old_spte))
		kvm_set_pfn_dirty(pfn);

	return 1;
}
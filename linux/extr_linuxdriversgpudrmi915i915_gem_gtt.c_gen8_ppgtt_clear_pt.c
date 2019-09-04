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
typedef  int /*<<< orphan*/  u64 ;
struct i915_page_table {unsigned int used_ptes; } ;
struct TYPE_2__ {int /*<<< orphan*/  daddr; } ;
struct i915_address_space {TYPE_1__ scratch_page; } ;
typedef  int /*<<< orphan*/  gen8_pte_t ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  I915_CACHE_LLC ; 
 unsigned int gen8_pte_count (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen8_pte_encode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int gen8_pte_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kmap_atomic_px (struct i915_page_table*) ; 
 int /*<<< orphan*/  kunmap_atomic (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool gen8_ppgtt_clear_pt(struct i915_address_space *vm,
				struct i915_page_table *pt,
				u64 start, u64 length)
{
	unsigned int num_entries = gen8_pte_count(start, length);
	unsigned int pte = gen8_pte_index(start);
	unsigned int pte_end = pte + num_entries;
	const gen8_pte_t scratch_pte =
		gen8_pte_encode(vm->scratch_page.daddr, I915_CACHE_LLC, 0);
	gen8_pte_t *vaddr;

	GEM_BUG_ON(num_entries > pt->used_ptes);

	pt->used_ptes -= num_entries;
	if (!pt->used_ptes)
		return true;

	vaddr = kmap_atomic_px(pt);
	while (pte < pte_end)
		vaddr[pte++] = scratch_pte;
	kunmap_atomic(vaddr);

	return false;
}
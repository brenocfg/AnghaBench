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
struct kvm_memory_slot {scalar_t__ dirty_bitmap; } ;
struct kvm {int dummy; } ;
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 unsigned long _PAGE_DIRTY ; 
 struct kvm_memory_slot* gfn_to_memslot (struct kvm*,unsigned long) ; 
 int /*<<< orphan*/  kvmppc_radix_tlbie_page (struct kvm*,unsigned long,unsigned int) ; 
 unsigned long kvmppc_radix_update_pte (struct kvm*,int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ ,unsigned long,unsigned int) ; 
 int /*<<< orphan*/  kvmppc_update_dirty_map (struct kvm_memory_slot*,unsigned long,unsigned long) ; 

__attribute__((used)) static void kvmppc_unmap_pte(struct kvm *kvm, pte_t *pte,
			     unsigned long gpa, unsigned int shift)

{
	unsigned long page_size = 1ul << shift;
	unsigned long old;

	old = kvmppc_radix_update_pte(kvm, pte, ~0UL, 0, gpa, shift);
	kvmppc_radix_tlbie_page(kvm, gpa, shift);
	if (old & _PAGE_DIRTY) {
		unsigned long gfn = gpa >> PAGE_SHIFT;
		struct kvm_memory_slot *memslot;

		memslot = gfn_to_memslot(kvm, gfn);
		if (memslot && memslot->dirty_bitmap)
			kvmppc_update_dirty_map(memslot, gfn, page_size);
	}
}
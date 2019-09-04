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
struct kvm_memory_slot {scalar_t__ dirty_bitmap; } ;
struct TYPE_2__ {int /*<<< orphan*/  pgtable; } ;
struct kvm {TYPE_1__ arch; } ;
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 unsigned long PAGE_SIZE ; 
 unsigned long _PAGE_DIRTY ; 
 int /*<<< orphan*/ * __find_linux_pte (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ *,unsigned int*) ; 
 int /*<<< orphan*/  kvmppc_radix_tlbie_page (struct kvm*,unsigned long,unsigned int) ; 
 unsigned long kvmppc_radix_update_pte (struct kvm*,int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ ,unsigned long,unsigned int) ; 
 int /*<<< orphan*/  kvmppc_update_dirty_map (struct kvm_memory_slot*,unsigned long,unsigned long) ; 
 scalar_t__ pte_present (int /*<<< orphan*/ ) ; 

int kvm_unmap_radix(struct kvm *kvm, struct kvm_memory_slot *memslot,
		    unsigned long gfn)
{
	pte_t *ptep;
	unsigned long gpa = gfn << PAGE_SHIFT;
	unsigned int shift;
	unsigned long old;

	ptep = __find_linux_pte(kvm->arch.pgtable, gpa, NULL, &shift);
	if (ptep && pte_present(*ptep)) {
		old = kvmppc_radix_update_pte(kvm, ptep, ~0UL, 0,
					      gpa, shift);
		kvmppc_radix_tlbie_page(kvm, gpa, shift);
		if ((old & _PAGE_DIRTY) && memslot->dirty_bitmap) {
			unsigned long psize = PAGE_SIZE;
			if (shift)
				psize = 1ul << shift;
			kvmppc_update_dirty_map(memslot, gfn, psize);
		}
	}
	return 0;				
}
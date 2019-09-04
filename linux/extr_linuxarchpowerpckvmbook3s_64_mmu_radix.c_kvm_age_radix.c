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
struct kvm_memory_slot {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pgtable; } ;
struct kvm {TYPE_1__ arch; } ;
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  _PAGE_ACCESSED ; 
 int /*<<< orphan*/ * __find_linux_pte (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ *,unsigned int*) ; 
 int /*<<< orphan*/  kvmppc_radix_update_pte (struct kvm*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,unsigned int) ; 
 scalar_t__ pte_present (int /*<<< orphan*/ ) ; 
 scalar_t__ pte_young (int /*<<< orphan*/ ) ; 

int kvm_age_radix(struct kvm *kvm, struct kvm_memory_slot *memslot,
		  unsigned long gfn)
{
	pte_t *ptep;
	unsigned long gpa = gfn << PAGE_SHIFT;
	unsigned int shift;
	int ref = 0;

	ptep = __find_linux_pte(kvm->arch.pgtable, gpa, NULL, &shift);
	if (ptep && pte_present(*ptep) && pte_young(*ptep)) {
		kvmppc_radix_update_pte(kvm, ptep, _PAGE_ACCESSED, 0,
					gpa, shift);
		/* XXX need to flush tlb here? */
		ref = 1;
	}
	return ref;
}
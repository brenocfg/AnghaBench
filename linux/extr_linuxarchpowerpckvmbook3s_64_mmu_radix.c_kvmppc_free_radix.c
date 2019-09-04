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
struct TYPE_2__ {int /*<<< orphan*/ * pgtable; } ;
struct kvm {TYPE_1__ arch; int /*<<< orphan*/  mm; } ;
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 unsigned long PTRS_PER_PGD ; 
 int /*<<< orphan*/  kvmppc_unmap_free_pud (struct kvm*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pgd_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pgd_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pgd_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pud_offset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void kvmppc_free_radix(struct kvm *kvm)
{
	unsigned long ig;
	pgd_t *pgd;

	if (!kvm->arch.pgtable)
		return;
	pgd = kvm->arch.pgtable;
	for (ig = 0; ig < PTRS_PER_PGD; ++ig, ++pgd) {
		pud_t *pud;

		if (!pgd_present(*pgd))
			continue;
		pud = pud_offset(pgd, 0);
		kvmppc_unmap_free_pud(kvm, pud);
		pgd_clear(pgd);
	}
	pgd_free(kvm->mm, kvm->arch.pgtable);
	kvm->arch.pgtable = NULL;
}
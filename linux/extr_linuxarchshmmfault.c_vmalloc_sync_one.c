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
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgd_t ;
struct TYPE_2__ {int /*<<< orphan*/ * pgd; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 TYPE_1__ init_mm ; 
 unsigned int pgd_index (unsigned long) ; 
 int /*<<< orphan*/  pgd_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmd_offset (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ pmd_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pud_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pud_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_pmd (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_pud (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline pmd_t *vmalloc_sync_one(pgd_t *pgd, unsigned long address)
{
	unsigned index = pgd_index(address);
	pgd_t *pgd_k;
	pud_t *pud, *pud_k;
	pmd_t *pmd, *pmd_k;

	pgd += index;
	pgd_k = init_mm.pgd + index;

	if (!pgd_present(*pgd_k))
		return NULL;

	pud = pud_offset(pgd, address);
	pud_k = pud_offset(pgd_k, address);
	if (!pud_present(*pud_k))
		return NULL;

	if (!pud_present(*pud))
	    set_pud(pud, *pud_k);

	pmd = pmd_offset(pud, address);
	pmd_k = pmd_offset(pud_k, address);
	if (!pmd_present(*pmd_k))
		return NULL;

	if (!pmd_present(*pmd))
		set_pmd(pmd, *pmd_k);
	else {
		/*
		 * The page tables are fully synchronised so there must
		 * be another reason for the fault. Return NULL here to
		 * signal that we have not taken care of the fault.
		 */
		BUG_ON(pmd_page(*pmd) != pmd_page(*pmd_k));
		return NULL;
	}

	return pmd_k;
}
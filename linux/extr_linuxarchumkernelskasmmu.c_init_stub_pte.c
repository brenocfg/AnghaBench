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
struct mm_struct {int dummy; } ;
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  _PAGE_PRESENT ; 
 int /*<<< orphan*/  __pgprot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mk_pte (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pgd_offset (struct mm_struct*,unsigned long) ; 
 int /*<<< orphan*/ * pmd_alloc (struct mm_struct*,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pmd_free (struct mm_struct*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pte_alloc_map (struct mm_struct*,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pte_mkread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pud_alloc (struct mm_struct*,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pud_free (struct mm_struct*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  virt_to_page (unsigned long) ; 

__attribute__((used)) static int init_stub_pte(struct mm_struct *mm, unsigned long proc,
			 unsigned long kernel)
{
	pgd_t *pgd;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;

	pgd = pgd_offset(mm, proc);
	pud = pud_alloc(mm, pgd, proc);
	if (!pud)
		goto out;

	pmd = pmd_alloc(mm, pud, proc);
	if (!pmd)
		goto out_pmd;

	pte = pte_alloc_map(mm, pmd, proc);
	if (!pte)
		goto out_pte;

	*pte = mk_pte(virt_to_page(kernel), __pgprot(_PAGE_PRESENT));
	*pte = pte_mkread(*pte);
	return 0;

 out_pte:
	pmd_free(mm, pmd);
 out_pmd:
	pud_free(mm, pud);
 out:
	return -ENOMEM;
}
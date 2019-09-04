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
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  mm_dec_nr_pmds (struct mm_struct*) ; 
 int /*<<< orphan*/  pgtable_pmd_page_dtor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virt_to_page (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_pmds(struct mm_struct *mm, pmd_t *pmds[], int count)
{
	int i;

	for (i = 0; i < count; i++)
		if (pmds[i]) {
			pgtable_pmd_page_dtor(virt_to_page(pmds[i]));
			free_page((unsigned long)pmds[i]);
			mm_dec_nr_pmds(mm);
		}
}
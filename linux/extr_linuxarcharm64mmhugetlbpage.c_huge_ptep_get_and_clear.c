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
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 int find_num_contig (struct mm_struct*,unsigned long,int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  get_clear_flush (struct mm_struct*,unsigned long,int /*<<< orphan*/ *,size_t,int) ; 
 int /*<<< orphan*/  huge_ptep_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pte_cont (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptep_get_and_clear (struct mm_struct*,unsigned long,int /*<<< orphan*/ *) ; 

pte_t huge_ptep_get_and_clear(struct mm_struct *mm,
			      unsigned long addr, pte_t *ptep)
{
	int ncontig;
	size_t pgsize;
	pte_t orig_pte = huge_ptep_get(ptep);

	if (!pte_cont(orig_pte))
		return ptep_get_and_clear(mm, addr, ptep);

	ncontig = find_num_contig(mm, addr, ptep, &pgsize);

	return get_clear_flush(mm, addr, ptep, pgsize, ncontig);
}
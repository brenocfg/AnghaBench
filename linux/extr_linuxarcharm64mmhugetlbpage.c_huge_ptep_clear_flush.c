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
struct vm_area_struct {int /*<<< orphan*/  vm_mm; } ;
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_flush (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ *,size_t,int) ; 
 int find_num_contig (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  pte_cont (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptep_clear_flush (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ *) ; 

void huge_ptep_clear_flush(struct vm_area_struct *vma,
			   unsigned long addr, pte_t *ptep)
{
	size_t pgsize;
	int ncontig;

	if (!pte_cont(READ_ONCE(*ptep))) {
		ptep_clear_flush(vma, addr, ptep);
		return;
	}

	ncontig = find_num_contig(vma->vm_mm, addr, ptep, &pgsize);
	clear_flush(vma->vm_mm, addr, ptep, pgsize, ncontig);
}
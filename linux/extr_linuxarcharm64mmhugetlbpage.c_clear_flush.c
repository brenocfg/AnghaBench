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
struct vm_area_struct {int dummy; } ;
struct mm_struct {int dummy; } ;
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 struct vm_area_struct TLB_FLUSH_VMA (struct mm_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_tlb_range (struct vm_area_struct*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  pte_clear (struct mm_struct*,unsigned long,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void clear_flush(struct mm_struct *mm,
			     unsigned long addr,
			     pte_t *ptep,
			     unsigned long pgsize,
			     unsigned long ncontig)
{
	struct vm_area_struct vma = TLB_FLUSH_VMA(mm, 0);
	unsigned long i, saddr = addr;

	for (i = 0; i < ncontig; i++, addr += pgsize, ptep++)
		pte_clear(mm, addr, ptep);

	flush_tlb_range(&vma, saddr, addr);
}
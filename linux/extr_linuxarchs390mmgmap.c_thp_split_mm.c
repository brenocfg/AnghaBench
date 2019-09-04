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

/* Variables and functions */

__attribute__((used)) static inline void thp_split_mm(struct mm_struct *mm)
{
#ifdef CONFIG_TRANSPARENT_HUGEPAGE
	struct vm_area_struct *vma;
	unsigned long addr;

	for (vma = mm->mmap; vma != NULL; vma = vma->vm_next) {
		for (addr = vma->vm_start;
		     addr < vma->vm_end;
		     addr += PAGE_SIZE)
			follow_page(vma, addr, FOLL_SPLIT);
		vma->vm_flags &= ~VM_HUGEPAGE;
		vma->vm_flags |= VM_NOHUGEPAGE;
	}
	mm->def_flags |= VM_NOHUGEPAGE;
#endif
}
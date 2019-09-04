#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vm_unmapped_area_info {unsigned long length; unsigned long high_limit; unsigned long align_mask; unsigned long align_offset; int /*<<< orphan*/  low_limit; scalar_t__ flags; } ;
struct vm_area_struct {int dummy; } ;
struct TYPE_3__ {unsigned long asce_limit; } ;
struct mm_struct {TYPE_1__ context; int /*<<< orphan*/  mmap_base; } ;
struct file {int dummy; } ;
struct TYPE_4__ {struct mm_struct* mm; } ;

/* Variables and functions */
 unsigned long ENOMEM ; 
 unsigned long MAP_FIXED ; 
 unsigned long MAP_SHARED ; 
 unsigned long MMAP_ALIGN_MASK ; 
 unsigned long PAGE_ALIGN (unsigned long) ; 
 unsigned long PAGE_MASK ; 
 unsigned long PAGE_SHIFT ; 
 unsigned long TASK_SIZE ; 
 int crst_table_upgrade (struct mm_struct*,unsigned long) ; 
 TYPE_2__* current ; 
 struct vm_area_struct* find_vma (struct mm_struct*,unsigned long) ; 
 unsigned long mmap_min_addr ; 
 unsigned long vm_start_gap (struct vm_area_struct*) ; 
 unsigned long vm_unmapped_area (struct vm_unmapped_area_info*) ; 

unsigned long
arch_get_unmapped_area(struct file *filp, unsigned long addr,
		unsigned long len, unsigned long pgoff, unsigned long flags)
{
	struct mm_struct *mm = current->mm;
	struct vm_area_struct *vma;
	struct vm_unmapped_area_info info;
	int rc;

	if (len > TASK_SIZE - mmap_min_addr)
		return -ENOMEM;

	if (flags & MAP_FIXED)
		goto check_asce_limit;

	if (addr) {
		addr = PAGE_ALIGN(addr);
		vma = find_vma(mm, addr);
		if (TASK_SIZE - len >= addr && addr >= mmap_min_addr &&
		    (!vma || addr + len <= vm_start_gap(vma)))
			goto check_asce_limit;
	}

	info.flags = 0;
	info.length = len;
	info.low_limit = mm->mmap_base;
	info.high_limit = TASK_SIZE;
	if (filp || (flags & MAP_SHARED))
		info.align_mask = MMAP_ALIGN_MASK << PAGE_SHIFT;
	else
		info.align_mask = 0;
	info.align_offset = pgoff << PAGE_SHIFT;
	addr = vm_unmapped_area(&info);
	if (addr & ~PAGE_MASK)
		return addr;

check_asce_limit:
	if (addr + len > current->mm->context.asce_limit &&
	    addr + len <= TASK_SIZE) {
		rc = crst_table_upgrade(mm, addr + len);
		if (rc)
			return (unsigned long) rc;
	}

	return addr;
}
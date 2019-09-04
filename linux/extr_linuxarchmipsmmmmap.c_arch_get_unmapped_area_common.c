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
struct vm_unmapped_area_info {unsigned long length; unsigned long align_mask; unsigned long align_offset; unsigned long low_limit; unsigned long high_limit; scalar_t__ flags; } ;
struct vm_area_struct {int dummy; } ;
struct mm_struct {unsigned long mmap_base; } ;
struct file {int dummy; } ;
typedef  enum mmap_allocation_direction { ____Placeholder_mmap_allocation_direction } mmap_allocation_direction ;
struct TYPE_2__ {struct mm_struct* mm; } ;

/* Variables and functions */
 unsigned long COLOUR_ALIGN (unsigned long,unsigned long) ; 
 int DOWN ; 
 unsigned long EINVAL ; 
 unsigned long ENOMEM ; 
 unsigned long MAP_FIXED ; 
 unsigned long MAP_SHARED ; 
 unsigned long PAGE_ALIGN (unsigned long) ; 
 unsigned long PAGE_MASK ; 
 unsigned long PAGE_SHIFT ; 
 unsigned long PAGE_SIZE ; 
 unsigned long TASK_SIZE ; 
 scalar_t__ VM_UNMAPPED_AREA_TOPDOWN ; 
 TYPE_1__* current ; 
 struct vm_area_struct* find_vma (struct mm_struct*,unsigned long) ; 
 unsigned long shm_align_mask ; 
 scalar_t__ unlikely (int) ; 
 unsigned long vm_start_gap (struct vm_area_struct*) ; 
 unsigned long vm_unmapped_area (struct vm_unmapped_area_info*) ; 

__attribute__((used)) static unsigned long arch_get_unmapped_area_common(struct file *filp,
	unsigned long addr0, unsigned long len, unsigned long pgoff,
	unsigned long flags, enum mmap_allocation_direction dir)
{
	struct mm_struct *mm = current->mm;
	struct vm_area_struct *vma;
	unsigned long addr = addr0;
	int do_color_align;
	struct vm_unmapped_area_info info;

	if (unlikely(len > TASK_SIZE))
		return -ENOMEM;

	if (flags & MAP_FIXED) {
		/* Even MAP_FIXED mappings must reside within TASK_SIZE */
		if (TASK_SIZE - len < addr)
			return -EINVAL;

		/*
		 * We do not accept a shared mapping if it would violate
		 * cache aliasing constraints.
		 */
		if ((flags & MAP_SHARED) &&
		    ((addr - (pgoff << PAGE_SHIFT)) & shm_align_mask))
			return -EINVAL;
		return addr;
	}

	do_color_align = 0;
	if (filp || (flags & MAP_SHARED))
		do_color_align = 1;

	/* requesting a specific address */
	if (addr) {
		if (do_color_align)
			addr = COLOUR_ALIGN(addr, pgoff);
		else
			addr = PAGE_ALIGN(addr);

		vma = find_vma(mm, addr);
		if (TASK_SIZE - len >= addr &&
		    (!vma || addr + len <= vm_start_gap(vma)))
			return addr;
	}

	info.length = len;
	info.align_mask = do_color_align ? (PAGE_MASK & shm_align_mask) : 0;
	info.align_offset = pgoff << PAGE_SHIFT;

	if (dir == DOWN) {
		info.flags = VM_UNMAPPED_AREA_TOPDOWN;
		info.low_limit = PAGE_SIZE;
		info.high_limit = mm->mmap_base;
		addr = vm_unmapped_area(&info);

		if (!(addr & ~PAGE_MASK))
			return addr;

		/*
		 * A failed mmap() very likely causes application failure,
		 * so fall back to the bottom-up function here. This scenario
		 * can happen with large stack limits and large mmap()
		 * allocations.
		 */
	}

	info.flags = 0;
	info.low_limit = mm->mmap_base;
	info.high_limit = TASK_SIZE;
	return vm_unmapped_area(&info);
}
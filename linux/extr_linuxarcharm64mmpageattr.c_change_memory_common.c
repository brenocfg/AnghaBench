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
struct vm_struct {unsigned long size; int flags; scalar_t__ addr; } ;
typedef  int /*<<< orphan*/  pgprot_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PAGE_ALIGNED (unsigned long) ; 
 unsigned long PAGE_MASK ; 
 int PAGE_SIZE ; 
 int VM_ALLOC ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int __change_memory_common (unsigned long,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vm_struct* find_vm_area (void*) ; 

__attribute__((used)) static int change_memory_common(unsigned long addr, int numpages,
				pgprot_t set_mask, pgprot_t clear_mask)
{
	unsigned long start = addr;
	unsigned long size = PAGE_SIZE*numpages;
	unsigned long end = start + size;
	struct vm_struct *area;

	if (!PAGE_ALIGNED(addr)) {
		start &= PAGE_MASK;
		end = start + size;
		WARN_ON_ONCE(1);
	}

	/*
	 * Kernel VA mappings are always live, and splitting live section
	 * mappings into page mappings may cause TLB conflicts. This means
	 * we have to ensure that changing the permission bits of the range
	 * we are operating on does not result in such splitting.
	 *
	 * Let's restrict ourselves to mappings created by vmalloc (or vmap).
	 * Those are guaranteed to consist entirely of page mappings, and
	 * splitting is never needed.
	 *
	 * So check whether the [addr, addr + size) interval is entirely
	 * covered by precisely one VM area that has the VM_ALLOC flag set.
	 */
	area = find_vm_area((void *)addr);
	if (!area ||
	    end > (unsigned long)area->addr + area->size ||
	    !(area->flags & VM_ALLOC))
		return -EINVAL;

	if (!numpages)
		return 0;

	return __change_memory_common(start, size, set_mask, clear_mask);
}
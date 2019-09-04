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
struct vm_area_struct {int vm_flags; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int VM_EXEC ; 
 int /*<<< orphan*/  cpu_cache_wbinval_page (unsigned long,int) ; 
 scalar_t__ kmap_atomic (struct page*) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

void flush_icache_page(struct vm_area_struct *vma, struct page *page)
{
	unsigned long flags;
	unsigned long kaddr;
	local_irq_save(flags);
	kaddr = (unsigned long)kmap_atomic(page);
	cpu_cache_wbinval_page(kaddr, vma->vm_flags & VM_EXEC);
	kunmap_atomic((void *)kaddr);
	local_irq_restore(flags);
}
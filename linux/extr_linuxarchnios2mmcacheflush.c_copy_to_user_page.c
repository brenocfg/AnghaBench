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
 int /*<<< orphan*/  __flush_dcache (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  __flush_icache (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  flush_cache_page (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 int /*<<< orphan*/  page_to_pfn (struct page*) ; 

void copy_to_user_page(struct vm_area_struct *vma, struct page *page,
			unsigned long user_vaddr,
			void *dst, void *src, int len)
{
	flush_cache_page(vma, user_vaddr, page_to_pfn(page));
	memcpy(dst, src, len);
	__flush_dcache((unsigned long)dst, (unsigned long)dst + len);
	if (vma->vm_flags & VM_EXEC)
		__flush_icache((unsigned long)dst, (unsigned long)dst + len);
}
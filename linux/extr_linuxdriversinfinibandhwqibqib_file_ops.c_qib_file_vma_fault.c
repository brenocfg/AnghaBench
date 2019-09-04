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
typedef  int /*<<< orphan*/  vm_fault_t ;
struct vm_fault {int pgoff; struct page* page; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  VM_FAULT_SIGBUS ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 struct page* vmalloc_to_page (void*) ; 

__attribute__((used)) static vm_fault_t qib_file_vma_fault(struct vm_fault *vmf)
{
	struct page *page;

	page = vmalloc_to_page((void *)(vmf->pgoff << PAGE_SHIFT));
	if (!page)
		return VM_FAULT_SIGBUS;

	get_page(page);
	vmf->page = page;

	return 0;
}
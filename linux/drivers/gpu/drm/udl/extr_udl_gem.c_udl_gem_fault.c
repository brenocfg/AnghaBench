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
struct vm_fault {unsigned int address; struct vm_area_struct* vma; } ;
struct vm_area_struct {unsigned int vm_start; int /*<<< orphan*/  vm_private_data; } ;
struct udl_gem_object {struct page** pages; } ;
struct page {int dummy; } ;

/* Variables and functions */
 unsigned int PAGE_SHIFT ; 
 int /*<<< orphan*/  VM_FAULT_SIGBUS ; 
 struct udl_gem_object* to_udl_bo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmf_insert_page (struct vm_area_struct*,unsigned int,struct page*) ; 

vm_fault_t udl_gem_fault(struct vm_fault *vmf)
{
	struct vm_area_struct *vma = vmf->vma;
	struct udl_gem_object *obj = to_udl_bo(vma->vm_private_data);
	struct page *page;
	unsigned int page_offset;

	page_offset = (vmf->address - vma->vm_start) >> PAGE_SHIFT;

	if (!obj->pages)
		return VM_FAULT_SIGBUS;

	page = obj->pages[page_offset];
	return vmf_insert_page(vma, vmf->address, page);
}
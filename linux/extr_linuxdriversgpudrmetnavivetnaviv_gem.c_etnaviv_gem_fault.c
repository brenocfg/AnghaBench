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
struct vm_fault {size_t address; struct vm_area_struct* vma; } ;
struct vm_area_struct {size_t vm_start; struct drm_gem_object* vm_private_data; } ;
struct page {int dummy; } ;
struct etnaviv_gem_object {int /*<<< orphan*/  lock; } ;
struct drm_gem_object {int dummy; } ;
typedef  size_t pgoff_t ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct page**) ; 
 size_t PAGE_SHIFT ; 
 int PTR_ERR (struct page**) ; 
 int /*<<< orphan*/  VERB (char*,void*,size_t,size_t) ; 
 int /*<<< orphan*/  VM_FAULT_NOPAGE ; 
 struct page** etnaviv_gem_get_pages (struct etnaviv_gem_object*) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 size_t page_to_pfn (struct page*) ; 
 struct etnaviv_gem_object* to_etnaviv_bo (struct drm_gem_object*) ; 
 int /*<<< orphan*/  vmf_error (int) ; 
 int /*<<< orphan*/  vmf_insert_page (struct vm_area_struct*,size_t,struct page*) ; 

vm_fault_t etnaviv_gem_fault(struct vm_fault *vmf)
{
	struct vm_area_struct *vma = vmf->vma;
	struct drm_gem_object *obj = vma->vm_private_data;
	struct etnaviv_gem_object *etnaviv_obj = to_etnaviv_bo(obj);
	struct page **pages, *page;
	pgoff_t pgoff;
	int err;

	/*
	 * Make sure we don't parallel update on a fault, nor move or remove
	 * something from beneath our feet.  Note that vmf_insert_page() is
	 * specifically coded to take care of this, so we don't have to.
	 */
	err = mutex_lock_interruptible(&etnaviv_obj->lock);
	if (err)
		return VM_FAULT_NOPAGE;
	/* make sure we have pages attached now */
	pages = etnaviv_gem_get_pages(etnaviv_obj);
	mutex_unlock(&etnaviv_obj->lock);

	if (IS_ERR(pages)) {
		err = PTR_ERR(pages);
		return vmf_error(err);
	}

	/* We don't use vmf->pgoff since that has the fake offset: */
	pgoff = (vmf->address - vma->vm_start) >> PAGE_SHIFT;

	page = pages[pgoff];

	VERB("Inserting %p pfn %lx, pa %lx", (void *)vmf->address,
	     page_to_pfn(page), page_to_pfn(page) << PAGE_SHIFT);

	return vmf_insert_page(vma, vmf->address, page);
}
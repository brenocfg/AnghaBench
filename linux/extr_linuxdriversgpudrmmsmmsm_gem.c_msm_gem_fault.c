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
struct vm_fault {unsigned long address; struct vm_area_struct* vma; } ;
struct vm_area_struct {unsigned long vm_start; struct drm_gem_object* vm_private_data; } ;
struct page {int dummy; } ;
struct msm_gem_object {scalar_t__ madv; int /*<<< orphan*/  lock; } ;
struct drm_gem_object {int dummy; } ;
typedef  size_t pgoff_t ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct page**) ; 
 scalar_t__ MSM_MADV_WILLNEED ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  PFN_DEV ; 
 int /*<<< orphan*/  PTR_ERR (struct page**) ; 
 int /*<<< orphan*/  VERB (char*,void*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  VM_FAULT_NOPAGE ; 
 int /*<<< orphan*/  VM_FAULT_SIGBUS ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  __pfn_to_pfn_t (unsigned long,int /*<<< orphan*/ ) ; 
 struct page** get_pages (struct drm_gem_object*) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 unsigned long page_to_pfn (struct page*) ; 
 struct msm_gem_object* to_msm_bo (struct drm_gem_object*) ; 
 int /*<<< orphan*/  vmf_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmf_insert_mixed (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ ) ; 

vm_fault_t msm_gem_fault(struct vm_fault *vmf)
{
	struct vm_area_struct *vma = vmf->vma;
	struct drm_gem_object *obj = vma->vm_private_data;
	struct msm_gem_object *msm_obj = to_msm_bo(obj);
	struct page **pages;
	unsigned long pfn;
	pgoff_t pgoff;
	int err;
	vm_fault_t ret;

	/*
	 * vm_ops.open/drm_gem_mmap_obj and close get and put
	 * a reference on obj. So, we dont need to hold one here.
	 */
	err = mutex_lock_interruptible(&msm_obj->lock);
	if (err) {
		ret = VM_FAULT_NOPAGE;
		goto out;
	}

	if (WARN_ON(msm_obj->madv != MSM_MADV_WILLNEED)) {
		mutex_unlock(&msm_obj->lock);
		return VM_FAULT_SIGBUS;
	}

	/* make sure we have pages attached now */
	pages = get_pages(obj);
	if (IS_ERR(pages)) {
		ret = vmf_error(PTR_ERR(pages));
		goto out_unlock;
	}

	/* We don't use vmf->pgoff since that has the fake offset: */
	pgoff = (vmf->address - vma->vm_start) >> PAGE_SHIFT;

	pfn = page_to_pfn(pages[pgoff]);

	VERB("Inserting %p pfn %lx, pa %lx", (void *)vmf->address,
			pfn, pfn << PAGE_SHIFT);

	ret = vmf_insert_mixed(vma, vmf->address, __pfn_to_pfn_t(pfn, PFN_DEV));
out_unlock:
	mutex_unlock(&msm_obj->lock);
out:
	return ret;
}
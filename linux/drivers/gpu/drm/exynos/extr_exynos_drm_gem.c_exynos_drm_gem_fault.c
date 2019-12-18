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
struct exynos_drm_gem {size_t size; int /*<<< orphan*/ * pages; } ;
struct drm_gem_object {int dummy; } ;
typedef  size_t pgoff_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 size_t PAGE_SHIFT ; 
 int /*<<< orphan*/  PFN_DEV ; 
 int /*<<< orphan*/  VM_FAULT_SIGBUS ; 
 int /*<<< orphan*/  __pfn_to_pfn_t (unsigned long,int /*<<< orphan*/ ) ; 
 unsigned long page_to_pfn (int /*<<< orphan*/ ) ; 
 struct exynos_drm_gem* to_exynos_gem (struct drm_gem_object*) ; 
 int /*<<< orphan*/  vmf_insert_mixed (struct vm_area_struct*,size_t,int /*<<< orphan*/ ) ; 

vm_fault_t exynos_drm_gem_fault(struct vm_fault *vmf)
{
	struct vm_area_struct *vma = vmf->vma;
	struct drm_gem_object *obj = vma->vm_private_data;
	struct exynos_drm_gem *exynos_gem = to_exynos_gem(obj);
	unsigned long pfn;
	pgoff_t page_offset;

	page_offset = (vmf->address - vma->vm_start) >> PAGE_SHIFT;

	if (page_offset >= (exynos_gem->size >> PAGE_SHIFT)) {
		DRM_ERROR("invalid page offset\n");
		return VM_FAULT_SIGBUS;
	}

	pfn = page_to_pfn(exynos_gem->pages[page_offset]);
	return vmf_insert_mixed(vma, vmf->address,
			__pfn_to_pfn_t(pfn, PFN_DEV));
}
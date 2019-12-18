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
struct vm_fault {size_t address; } ;
struct vm_area_struct {size_t vm_start; } ;
struct omap_gem_object {size_t dma_addr; int /*<<< orphan*/ * pages; } ;
struct drm_gem_object {int dummy; } ;
typedef  size_t pgoff_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 size_t PAGE_SHIFT ; 
 int /*<<< orphan*/  PFN_DEV ; 
 int /*<<< orphan*/  VERB (char*,void*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  __pfn_to_pfn_t (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_gem_cpu_sync_page (struct drm_gem_object*,size_t) ; 
 int /*<<< orphan*/  omap_gem_is_contiguous (struct omap_gem_object*) ; 
 unsigned long page_to_pfn (int /*<<< orphan*/ ) ; 
 struct omap_gem_object* to_omap_bo (struct drm_gem_object*) ; 
 int /*<<< orphan*/  vmf_insert_mixed (struct vm_area_struct*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static vm_fault_t omap_gem_fault_1d(struct drm_gem_object *obj,
		struct vm_area_struct *vma, struct vm_fault *vmf)
{
	struct omap_gem_object *omap_obj = to_omap_bo(obj);
	unsigned long pfn;
	pgoff_t pgoff;

	/* We don't use vmf->pgoff since that has the fake offset: */
	pgoff = (vmf->address - vma->vm_start) >> PAGE_SHIFT;

	if (omap_obj->pages) {
		omap_gem_cpu_sync_page(obj, pgoff);
		pfn = page_to_pfn(omap_obj->pages[pgoff]);
	} else {
		BUG_ON(!omap_gem_is_contiguous(omap_obj));
		pfn = (omap_obj->dma_addr >> PAGE_SHIFT) + pgoff;
	}

	VERB("Inserting %p pfn %lx, pa %lx", (void *)vmf->address,
			pfn, pfn << PAGE_SHIFT);

	return vmf_insert_mixed(vma, vmf->address,
			__pfn_to_pfn_t(pfn, PFN_DEV));
}
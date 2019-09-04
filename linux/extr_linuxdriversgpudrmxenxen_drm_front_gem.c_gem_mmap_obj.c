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
struct xen_gem_object {int num_pages; int /*<<< orphan*/ * pages; } ;
struct vm_area_struct {unsigned long vm_start; int /*<<< orphan*/  vm_flags; int /*<<< orphan*/  vm_page_prot; scalar_t__ vm_pgoff; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  VM_MIXEDMAP ; 
 int /*<<< orphan*/  VM_PFNMAP ; 
 int /*<<< orphan*/  pgprot_writecombine (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_get_page_prot (int /*<<< orphan*/ ) ; 
 int vm_insert_page (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gem_mmap_obj(struct xen_gem_object *xen_obj,
			struct vm_area_struct *vma)
{
	unsigned long addr = vma->vm_start;
	int i;

	/*
	 * clear the VM_PFNMAP flag that was set by drm_gem_mmap(), and set the
	 * vm_pgoff (used as a fake buffer offset by DRM) to 0 as we want to map
	 * the whole buffer.
	 */
	vma->vm_flags &= ~VM_PFNMAP;
	vma->vm_flags |= VM_MIXEDMAP;
	vma->vm_pgoff = 0;
	vma->vm_page_prot =
			pgprot_writecombine(vm_get_page_prot(vma->vm_flags));

	/*
	 * vm_operations_struct.fault handler will be called if CPU access
	 * to VM is here. For GPUs this isn't the case, because CPU
	 * doesn't touch the memory. Insert pages now, so both CPU and GPU are
	 * happy.
	 * FIXME: as we insert all the pages now then no .fault handler must
	 * be called, so don't provide one
	 */
	for (i = 0; i < xen_obj->num_pages; i++) {
		int ret;

		ret = vm_insert_page(vma, addr, xen_obj->pages[i]);
		if (ret < 0) {
			DRM_ERROR("Failed to insert pages into vma: %d\n", ret);
			return ret;
		}

		addr += PAGE_SIZE;
	}
	return 0;
}
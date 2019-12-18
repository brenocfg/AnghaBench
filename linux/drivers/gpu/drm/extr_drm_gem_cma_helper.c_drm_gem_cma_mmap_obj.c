#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vm_area_struct {scalar_t__ vm_start; scalar_t__ vm_end; scalar_t__ vm_pgoff; int /*<<< orphan*/  vm_flags; } ;
struct TYPE_4__ {TYPE_1__* dev; } ;
struct drm_gem_cma_object {int /*<<< orphan*/  paddr; int /*<<< orphan*/  vaddr; TYPE_2__ base; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_PFNMAP ; 
 int dma_mmap_wc (int /*<<< orphan*/ ,struct vm_area_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  drm_gem_vm_close (struct vm_area_struct*) ; 

__attribute__((used)) static int drm_gem_cma_mmap_obj(struct drm_gem_cma_object *cma_obj,
				struct vm_area_struct *vma)
{
	int ret;

	/*
	 * Clear the VM_PFNMAP flag that was set by drm_gem_mmap(), and set the
	 * vm_pgoff (used as a fake buffer offset by DRM) to 0 as we want to map
	 * the whole buffer.
	 */
	vma->vm_flags &= ~VM_PFNMAP;
	vma->vm_pgoff = 0;

	ret = dma_mmap_wc(cma_obj->base.dev->dev, vma, cma_obj->vaddr,
			  cma_obj->paddr, vma->vm_end - vma->vm_start);
	if (ret)
		drm_gem_vm_close(vma);

	return ret;
}
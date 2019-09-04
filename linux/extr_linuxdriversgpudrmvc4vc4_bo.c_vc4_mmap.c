#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vm_area_struct {int vm_flags; unsigned long vm_pgoff; scalar_t__ vm_start; scalar_t__ vm_end; struct drm_gem_object* vm_private_data; } ;
struct TYPE_5__ {TYPE_1__* dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  paddr; int /*<<< orphan*/  vaddr; TYPE_2__ base; } ;
struct vc4_bo {scalar_t__ madv; TYPE_3__ base; scalar_t__ validated_shader; } ;
struct file {int dummy; } ;
struct drm_gem_object {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,...) ; 
 int EINVAL ; 
 scalar_t__ VC4_MADV_DONTNEED ; 
 scalar_t__ VC4_MADV_WILLNEED ; 
 int VM_PFNMAP ; 
 int VM_WRITE ; 
 int dma_mmap_wc (int /*<<< orphan*/ ,struct vm_area_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int drm_gem_mmap (struct file*,struct vm_area_struct*) ; 
 int /*<<< orphan*/  drm_gem_vm_close (struct vm_area_struct*) ; 
 struct vc4_bo* to_vc4_bo (struct drm_gem_object*) ; 

int vc4_mmap(struct file *filp, struct vm_area_struct *vma)
{
	struct drm_gem_object *gem_obj;
	unsigned long vm_pgoff;
	struct vc4_bo *bo;
	int ret;

	ret = drm_gem_mmap(filp, vma);
	if (ret)
		return ret;

	gem_obj = vma->vm_private_data;
	bo = to_vc4_bo(gem_obj);

	if (bo->validated_shader && (vma->vm_flags & VM_WRITE)) {
		DRM_DEBUG("mmaping of shader BOs for writing not allowed.\n");
		return -EINVAL;
	}

	if (bo->madv != VC4_MADV_WILLNEED) {
		DRM_DEBUG("mmaping of %s BO not allowed\n",
			  bo->madv == VC4_MADV_DONTNEED ?
			  "purgeable" : "purged");
		return -EINVAL;
	}

	/*
	 * Clear the VM_PFNMAP flag that was set by drm_gem_mmap(), and set the
	 * vm_pgoff (used as a fake buffer offset by DRM) to 0 as we want to map
	 * the whole buffer.
	 */
	vma->vm_flags &= ~VM_PFNMAP;

	/* This ->vm_pgoff dance is needed to make all parties happy:
	 * - dma_mmap_wc() uses ->vm_pgoff as an offset within the allocated
	 *   mem-region, hence the need to set it to zero (the value set by
	 *   the DRM core is a virtual offset encoding the GEM object-id)
	 * - the mmap() core logic needs ->vm_pgoff to be restored to its
	 *   initial value before returning from this function because it
	 *   encodes the  offset of this GEM in the dev->anon_inode pseudo-file
	 *   and this information will be used when we invalidate userspace
	 *   mappings  with drm_vma_node_unmap() (called from vc4_gem_purge()).
	 */
	vm_pgoff = vma->vm_pgoff;
	vma->vm_pgoff = 0;
	ret = dma_mmap_wc(bo->base.base.dev->dev, vma, bo->base.vaddr,
			  bo->base.paddr, vma->vm_end - vma->vm_start);
	vma->vm_pgoff = vm_pgoff;

	if (ret)
		drm_gem_vm_close(vma);

	return ret;
}
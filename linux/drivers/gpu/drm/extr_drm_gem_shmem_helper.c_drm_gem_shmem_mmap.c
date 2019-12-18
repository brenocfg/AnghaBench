#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vm_area_struct {int /*<<< orphan*/  vm_pgoff; int /*<<< orphan*/  vm_flags; int /*<<< orphan*/  vm_private_data; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  vma_node; } ;
struct drm_gem_shmem_object {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_MIXEDMAP ; 
 int /*<<< orphan*/  VM_PFNMAP ; 
 int drm_gem_mmap (struct file*,struct vm_area_struct*) ; 
 int drm_gem_shmem_get_pages (struct drm_gem_shmem_object*) ; 
 int /*<<< orphan*/  drm_gem_vm_close (struct vm_area_struct*) ; 
 scalar_t__ drm_vma_node_start (int /*<<< orphan*/ *) ; 
 struct drm_gem_shmem_object* to_drm_gem_shmem_obj (int /*<<< orphan*/ ) ; 

int drm_gem_shmem_mmap(struct file *filp, struct vm_area_struct *vma)
{
	struct drm_gem_shmem_object *shmem;
	int ret;

	ret = drm_gem_mmap(filp, vma);
	if (ret)
		return ret;

	shmem = to_drm_gem_shmem_obj(vma->vm_private_data);

	ret = drm_gem_shmem_get_pages(shmem);
	if (ret) {
		drm_gem_vm_close(vma);
		return ret;
	}

	/* VM_PFNMAP was set by drm_gem_mmap() */
	vma->vm_flags &= ~VM_PFNMAP;
	vma->vm_flags |= VM_MIXEDMAP;

	/* Remove the fake offset */
	vma->vm_pgoff -= drm_vma_node_start(&shmem->base.vma_node);

	return 0;
}
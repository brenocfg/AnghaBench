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
struct vm_area_struct {struct drm_gem_object* vm_private_data; } ;
struct file {int dummy; } ;
struct drm_gem_object {int /*<<< orphan*/  dma_buf; scalar_t__ import_attach; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int dma_buf_mmap (int /*<<< orphan*/ ,struct vm_area_struct*,int /*<<< orphan*/ ) ; 
 int drm_gem_mmap (struct file*,struct vm_area_struct*) ; 
 int exynos_drm_gem_mmap_obj (struct drm_gem_object*,struct vm_area_struct*) ; 

int exynos_drm_gem_mmap(struct file *filp, struct vm_area_struct *vma)
{
	struct drm_gem_object *obj;
	int ret;

	/* set vm_area_struct. */
	ret = drm_gem_mmap(filp, vma);
	if (ret < 0) {
		DRM_ERROR("failed to mmap.\n");
		return ret;
	}

	obj = vma->vm_private_data;

	if (obj->import_attach)
		return dma_buf_mmap(obj->dma_buf, vma, 0);

	return exynos_drm_gem_mmap_obj(obj, vma);
}
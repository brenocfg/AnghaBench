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
struct vm_area_struct {unsigned long vm_end; unsigned long vm_start; scalar_t__ vm_pgoff; int /*<<< orphan*/  vm_flags; } ;
struct TYPE_2__ {struct drm_device* dev; } ;
struct exynos_drm_gem {unsigned long size; int /*<<< orphan*/  dma_attrs; int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  cookie; TYPE_1__ base; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  VM_PFNMAP ; 
 int dma_mmap_attrs (int /*<<< orphan*/ ,struct vm_area_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_dma_dev (struct drm_device*) ; 

__attribute__((used)) static int exynos_drm_gem_mmap_buffer(struct exynos_drm_gem *exynos_gem,
				      struct vm_area_struct *vma)
{
	struct drm_device *drm_dev = exynos_gem->base.dev;
	unsigned long vm_size;
	int ret;

	vma->vm_flags &= ~VM_PFNMAP;
	vma->vm_pgoff = 0;

	vm_size = vma->vm_end - vma->vm_start;

	/* check if user-requested size is valid. */
	if (vm_size > exynos_gem->size)
		return -EINVAL;

	ret = dma_mmap_attrs(to_dma_dev(drm_dev), vma, exynos_gem->cookie,
			     exynos_gem->dma_addr, exynos_gem->size,
			     exynos_gem->dma_attrs);
	if (ret < 0) {
		DRM_ERROR("failed to mmap.\n");
		return ret;
	}

	return 0;
}
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
struct vm_area_struct {int /*<<< orphan*/  vm_flags; int /*<<< orphan*/  vm_page_prot; } ;
struct exynos_drm_gem {int flags; } ;
struct drm_gem_object {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_DEBUG_KMS (int /*<<< orphan*/ ,char*,int) ; 
 int EXYNOS_BO_CACHABLE ; 
 int EXYNOS_BO_WC ; 
 int /*<<< orphan*/  drm_gem_vm_close (struct vm_area_struct*) ; 
 int exynos_drm_gem_mmap_buffer (struct exynos_drm_gem*,struct vm_area_struct*) ; 
 int /*<<< orphan*/  pgprot_noncached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgprot_writecombine (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_dma_dev (int /*<<< orphan*/ ) ; 
 struct exynos_drm_gem* to_exynos_gem (struct drm_gem_object*) ; 
 int /*<<< orphan*/  vm_get_page_prot (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int exynos_drm_gem_mmap_obj(struct drm_gem_object *obj,
				   struct vm_area_struct *vma)
{
	struct exynos_drm_gem *exynos_gem = to_exynos_gem(obj);
	int ret;

	DRM_DEV_DEBUG_KMS(to_dma_dev(obj->dev), "flags = 0x%x\n",
			  exynos_gem->flags);

	/* non-cachable as default. */
	if (exynos_gem->flags & EXYNOS_BO_CACHABLE)
		vma->vm_page_prot = vm_get_page_prot(vma->vm_flags);
	else if (exynos_gem->flags & EXYNOS_BO_WC)
		vma->vm_page_prot =
			pgprot_writecombine(vm_get_page_prot(vma->vm_flags));
	else
		vma->vm_page_prot =
			pgprot_noncached(vm_get_page_prot(vma->vm_flags));

	ret = exynos_drm_gem_mmap_buffer(exynos_gem, vma);
	if (ret)
		goto err_close_vm;

	return ret;

err_close_vm:
	drm_gem_vm_close(vma);

	return ret;
}
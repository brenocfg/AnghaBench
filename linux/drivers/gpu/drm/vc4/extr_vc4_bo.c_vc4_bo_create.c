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
struct vc4_dev {int /*<<< orphan*/  bo_lock; TYPE_3__* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  size; } ;
struct TYPE_5__ {TYPE_1__ base; int /*<<< orphan*/  vaddr; } ;
struct vc4_bo {int /*<<< orphan*/  madv; TYPE_2__ base; } ;
struct drm_printer {int dummy; } ;
struct drm_gem_cma_object {int /*<<< orphan*/  base; } ;
struct drm_device {int dummy; } ;
typedef  enum vc4_kernel_bo_type { ____Placeholder_vc4_kernel_bo_type } vc4_kernel_bo_type ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct vc4_bo* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct drm_gem_cma_object*) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  __VC4_MADV_NOTSUPP ; 
 struct drm_gem_cma_object* drm_gem_cma_create (struct drm_device*,size_t) ; 
 struct drm_printer drm_info_printer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 size_t roundup (size_t,int /*<<< orphan*/ ) ; 
 struct vc4_bo* to_vc4_bo (int /*<<< orphan*/ *) ; 
 struct vc4_dev* to_vc4_dev (struct drm_device*) ; 
 int /*<<< orphan*/  vc4_bo_cache_purge (struct drm_device*) ; 
 struct vc4_bo* vc4_bo_get_from_cache (struct drm_device*,size_t,int) ; 
 int /*<<< orphan*/  vc4_bo_set_label (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vc4_bo_stats_print (struct drm_printer*,struct vc4_dev*) ; 
 int /*<<< orphan*/  vc4_bo_userspace_cache_purge (struct drm_device*) ; 

struct vc4_bo *vc4_bo_create(struct drm_device *dev, size_t unaligned_size,
			     bool allow_unzeroed, enum vc4_kernel_bo_type type)
{
	size_t size = roundup(unaligned_size, PAGE_SIZE);
	struct vc4_dev *vc4 = to_vc4_dev(dev);
	struct drm_gem_cma_object *cma_obj;
	struct vc4_bo *bo;

	if (size == 0)
		return ERR_PTR(-EINVAL);

	/* First, try to get a vc4_bo from the kernel BO cache. */
	bo = vc4_bo_get_from_cache(dev, size, type);
	if (bo) {
		if (!allow_unzeroed)
			memset(bo->base.vaddr, 0, bo->base.base.size);
		return bo;
	}

	cma_obj = drm_gem_cma_create(dev, size);
	if (IS_ERR(cma_obj)) {
		/*
		 * If we've run out of CMA memory, kill the cache of
		 * CMA allocations we've got laying around and try again.
		 */
		vc4_bo_cache_purge(dev);
		cma_obj = drm_gem_cma_create(dev, size);
	}

	if (IS_ERR(cma_obj)) {
		/*
		 * Still not enough CMA memory, purge the userspace BO
		 * cache and retry.
		 * This is sub-optimal since we purge the whole userspace
		 * BO cache which forces user that want to re-use the BO to
		 * restore its initial content.
		 * Ideally, we should purge entries one by one and retry
		 * after each to see if CMA allocation succeeds. Or even
		 * better, try to find an entry with at least the same
		 * size.
		 */
		vc4_bo_userspace_cache_purge(dev);
		cma_obj = drm_gem_cma_create(dev, size);
	}

	if (IS_ERR(cma_obj)) {
		struct drm_printer p = drm_info_printer(vc4->dev->dev);
		DRM_ERROR("Failed to allocate from CMA:\n");
		vc4_bo_stats_print(&p, vc4);
		return ERR_PTR(-ENOMEM);
	}
	bo = to_vc4_bo(&cma_obj->base);

	/* By default, BOs do not support the MADV ioctl. This will be enabled
	 * only on BOs that are exposed to userspace (V3D, V3D_SHADER and DUMB
	 * BOs).
	 */
	bo->madv = __VC4_MADV_NOTSUPP;

	mutex_lock(&vc4->bo_lock);
	vc4_bo_set_label(&cma_obj->base, type);
	mutex_unlock(&vc4->bo_lock);

	return bo;
}
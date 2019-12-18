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
typedef  int uint32_t ;
struct sg_table {int dummy; } ;
struct page {int dummy; } ;
struct msm_gem_object {int /*<<< orphan*/  lock; int /*<<< orphan*/  pages; struct sg_table* sgt; } ;
struct drm_gem_object {int dummy; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;
struct dma_buf {int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 struct drm_gem_object* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MSM_BO_WC ; 
 int PAGE_ALIGN (int /*<<< orphan*/ ) ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (struct drm_gem_object*) ; 
 int /*<<< orphan*/  drm_gem_private_object_init (struct drm_device*,struct drm_gem_object*,int) ; 
 int drm_prime_sg_to_page_addr_arrays (struct sg_table*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kvmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 int msm_gem_new_impl (struct drm_device*,int,int /*<<< orphan*/ ,struct drm_gem_object**,int) ; 
 int /*<<< orphan*/  msm_use_mmu (struct drm_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct msm_gem_object* to_msm_bo (struct drm_gem_object*) ; 

struct drm_gem_object *msm_gem_import(struct drm_device *dev,
		struct dma_buf *dmabuf, struct sg_table *sgt)
{
	struct msm_gem_object *msm_obj;
	struct drm_gem_object *obj;
	uint32_t size;
	int ret, npages;

	/* if we don't have IOMMU, don't bother pretending we can import: */
	if (!msm_use_mmu(dev)) {
		DRM_DEV_ERROR(dev->dev, "cannot import without IOMMU\n");
		return ERR_PTR(-EINVAL);
	}

	size = PAGE_ALIGN(dmabuf->size);

	ret = msm_gem_new_impl(dev, size, MSM_BO_WC, &obj, false);
	if (ret)
		goto fail;

	drm_gem_private_object_init(dev, obj, size);

	npages = size / PAGE_SIZE;

	msm_obj = to_msm_bo(obj);
	mutex_lock(&msm_obj->lock);
	msm_obj->sgt = sgt;
	msm_obj->pages = kvmalloc_array(npages, sizeof(struct page *), GFP_KERNEL);
	if (!msm_obj->pages) {
		mutex_unlock(&msm_obj->lock);
		ret = -ENOMEM;
		goto fail;
	}

	ret = drm_prime_sg_to_page_addr_arrays(sgt, msm_obj->pages, NULL, npages);
	if (ret) {
		mutex_unlock(&msm_obj->lock);
		goto fail;
	}

	mutex_unlock(&msm_obj->lock);
	return obj;

fail:
	drm_gem_object_put_unlocked(obj);
	return ERR_PTR(ret);
}
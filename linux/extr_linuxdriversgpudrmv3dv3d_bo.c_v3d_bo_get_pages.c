#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct drm_gem_object {int size; int /*<<< orphan*/  import_attach; struct drm_device* dev; } ;
struct v3d_bo {int /*<<< orphan*/  lock; int /*<<< orphan*/  pages_refcount; TYPE_1__* pages; TYPE_1__* sgt; struct drm_gem_object base; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;
struct TYPE_10__ {int /*<<< orphan*/  nents; int /*<<< orphan*/  sgl; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (TYPE_1__*) ; 
 int PAGE_SHIFT ; 
 int PTR_ERR (TYPE_1__*) ; 
 int /*<<< orphan*/  dma_map_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* drm_gem_get_pages (struct drm_gem_object*) ; 
 int /*<<< orphan*/  drm_gem_put_pages (struct drm_gem_object*,TYPE_1__*,int,int) ; 
 TYPE_1__* drm_prime_pages_to_sg (TYPE_1__*,int) ; 
 int /*<<< orphan*/  drm_prime_sg_to_page_addr_arrays (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 TYPE_1__* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
v3d_bo_get_pages(struct v3d_bo *bo)
{
	struct drm_gem_object *obj = &bo->base;
	struct drm_device *dev = obj->dev;
	int npages = obj->size >> PAGE_SHIFT;
	int ret = 0;

	mutex_lock(&bo->lock);
	if (bo->pages_refcount++ != 0)
		goto unlock;

	if (!obj->import_attach) {
		bo->pages = drm_gem_get_pages(obj);
		if (IS_ERR(bo->pages)) {
			ret = PTR_ERR(bo->pages);
			goto unlock;
		}

		bo->sgt = drm_prime_pages_to_sg(bo->pages, npages);
		if (IS_ERR(bo->sgt)) {
			ret = PTR_ERR(bo->sgt);
			goto put_pages;
		}

		/* Map the pages for use by the GPU. */
		dma_map_sg(dev->dev, bo->sgt->sgl,
			   bo->sgt->nents, DMA_BIDIRECTIONAL);
	} else {
		bo->pages = kcalloc(npages, sizeof(*bo->pages), GFP_KERNEL);
		if (!bo->pages)
			goto put_pages;

		drm_prime_sg_to_page_addr_arrays(bo->sgt, bo->pages,
						 NULL, npages);

		/* Note that dma-bufs come in mapped. */
	}

	mutex_unlock(&bo->lock);

	return 0;

put_pages:
	drm_gem_put_pages(obj, bo->pages, true, true);
	bo->pages = NULL;
unlock:
	bo->pages_refcount--;
	mutex_unlock(&bo->lock);
	return ret;
}
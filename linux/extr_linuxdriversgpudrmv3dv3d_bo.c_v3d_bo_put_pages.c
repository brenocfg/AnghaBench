#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct drm_gem_object {TYPE_1__* dev; int /*<<< orphan*/  import_attach; } ;
struct v3d_bo {scalar_t__ pages_refcount; int /*<<< orphan*/  lock; TYPE_2__* pages; TYPE_2__* sgt; struct drm_gem_object base; } ;
struct TYPE_6__ {int /*<<< orphan*/  nents; int /*<<< orphan*/  sgl; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_put_pages (struct drm_gem_object*,TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sg_free_table (TYPE_2__*) ; 

__attribute__((used)) static void
v3d_bo_put_pages(struct v3d_bo *bo)
{
	struct drm_gem_object *obj = &bo->base;

	mutex_lock(&bo->lock);
	if (--bo->pages_refcount == 0) {
		if (!obj->import_attach) {
			dma_unmap_sg(obj->dev->dev, bo->sgt->sgl,
				     bo->sgt->nents, DMA_BIDIRECTIONAL);
			sg_free_table(bo->sgt);
			kfree(bo->sgt);
			drm_gem_put_pages(obj, bo->pages, true, true);
		} else {
			kfree(bo->pages);
		}
	}
	mutex_unlock(&bo->lock);
}
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
struct omap_gem_object {scalar_t__ dma_addr_cnt; int flags; int /*<<< orphan*/  lock; int /*<<< orphan*/  sgt; scalar_t__ vaddr; int /*<<< orphan*/  dma_addr; struct omap_gem_object* pages; int /*<<< orphan*/  mm_list; } ;
struct omap_drm_private {int /*<<< orphan*/  list_lock; } ;
struct drm_gem_object {scalar_t__ import_attach; int /*<<< orphan*/  size; struct drm_device* dev; } ;
struct drm_device {int /*<<< orphan*/  dev; struct omap_drm_private* dev_private; } ;

/* Variables and functions */
 int OMAP_BO_MEM_DMABUF ; 
 int OMAP_BO_MEM_DMA_API ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dma_free_wc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_object_release (struct drm_gem_object*) ; 
 int /*<<< orphan*/  drm_prime_gem_destroy (struct drm_gem_object*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct omap_gem_object*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  omap_gem_detach_pages (struct drm_gem_object*) ; 
 int /*<<< orphan*/  omap_gem_evict (struct drm_gem_object*) ; 
 struct omap_gem_object* to_omap_bo (struct drm_gem_object*) ; 
 int /*<<< orphan*/  vunmap (scalar_t__) ; 

void omap_gem_free_object(struct drm_gem_object *obj)
{
	struct drm_device *dev = obj->dev;
	struct omap_drm_private *priv = dev->dev_private;
	struct omap_gem_object *omap_obj = to_omap_bo(obj);

	omap_gem_evict(obj);

	mutex_lock(&priv->list_lock);
	list_del(&omap_obj->mm_list);
	mutex_unlock(&priv->list_lock);

	/*
	 * We own the sole reference to the object at this point, but to keep
	 * lockdep happy, we must still take the omap_obj_lock to call
	 * omap_gem_detach_pages(). This should hardly make any difference as
	 * there can't be any lock contention.
	 */
	mutex_lock(&omap_obj->lock);

	/* The object should not be pinned. */
	WARN_ON(omap_obj->dma_addr_cnt > 0);

	if (omap_obj->pages) {
		if (omap_obj->flags & OMAP_BO_MEM_DMABUF)
			kfree(omap_obj->pages);
		else
			omap_gem_detach_pages(obj);
	}

	if (omap_obj->flags & OMAP_BO_MEM_DMA_API) {
		dma_free_wc(dev->dev, obj->size, omap_obj->vaddr,
			    omap_obj->dma_addr);
	} else if (omap_obj->vaddr) {
		vunmap(omap_obj->vaddr);
	} else if (obj->import_attach) {
		drm_prime_gem_destroy(obj, omap_obj->sgt);
	}

	mutex_unlock(&omap_obj->lock);

	drm_gem_object_release(obj);

	mutex_destroy(&omap_obj->lock);

	kfree(omap_obj);
}
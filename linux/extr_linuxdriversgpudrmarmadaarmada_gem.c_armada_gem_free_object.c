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
struct drm_gem_object {TYPE_1__* dev; } ;
struct armada_private {int /*<<< orphan*/  linear_lock; } ;
struct TYPE_6__ {scalar_t__ import_attach; int /*<<< orphan*/  size; } ;
struct armada_gem_object {TYPE_2__ obj; scalar_t__ sgt; scalar_t__ addr; struct armada_gem_object* linear; scalar_t__ page; } ;
struct TYPE_5__ {struct armada_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,struct armada_gem_object*) ; 
 int /*<<< orphan*/  __free_pages (scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  dma_buf_unmap_attachment (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_free_mmap_offset (TYPE_2__*) ; 
 int /*<<< orphan*/  drm_gem_object_release (TYPE_2__*) ; 
 int /*<<< orphan*/  drm_mm_remove_node (struct armada_gem_object*) ; 
 int /*<<< orphan*/  drm_prime_gem_destroy (TYPE_2__*,int /*<<< orphan*/ *) ; 
 struct armada_gem_object* drm_to_armada_gem (struct drm_gem_object*) ; 
 unsigned int get_order (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct armada_gem_object*) ; 
 int /*<<< orphan*/  might_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void armada_gem_free_object(struct drm_gem_object *obj)
{
	struct armada_gem_object *dobj = drm_to_armada_gem(obj);
	struct armada_private *priv = obj->dev->dev_private;

	DRM_DEBUG_DRIVER("release obj %p\n", dobj);

	drm_gem_free_mmap_offset(&dobj->obj);

	might_lock(&priv->linear_lock);

	if (dobj->page) {
		/* page backed memory */
		unsigned int order = get_order(dobj->obj.size);
		__free_pages(dobj->page, order);
	} else if (dobj->linear) {
		/* linear backed memory */
		mutex_lock(&priv->linear_lock);
		drm_mm_remove_node(dobj->linear);
		mutex_unlock(&priv->linear_lock);
		kfree(dobj->linear);
		if (dobj->addr)
			iounmap(dobj->addr);
	}

	if (dobj->obj.import_attach) {
		/* We only ever display imported data */
		if (dobj->sgt)
			dma_buf_unmap_attachment(dobj->obj.import_attach,
						 dobj->sgt, DMA_TO_DEVICE);
		drm_prime_gem_destroy(&dobj->obj, NULL);
	}

	drm_gem_object_release(&dobj->obj);

	kfree(dobj);
}
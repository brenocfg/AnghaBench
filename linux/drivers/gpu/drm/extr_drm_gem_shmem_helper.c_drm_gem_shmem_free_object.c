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
struct drm_gem_shmem_object {int /*<<< orphan*/  vmap_lock; int /*<<< orphan*/  pages_lock; int /*<<< orphan*/  pages_use_count; scalar_t__ pages; struct drm_gem_shmem_object* sgt; int /*<<< orphan*/  nents; int /*<<< orphan*/  sgl; int /*<<< orphan*/  vmap_use_count; } ;
struct drm_gem_object {TYPE_1__* dev; scalar_t__ import_attach; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_object_release (struct drm_gem_object*) ; 
 int /*<<< orphan*/  drm_gem_shmem_put_pages (struct drm_gem_shmem_object*) ; 
 int /*<<< orphan*/  drm_prime_gem_destroy (struct drm_gem_object*,struct drm_gem_shmem_object*) ; 
 int /*<<< orphan*/  kfree (struct drm_gem_shmem_object*) ; 
 int /*<<< orphan*/  kvfree (scalar_t__) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sg_free_table (struct drm_gem_shmem_object*) ; 
 struct drm_gem_shmem_object* to_drm_gem_shmem_obj (struct drm_gem_object*) ; 

void drm_gem_shmem_free_object(struct drm_gem_object *obj)
{
	struct drm_gem_shmem_object *shmem = to_drm_gem_shmem_obj(obj);

	WARN_ON(shmem->vmap_use_count);

	if (obj->import_attach) {
		shmem->pages_use_count--;
		drm_prime_gem_destroy(obj, shmem->sgt);
		kvfree(shmem->pages);
	} else {
		if (shmem->sgt) {
			dma_unmap_sg(obj->dev->dev, shmem->sgt->sgl,
				     shmem->sgt->nents, DMA_BIDIRECTIONAL);
			sg_free_table(shmem->sgt);
			kfree(shmem->sgt);
		}
		if (shmem->pages)
			drm_gem_shmem_put_pages(shmem);
	}

	WARN_ON(shmem->pages_use_count);

	drm_gem_object_release(obj);
	mutex_destroy(&shmem->pages_lock);
	mutex_destroy(&shmem->vmap_lock);
	kfree(shmem);
}
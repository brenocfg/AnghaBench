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
struct TYPE_2__ {int pages_allocated; int /*<<< orphan*/  num_allocated; } ;
struct v3d_dev {int /*<<< orphan*/  mm_lock; int /*<<< orphan*/  bo_lock; TYPE_1__ bo_stats; } ;
struct v3d_bo {int /*<<< orphan*/  lock; int /*<<< orphan*/  node; int /*<<< orphan*/  sgt; int /*<<< orphan*/  _resv; } ;
struct drm_gem_object {int size; scalar_t__ import_attach; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  drm_gem_object_release (struct drm_gem_object*) ; 
 int /*<<< orphan*/  drm_mm_remove_node (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_prime_gem_destroy (struct drm_gem_object*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct v3d_bo*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reservation_object_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct v3d_bo* to_v3d_bo (struct drm_gem_object*) ; 
 struct v3d_dev* to_v3d_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v3d_bo_put_pages (struct v3d_bo*) ; 
 int /*<<< orphan*/  v3d_mmu_remove_ptes (struct v3d_bo*) ; 

void v3d_free_object(struct drm_gem_object *obj)
{
	struct v3d_dev *v3d = to_v3d_dev(obj->dev);
	struct v3d_bo *bo = to_v3d_bo(obj);

	mutex_lock(&v3d->bo_lock);
	v3d->bo_stats.num_allocated--;
	v3d->bo_stats.pages_allocated -= obj->size >> PAGE_SHIFT;
	mutex_unlock(&v3d->bo_lock);

	reservation_object_fini(&bo->_resv);

	v3d_bo_put_pages(bo);

	if (obj->import_attach)
		drm_prime_gem_destroy(obj, bo->sgt);

	v3d_mmu_remove_ptes(bo);
	spin_lock(&v3d->mm_lock);
	drm_mm_remove_node(&bo->node);
	spin_unlock(&v3d->mm_lock);

	mutex_destroy(&bo->lock);

	drm_gem_object_release(obj);
	kfree(bo);
}
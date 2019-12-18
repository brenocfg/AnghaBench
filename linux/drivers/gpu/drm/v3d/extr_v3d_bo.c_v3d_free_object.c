#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int pages_allocated; int /*<<< orphan*/  num_allocated; } ;
struct v3d_dev {int /*<<< orphan*/  mm_lock; int /*<<< orphan*/  bo_lock; TYPE_1__ bo_stats; } ;
struct TYPE_4__ {int pages_mark_dirty_on_put; } ;
struct v3d_bo {TYPE_2__ base; int /*<<< orphan*/  node; } ;
struct drm_gem_object {int size; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  drm_gem_shmem_free_object (struct drm_gem_object*) ; 
 int /*<<< orphan*/  drm_mm_remove_node (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct v3d_bo* to_v3d_bo (struct drm_gem_object*) ; 
 struct v3d_dev* to_v3d_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v3d_mmu_remove_ptes (struct v3d_bo*) ; 

void v3d_free_object(struct drm_gem_object *obj)
{
	struct v3d_dev *v3d = to_v3d_dev(obj->dev);
	struct v3d_bo *bo = to_v3d_bo(obj);

	v3d_mmu_remove_ptes(bo);

	mutex_lock(&v3d->bo_lock);
	v3d->bo_stats.num_allocated--;
	v3d->bo_stats.pages_allocated -= obj->size >> PAGE_SHIFT;
	mutex_unlock(&v3d->bo_lock);

	spin_lock(&v3d->mm_lock);
	drm_mm_remove_node(&bo->node);
	spin_unlock(&v3d->mm_lock);

	/* GPU execution may have dirtied any pages in the BO. */
	bo->base.pages_mark_dirty_on_put = true;

	drm_gem_shmem_free_object(obj);
}
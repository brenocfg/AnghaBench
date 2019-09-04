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
struct drm_gem_object {int size; } ;
struct v3d_bo {int /*<<< orphan*/  node; int /*<<< orphan*/ * resv; int /*<<< orphan*/  _resv; struct drm_gem_object base; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 struct v3d_bo* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct v3d_bo*) ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  drm_gem_object_release (struct drm_gem_object*) ; 
 int /*<<< orphan*/  drm_mm_remove_node (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct v3d_bo*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reservation_object_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct v3d_dev* to_v3d_dev (struct drm_device*) ; 
 struct v3d_bo* v3d_bo_create_struct (struct drm_device*,size_t) ; 
 int v3d_bo_get_pages (struct v3d_bo*) ; 
 int /*<<< orphan*/  v3d_mmu_insert_ptes (struct v3d_bo*) ; 

struct v3d_bo *v3d_bo_create(struct drm_device *dev, struct drm_file *file_priv,
			     size_t unaligned_size)
{
	struct v3d_dev *v3d = to_v3d_dev(dev);
	struct drm_gem_object *obj;
	struct v3d_bo *bo;
	int ret;

	bo = v3d_bo_create_struct(dev, unaligned_size);
	if (IS_ERR(bo))
		return bo;
	obj = &bo->base;

	bo->resv = &bo->_resv;
	reservation_object_init(bo->resv);

	ret = v3d_bo_get_pages(bo);
	if (ret)
		goto free_mm;

	v3d_mmu_insert_ptes(bo);

	mutex_lock(&v3d->bo_lock);
	v3d->bo_stats.num_allocated++;
	v3d->bo_stats.pages_allocated += obj->size >> PAGE_SHIFT;
	mutex_unlock(&v3d->bo_lock);

	return bo;

free_mm:
	spin_lock(&v3d->mm_lock);
	drm_mm_remove_node(&bo->node);
	spin_unlock(&v3d->mm_lock);

	drm_gem_object_release(obj);
	kfree(bo);
	return ERR_PTR(ret);
}
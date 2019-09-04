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
struct list_head {int dummy; } ;
struct TYPE_4__ {struct list_head time_list; } ;
struct vc4_dev {int /*<<< orphan*/  bo_lock; TYPE_1__ bo_cache; } ;
struct TYPE_5__ {int /*<<< orphan*/  base; int /*<<< orphan*/  vaddr; } ;
struct vc4_bo {scalar_t__ madv; int t_format; TYPE_2__ base; int /*<<< orphan*/  unref_head; int /*<<< orphan*/  size_head; int /*<<< orphan*/  free_time; int /*<<< orphan*/  usecnt; TYPE_3__* validated_shader; int /*<<< orphan*/  madv_lock; } ;
struct drm_gem_object {int /*<<< orphan*/  size; scalar_t__ name; scalar_t__ import_attach; struct drm_device* dev; } ;
struct drm_device {int dummy; } ;
struct TYPE_6__ {struct TYPE_6__* texture_samples; struct TYPE_6__* uniform_addr_offsets; } ;

/* Variables and functions */
 int /*<<< orphan*/  VC4_BO_TYPE_KERNEL_CACHE ; 
 scalar_t__ VC4_MADV_DONTNEED ; 
 scalar_t__ __VC4_MADV_NOTSUPP ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  kfree (TYPE_3__*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct vc4_bo* to_vc4_bo (struct drm_gem_object*) ; 
 struct vc4_dev* to_vc4_dev (struct drm_device*) ; 
 int /*<<< orphan*/  vc4_bo_cache_free_old (struct drm_device*) ; 
 int /*<<< orphan*/  vc4_bo_destroy (struct vc4_bo*) ; 
 int /*<<< orphan*/  vc4_bo_remove_from_purgeable_pool (struct vc4_bo*) ; 
 int /*<<< orphan*/  vc4_bo_set_label (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct list_head* vc4_get_cache_list_for_size (struct drm_device*,int /*<<< orphan*/ ) ; 

void vc4_free_object(struct drm_gem_object *gem_bo)
{
	struct drm_device *dev = gem_bo->dev;
	struct vc4_dev *vc4 = to_vc4_dev(dev);
	struct vc4_bo *bo = to_vc4_bo(gem_bo);
	struct list_head *cache_list;

	/* Remove the BO from the purgeable list. */
	mutex_lock(&bo->madv_lock);
	if (bo->madv == VC4_MADV_DONTNEED && !refcount_read(&bo->usecnt))
		vc4_bo_remove_from_purgeable_pool(bo);
	mutex_unlock(&bo->madv_lock);

	mutex_lock(&vc4->bo_lock);
	/* If the object references someone else's memory, we can't cache it.
	 */
	if (gem_bo->import_attach) {
		vc4_bo_destroy(bo);
		goto out;
	}

	/* Don't cache if it was publicly named. */
	if (gem_bo->name) {
		vc4_bo_destroy(bo);
		goto out;
	}

	/* If this object was partially constructed but CMA allocation
	 * had failed, just free it. Can also happen when the BO has been
	 * purged.
	 */
	if (!bo->base.vaddr) {
		vc4_bo_destroy(bo);
		goto out;
	}

	cache_list = vc4_get_cache_list_for_size(dev, gem_bo->size);
	if (!cache_list) {
		vc4_bo_destroy(bo);
		goto out;
	}

	if (bo->validated_shader) {
		kfree(bo->validated_shader->uniform_addr_offsets);
		kfree(bo->validated_shader->texture_samples);
		kfree(bo->validated_shader);
		bo->validated_shader = NULL;
	}

	/* Reset madv and usecnt before adding the BO to the cache. */
	bo->madv = __VC4_MADV_NOTSUPP;
	refcount_set(&bo->usecnt, 0);

	bo->t_format = false;
	bo->free_time = jiffies;
	list_add(&bo->size_head, cache_list);
	list_add(&bo->unref_head, &vc4->bo_cache.time_list);

	vc4_bo_set_label(&bo->base.base, VC4_BO_TYPE_KERNEL_CACHE);

	vc4_bo_cache_free_old(dev);

out:
	mutex_unlock(&vc4->bo_lock);
}
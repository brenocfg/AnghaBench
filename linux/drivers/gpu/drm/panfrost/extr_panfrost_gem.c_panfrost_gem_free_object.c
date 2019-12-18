#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int size; } ;
struct TYPE_8__ {int /*<<< orphan*/  madv_list; TYPE_2__ base; } ;
struct panfrost_gem_object {TYPE_3__ base; TYPE_4__* sgts; } ;
struct panfrost_device {int /*<<< orphan*/  shrinker_lock; int /*<<< orphan*/  dev; } ;
struct drm_gem_object {TYPE_1__* dev; } ;
struct TYPE_9__ {int /*<<< orphan*/  nents; scalar_t__ sgl; } ;
struct TYPE_6__ {struct panfrost_device* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int SZ_2M ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_shmem_free_object (struct drm_gem_object*) ; 
 int /*<<< orphan*/  kfree (TYPE_4__*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sg_free_table (TYPE_4__*) ; 
 struct panfrost_gem_object* to_panfrost_bo (struct drm_gem_object*) ; 

__attribute__((used)) static void panfrost_gem_free_object(struct drm_gem_object *obj)
{
	struct panfrost_gem_object *bo = to_panfrost_bo(obj);
	struct panfrost_device *pfdev = obj->dev->dev_private;

	if (bo->sgts) {
		int i;
		int n_sgt = bo->base.base.size / SZ_2M;

		for (i = 0; i < n_sgt; i++) {
			if (bo->sgts[i].sgl) {
				dma_unmap_sg(pfdev->dev, bo->sgts[i].sgl,
					     bo->sgts[i].nents, DMA_BIDIRECTIONAL);
				sg_free_table(&bo->sgts[i]);
			}
		}
		kfree(bo->sgts);
	}

	mutex_lock(&pfdev->shrinker_lock);
	if (!list_empty(&bo->base.madv_list))
		list_del(&bo->base.madv_list);
	mutex_unlock(&pfdev->shrinker_lock);

	drm_gem_shmem_free_object(obj);
}
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
struct TYPE_4__ {int pages_allocated; int /*<<< orphan*/  num_allocated; } ;
struct v3d_dev {int /*<<< orphan*/  bo_lock; TYPE_2__ bo_stats; int /*<<< orphan*/  mm_lock; int /*<<< orphan*/  mm; } ;
struct TYPE_3__ {int /*<<< orphan*/  base; } ;
struct v3d_bo {int /*<<< orphan*/  node; TYPE_1__ base; } ;
struct sg_table {int dummy; } ;
struct drm_gem_object {int size; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int GMP_GRANULARITY ; 
 scalar_t__ IS_ERR (struct sg_table*) ; 
 int PAGE_SHIFT ; 
 int PTR_ERR (struct sg_table*) ; 
 struct sg_table* drm_gem_shmem_get_pages_sgt (int /*<<< orphan*/ *) ; 
 int drm_mm_insert_node_generic (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct v3d_bo* to_v3d_bo (struct drm_gem_object*) ; 
 struct v3d_dev* to_v3d_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v3d_mmu_insert_ptes (struct v3d_bo*) ; 

__attribute__((used)) static int
v3d_bo_create_finish(struct drm_gem_object *obj)
{
	struct v3d_dev *v3d = to_v3d_dev(obj->dev);
	struct v3d_bo *bo = to_v3d_bo(obj);
	struct sg_table *sgt;
	int ret;

	/* So far we pin the BO in the MMU for its lifetime, so use
	 * shmem's helper for getting a lifetime sgt.
	 */
	sgt = drm_gem_shmem_get_pages_sgt(&bo->base.base);
	if (IS_ERR(sgt))
		return PTR_ERR(sgt);

	spin_lock(&v3d->mm_lock);
	/* Allocate the object's space in the GPU's page tables.
	 * Inserting PTEs will happen later, but the offset is for the
	 * lifetime of the BO.
	 */
	ret = drm_mm_insert_node_generic(&v3d->mm, &bo->node,
					 obj->size >> PAGE_SHIFT,
					 GMP_GRANULARITY >> PAGE_SHIFT, 0, 0);
	spin_unlock(&v3d->mm_lock);
	if (ret)
		return ret;

	/* Track stats for /debug/dri/n/bo_stats. */
	mutex_lock(&v3d->bo_lock);
	v3d->bo_stats.num_allocated++;
	v3d->bo_stats.pages_allocated += obj->size >> PAGE_SHIFT;
	mutex_unlock(&v3d->bo_lock);

	v3d_mmu_insert_ptes(bo);

	return 0;
}
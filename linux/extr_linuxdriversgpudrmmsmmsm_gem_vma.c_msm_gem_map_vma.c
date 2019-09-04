#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sg_table {int dummy; } ;
struct TYPE_7__ {int start; } ;
struct msm_gem_vma {int iova; TYPE_3__ node; } ;
struct msm_gem_address_space {int /*<<< orphan*/  kref; TYPE_2__* mmu; int /*<<< orphan*/  lock; int /*<<< orphan*/  mm; } ;
struct TYPE_6__ {TYPE_1__* funcs; } ;
struct TYPE_5__ {int (* map ) (TYPE_2__*,int,struct sg_table*,unsigned int,int) ;} ;

/* Variables and functions */
 int IOMMU_READ ; 
 int IOMMU_WRITE ; 
 int PAGE_SHIFT ; 
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 int drm_mm_insert_node (int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 int /*<<< orphan*/  drm_mm_node_allocated (TYPE_3__*) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (TYPE_2__*,int,struct sg_table*,unsigned int,int) ; 

int
msm_gem_map_vma(struct msm_gem_address_space *aspace,
		struct msm_gem_vma *vma, struct sg_table *sgt, int npages)
{
	int ret;

	spin_lock(&aspace->lock);
	if (WARN_ON(drm_mm_node_allocated(&vma->node))) {
		spin_unlock(&aspace->lock);
		return 0;
	}

	ret = drm_mm_insert_node(&aspace->mm, &vma->node, npages);
	spin_unlock(&aspace->lock);

	if (ret)
		return ret;

	vma->iova = vma->node.start << PAGE_SHIFT;

	if (aspace->mmu) {
		unsigned size = npages << PAGE_SHIFT;
		ret = aspace->mmu->funcs->map(aspace->mmu, vma->iova, sgt,
				size, IOMMU_READ | IOMMU_WRITE);
	}

	/* Get a reference to the aspace to keep it around */
	kref_get(&aspace->kref);

	return ret;
}
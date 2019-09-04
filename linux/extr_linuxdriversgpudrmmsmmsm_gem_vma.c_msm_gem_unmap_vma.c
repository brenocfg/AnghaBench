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
struct sg_table {int dummy; } ;
struct TYPE_6__ {unsigned int size; } ;
struct msm_gem_vma {scalar_t__ iova; TYPE_3__ node; } ;
struct msm_gem_address_space {int /*<<< orphan*/  lock; TYPE_2__* mmu; } ;
struct TYPE_5__ {TYPE_1__* funcs; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* unmap ) (TYPE_2__*,scalar_t__,struct sg_table*,unsigned int) ;} ;

/* Variables and functions */
 unsigned int PAGE_SHIFT ; 
 int /*<<< orphan*/  drm_mm_remove_node (TYPE_3__*) ; 
 int /*<<< orphan*/  msm_gem_address_space_put (struct msm_gem_address_space*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,scalar_t__,struct sg_table*,unsigned int) ; 

void
msm_gem_unmap_vma(struct msm_gem_address_space *aspace,
		struct msm_gem_vma *vma, struct sg_table *sgt)
{
	if (!aspace || !vma->iova)
		return;

	if (aspace->mmu) {
		unsigned size = vma->node.size << PAGE_SHIFT;
		aspace->mmu->funcs->unmap(aspace->mmu, vma->iova, sgt, size);
	}

	spin_lock(&aspace->lock);
	drm_mm_remove_node(&vma->node);
	spin_unlock(&aspace->lock);

	vma->iova = 0;

	msm_gem_address_space_put(aspace);
}
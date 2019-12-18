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
struct TYPE_2__ {int start; } ;
struct msm_gem_vma {int iova; int mapped; TYPE_1__ node; } ;
struct msm_gem_address_space {int /*<<< orphan*/  kref; int /*<<< orphan*/  lock; int /*<<< orphan*/  mm; } ;

/* Variables and functions */
 int EBUSY ; 
 int PAGE_SHIFT ; 
 scalar_t__ WARN_ON (int) ; 
 int drm_mm_insert_node (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int msm_gem_init_vma(struct msm_gem_address_space *aspace,
		struct msm_gem_vma *vma, int npages)
{
	int ret;

	if (WARN_ON(vma->iova))
		return -EBUSY;

	spin_lock(&aspace->lock);
	ret = drm_mm_insert_node(&aspace->mm, &vma->node, npages);
	spin_unlock(&aspace->lock);

	if (ret)
		return ret;

	vma->iova = vma->node.start << PAGE_SHIFT;
	vma->mapped = false;

	kref_get(&aspace->kref);

	return 0;
}
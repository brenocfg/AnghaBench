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
struct sg_table {int dummy; } ;
struct msm_gem_vma {int mapped; int /*<<< orphan*/  iova; int /*<<< orphan*/  inuse; } ;
struct msm_gem_address_space {TYPE_2__* mmu; } ;
struct TYPE_4__ {TYPE_1__* funcs; } ;
struct TYPE_3__ {int (* map ) (TYPE_2__*,int /*<<< orphan*/ ,struct sg_table*,unsigned int,int) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int PAGE_SHIFT ; 
 scalar_t__ WARN_ON (int) ; 
 int stub1 (TYPE_2__*,int /*<<< orphan*/ ,struct sg_table*,unsigned int,int) ; 

int
msm_gem_map_vma(struct msm_gem_address_space *aspace,
		struct msm_gem_vma *vma, int prot,
		struct sg_table *sgt, int npages)
{
	unsigned size = npages << PAGE_SHIFT;
	int ret = 0;

	if (WARN_ON(!vma->iova))
		return -EINVAL;

	/* Increase the usage counter */
	vma->inuse++;

	if (vma->mapped)
		return 0;

	vma->mapped = true;

	if (aspace && aspace->mmu)
		ret = aspace->mmu->funcs->map(aspace->mmu, vma->iova, sgt,
				size, prot);

	if (ret)
		vma->mapped = false;

	return ret;
}
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
struct TYPE_4__ {unsigned int size; } ;
struct msm_gem_vma {scalar_t__ inuse; int mapped; int /*<<< orphan*/  iova; TYPE_1__ node; } ;
struct msm_gem_address_space {TYPE_3__* mmu; } ;
struct TYPE_6__ {TYPE_2__* funcs; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* unmap ) (TYPE_3__*,int /*<<< orphan*/ ,unsigned int) ;} ;

/* Variables and functions */
 unsigned int PAGE_SHIFT ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ ,unsigned int) ; 

void msm_gem_purge_vma(struct msm_gem_address_space *aspace,
		struct msm_gem_vma *vma)
{
	unsigned size = vma->node.size << PAGE_SHIFT;

	/* Print a message if we try to purge a vma in use */
	if (WARN_ON(vma->inuse > 0))
		return;

	/* Don't do anything if the memory isn't mapped */
	if (!vma->mapped)
		return;

	if (aspace->mmu)
		aspace->mmu->funcs->unmap(aspace->mmu, vma->iova, size);

	vma->mapped = false;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct msm_gem_vma {scalar_t__ inuse; scalar_t__ iova; int /*<<< orphan*/  node; scalar_t__ mapped; } ;
struct msm_gem_address_space {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  drm_mm_remove_node (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msm_gem_address_space_put (struct msm_gem_address_space*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void msm_gem_close_vma(struct msm_gem_address_space *aspace,
		struct msm_gem_vma *vma)
{
	if (WARN_ON(vma->inuse > 0 || vma->mapped))
		return;

	spin_lock(&aspace->lock);
	if (vma->iova)
		drm_mm_remove_node(&vma->node);
	spin_unlock(&aspace->lock);

	vma->iova = 0;

	msm_gem_address_space_put(aspace);
}
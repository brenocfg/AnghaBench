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
typedef  size_t uint32_t ;
struct dma_fence {size_t context; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct amdgpu_sa_manager {TYPE_1__ wq; int /*<<< orphan*/ * flist; } ;
struct amdgpu_sa_bo {int /*<<< orphan*/  flist; int /*<<< orphan*/  fence; struct amdgpu_sa_manager* manager; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 size_t AMDGPU_SA_NUM_FENCE_LISTS ; 
 int /*<<< orphan*/  amdgpu_sa_bo_remove_locked (struct amdgpu_sa_bo*) ; 
 int /*<<< orphan*/  dma_fence_get (struct dma_fence*) ; 
 int /*<<< orphan*/  dma_fence_is_signaled (struct dma_fence*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_all_locked (TYPE_1__*) ; 

void amdgpu_sa_bo_free(struct amdgpu_device *adev, struct amdgpu_sa_bo **sa_bo,
		       struct dma_fence *fence)
{
	struct amdgpu_sa_manager *sa_manager;

	if (sa_bo == NULL || *sa_bo == NULL) {
		return;
	}

	sa_manager = (*sa_bo)->manager;
	spin_lock(&sa_manager->wq.lock);
	if (fence && !dma_fence_is_signaled(fence)) {
		uint32_t idx;

		(*sa_bo)->fence = dma_fence_get(fence);
		idx = fence->context % AMDGPU_SA_NUM_FENCE_LISTS;
		list_add_tail(&(*sa_bo)->flist, &sa_manager->flist[idx]);
	} else {
		amdgpu_sa_bo_remove_locked(*sa_bo);
	}
	wake_up_all_locked(&sa_manager->wq);
	spin_unlock(&sa_manager->wq.lock);
	*sa_bo = NULL;
}
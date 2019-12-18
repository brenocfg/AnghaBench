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
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct radeon_sa_manager {TYPE_1__ wq; int /*<<< orphan*/ * flist; } ;
struct radeon_sa_bo {int /*<<< orphan*/  flist; int /*<<< orphan*/  fence; struct radeon_sa_manager* manager; } ;
struct radeon_fence {size_t ring; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radeon_fence_ref (struct radeon_fence*) ; 
 int /*<<< orphan*/  radeon_fence_signaled (struct radeon_fence*) ; 
 int /*<<< orphan*/  radeon_sa_bo_remove_locked (struct radeon_sa_bo*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_all_locked (TYPE_1__*) ; 

void radeon_sa_bo_free(struct radeon_device *rdev, struct radeon_sa_bo **sa_bo,
		       struct radeon_fence *fence)
{
	struct radeon_sa_manager *sa_manager;

	if (sa_bo == NULL || *sa_bo == NULL) {
		return;
	}

	sa_manager = (*sa_bo)->manager;
	spin_lock(&sa_manager->wq.lock);
	if (fence && !radeon_fence_signaled(fence)) {
		(*sa_bo)->fence = radeon_fence_ref(fence);
		list_add_tail(&(*sa_bo)->flist,
			      &sa_manager->flist[fence->ring]);
	} else {
		radeon_sa_bo_remove_locked(*sa_bo);
	}
	wake_up_all_locked(&sa_manager->wq);
	spin_unlock(&sa_manager->wq.lock);
	*sa_bo = NULL;
}
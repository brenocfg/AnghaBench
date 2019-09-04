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
struct amdgpu_ring {int priority; int /*<<< orphan*/  priority_mutex; TYPE_1__* funcs; int /*<<< orphan*/ * num_jobs; } ;
typedef  enum drm_sched_priority { ____Placeholder_drm_sched_priority } drm_sched_priority ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_priority ) (struct amdgpu_ring*,int) ;} ;

/* Variables and functions */
 int DRM_SCHED_PRIORITY_MIN ; 
 int DRM_SCHED_PRIORITY_NORMAL ; 
 scalar_t__ atomic_dec_return (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct amdgpu_ring*,int) ; 

void amdgpu_ring_priority_put(struct amdgpu_ring *ring,
			      enum drm_sched_priority priority)
{
	int i;

	if (!ring->funcs->set_priority)
		return;

	if (atomic_dec_return(&ring->num_jobs[priority]) > 0)
		return;

	/* no need to restore if the job is already at the lowest priority */
	if (priority == DRM_SCHED_PRIORITY_NORMAL)
		return;

	mutex_lock(&ring->priority_mutex);
	/* something higher prio is executing, no need to decay */
	if (ring->priority > priority)
		goto out_unlock;

	/* decay priority to the next level with a job available */
	for (i = priority; i >= DRM_SCHED_PRIORITY_MIN; i--) {
		if (i == DRM_SCHED_PRIORITY_NORMAL
				|| atomic_read(&ring->num_jobs[i])) {
			ring->priority = i;
			ring->funcs->set_priority(ring, i);
			break;
		}
	}

out_unlock:
	mutex_unlock(&ring->priority_mutex);
}
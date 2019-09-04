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
 scalar_t__ atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct amdgpu_ring*,int) ; 

void amdgpu_ring_priority_get(struct amdgpu_ring *ring,
			      enum drm_sched_priority priority)
{
	if (!ring->funcs->set_priority)
		return;

	if (atomic_inc_return(&ring->num_jobs[priority]) <= 0)
		return;

	mutex_lock(&ring->priority_mutex);
	if (priority <= ring->priority)
		goto out_unlock;

	ring->priority = priority;
	ring->funcs->set_priority(ring, priority);

out_unlock:
	mutex_unlock(&ring->priority_mutex);
}
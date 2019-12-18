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
struct v3d_dev {int /*<<< orphan*/  reset_lock; TYPE_1__* queue; } ;
struct drm_sched_job {int dummy; } ;
typedef  enum v3d_queue { ____Placeholder_v3d_queue } v3d_queue ;
struct TYPE_2__ {int /*<<< orphan*/  sched; } ;

/* Variables and functions */
 int V3D_MAX_QUEUES ; 
 int /*<<< orphan*/  drm_sched_increase_karma (struct drm_sched_job*) ; 
 int /*<<< orphan*/  drm_sched_resubmit_jobs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_sched_start (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  drm_sched_stop (int /*<<< orphan*/ *,struct drm_sched_job*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v3d_reset (struct v3d_dev*) ; 

__attribute__((used)) static void
v3d_gpu_reset_for_timeout(struct v3d_dev *v3d, struct drm_sched_job *sched_job)
{
	enum v3d_queue q;

	mutex_lock(&v3d->reset_lock);

	/* block scheduler */
	for (q = 0; q < V3D_MAX_QUEUES; q++)
		drm_sched_stop(&v3d->queue[q].sched, sched_job);

	if (sched_job)
		drm_sched_increase_karma(sched_job);

	/* get the GPU back into the init state */
	v3d_reset(v3d);

	for (q = 0; q < V3D_MAX_QUEUES; q++)
		drm_sched_resubmit_jobs(&v3d->queue[q].sched);

	/* Unblock schedulers and restart their jobs. */
	for (q = 0; q < V3D_MAX_QUEUES; q++) {
		drm_sched_start(&v3d->queue[q].sched, true);
	}

	mutex_unlock(&v3d->reset_lock);
}
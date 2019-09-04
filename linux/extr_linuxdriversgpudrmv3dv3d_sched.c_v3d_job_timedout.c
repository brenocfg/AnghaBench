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
typedef  scalar_t__ u32 ;
struct TYPE_5__ {TYPE_1__* sched; int /*<<< orphan*/  work_tdr; } ;
struct v3d_job {scalar_t__ timedout_ctca; scalar_t__ timedout_ctra; TYPE_2__ base; struct v3d_exec_info* exec; } ;
struct v3d_exec_info {struct v3d_job bin; struct v3d_dev* v3d; } ;
struct v3d_dev {int /*<<< orphan*/  reset_lock; TYPE_3__* queue; } ;
struct drm_sched_job {struct drm_gpu_scheduler* sched; } ;
struct drm_gpu_scheduler {int /*<<< orphan*/  thread; } ;
typedef  enum v3d_queue { ____Placeholder_v3d_queue } v3d_queue ;
struct TYPE_6__ {struct drm_gpu_scheduler sched; } ;
struct TYPE_4__ {int /*<<< orphan*/  timeout; } ;

/* Variables and functions */
 int V3D_BIN ; 
 int /*<<< orphan*/  V3D_CLE_CTNCA (int) ; 
 int /*<<< orphan*/  V3D_CLE_CTNRA (int) ; 
 scalar_t__ V3D_CORE_READ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int V3D_MAX_QUEUES ; 
 int V3D_RENDER ; 
 int /*<<< orphan*/  drm_sched_hw_job_reset (struct drm_gpu_scheduler*,struct drm_sched_job*) ; 
 int /*<<< orphan*/  drm_sched_job_recovery (struct drm_gpu_scheduler*) ; 
 int /*<<< orphan*/  kthread_park (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_unpark (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct v3d_job* to_v3d_job (struct drm_sched_job*) ; 
 int /*<<< orphan*/  v3d_reset (struct v3d_dev*) ; 

__attribute__((used)) static void
v3d_job_timedout(struct drm_sched_job *sched_job)
{
	struct v3d_job *job = to_v3d_job(sched_job);
	struct v3d_exec_info *exec = job->exec;
	struct v3d_dev *v3d = exec->v3d;
	enum v3d_queue job_q = job == &exec->bin ? V3D_BIN : V3D_RENDER;
	enum v3d_queue q;
	u32 ctca = V3D_CORE_READ(0, V3D_CLE_CTNCA(job_q));
	u32 ctra = V3D_CORE_READ(0, V3D_CLE_CTNRA(job_q));

	/* If the current address or return address have changed, then
	 * the GPU has probably made progress and we should delay the
	 * reset.  This could fail if the GPU got in an infinite loop
	 * in the CL, but that is pretty unlikely outside of an i-g-t
	 * testcase.
	 */
	if (job->timedout_ctca != ctca || job->timedout_ctra != ctra) {
		job->timedout_ctca = ctca;
		job->timedout_ctra = ctra;

		schedule_delayed_work(&job->base.work_tdr,
				      job->base.sched->timeout);
		return;
	}

	mutex_lock(&v3d->reset_lock);

	/* block scheduler */
	for (q = 0; q < V3D_MAX_QUEUES; q++) {
		struct drm_gpu_scheduler *sched = &v3d->queue[q].sched;

		kthread_park(sched->thread);
		drm_sched_hw_job_reset(sched, (sched_job->sched == sched ?
					       sched_job : NULL));
	}

	/* get the GPU back into the init state */
	v3d_reset(v3d);

	/* Unblock schedulers and restart their jobs. */
	for (q = 0; q < V3D_MAX_QUEUES; q++) {
		drm_sched_job_recovery(&v3d->queue[q].sched);
		kthread_unpark(v3d->queue[q].sched.thread);
	}

	mutex_unlock(&v3d->reset_lock);
}
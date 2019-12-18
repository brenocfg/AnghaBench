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
struct drm_sched_backend_ops {int dummy; } ;
struct drm_gpu_scheduler {unsigned int hw_submission_limit; char const* name; long timeout; unsigned int hang_limit; int ready; int /*<<< orphan*/ * thread; int /*<<< orphan*/  job_id_count; int /*<<< orphan*/  num_jobs; int /*<<< orphan*/  work_tdr; int /*<<< orphan*/  hw_rq_count; int /*<<< orphan*/  job_list_lock; int /*<<< orphan*/  ring_mirror_list; int /*<<< orphan*/  job_scheduled; int /*<<< orphan*/  wake_up_worker; int /*<<< orphan*/ * sched_rq; struct drm_sched_backend_ops const* ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,char const*) ; 
 int DRM_SCHED_PRIORITY_MAX ; 
 int DRM_SCHED_PRIORITY_MIN ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic64_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_sched_job_timedout ; 
 int /*<<< orphan*/  drm_sched_main ; 
 int /*<<< orphan*/  drm_sched_rq_init (struct drm_gpu_scheduler*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kthread_run (int /*<<< orphan*/ ,struct drm_gpu_scheduler*,char const*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int drm_sched_init(struct drm_gpu_scheduler *sched,
		   const struct drm_sched_backend_ops *ops,
		   unsigned hw_submission,
		   unsigned hang_limit,
		   long timeout,
		   const char *name)
{
	int i, ret;
	sched->ops = ops;
	sched->hw_submission_limit = hw_submission;
	sched->name = name;
	sched->timeout = timeout;
	sched->hang_limit = hang_limit;
	for (i = DRM_SCHED_PRIORITY_MIN; i < DRM_SCHED_PRIORITY_MAX; i++)
		drm_sched_rq_init(sched, &sched->sched_rq[i]);

	init_waitqueue_head(&sched->wake_up_worker);
	init_waitqueue_head(&sched->job_scheduled);
	INIT_LIST_HEAD(&sched->ring_mirror_list);
	spin_lock_init(&sched->job_list_lock);
	atomic_set(&sched->hw_rq_count, 0);
	INIT_DELAYED_WORK(&sched->work_tdr, drm_sched_job_timedout);
	atomic_set(&sched->num_jobs, 0);
	atomic64_set(&sched->job_id_count, 0);

	/* Each scheduler will run on a seperate kernel thread */
	sched->thread = kthread_run(drm_sched_main, sched, sched->name);
	if (IS_ERR(sched->thread)) {
		ret = PTR_ERR(sched->thread);
		sched->thread = NULL;
		DRM_ERROR("Failed to create scheduler for %s.\n", name);
		return ret;
	}

	sched->ready = true;
	return 0;
}
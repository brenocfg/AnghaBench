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
struct drm_sched_job {int /*<<< orphan*/  finish_cb; struct drm_sched_fence* s_fence; } ;
struct drm_sched_fence {int /*<<< orphan*/  finished; } ;
struct drm_sched_entity {int /*<<< orphan*/  last_scheduled; int /*<<< orphan*/  job_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int ENOENT ; 
 int /*<<< orphan*/  ESRCH ; 
 int dma_fence_add_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (int /*<<< orphan*/ *,int /*<<< orphan*/ *)) ; 
 int /*<<< orphan*/  dma_fence_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_sched_entity_kill_jobs_cb (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_sched_fence_scheduled (struct drm_sched_fence*) ; 
 int /*<<< orphan*/  spsc_queue_pop (int /*<<< orphan*/ *) ; 
 struct drm_sched_job* to_drm_sched_job (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void drm_sched_entity_kill_jobs(struct drm_sched_entity *entity)
{
	struct drm_sched_job *job;
	int r;

	while ((job = to_drm_sched_job(spsc_queue_pop(&entity->job_queue)))) {
		struct drm_sched_fence *s_fence = job->s_fence;

		drm_sched_fence_scheduled(s_fence);
		dma_fence_set_error(&s_fence->finished, -ESRCH);

		/*
		 * When pipe is hanged by older entity, new entity might
		 * not even have chance to submit it's first job to HW
		 * and so entity->last_scheduled will remain NULL
		 */
		if (!entity->last_scheduled) {
			drm_sched_entity_kill_jobs_cb(NULL, &job->finish_cb);
			continue;
		}

		r = dma_fence_add_callback(entity->last_scheduled,
					   &job->finish_cb,
					   drm_sched_entity_kill_jobs_cb);
		if (r == -ENOENT)
			drm_sched_entity_kill_jobs_cb(NULL, &job->finish_cb);
		else if (r)
			DRM_ERROR("fence add callback failed (%d)\n", r);
	}
}
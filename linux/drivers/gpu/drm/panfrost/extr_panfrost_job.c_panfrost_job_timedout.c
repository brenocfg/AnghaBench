#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct panfrost_job {int /*<<< orphan*/  done_fence; struct panfrost_device* pfdev; } ;
struct panfrost_device {int /*<<< orphan*/  reset_lock; TYPE_2__* js; int /*<<< orphan*/ ** jobs; int /*<<< orphan*/  dev; } ;
struct drm_sched_job {int dummy; } ;
struct drm_gpu_scheduler {int /*<<< orphan*/  work_tdr; } ;
struct TYPE_4__ {TYPE_1__* queue; int /*<<< orphan*/  job_lock; } ;
struct TYPE_3__ {struct drm_gpu_scheduler sched; } ;

/* Variables and functions */
 int /*<<< orphan*/  JS_CONFIG (int) ; 
 int /*<<< orphan*/  JS_HEAD_LO (int) ; 
 int /*<<< orphan*/  JS_STATUS (int) ; 
 int /*<<< orphan*/  JS_TAIL_LO (int) ; 
 int NUM_JOB_SLOTS ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct drm_sched_job*) ; 
 scalar_t__ dma_fence_is_signaled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_sched_increase_karma (struct drm_sched_job*) ; 
 int /*<<< orphan*/  drm_sched_resubmit_jobs (struct drm_gpu_scheduler*) ; 
 int /*<<< orphan*/  drm_sched_start (struct drm_gpu_scheduler*,int) ; 
 int /*<<< orphan*/  drm_sched_stop (struct drm_gpu_scheduler*,struct drm_sched_job*) ; 
 int /*<<< orphan*/  job_read (struct panfrost_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panfrost_devfreq_record_transition (struct panfrost_device*,int) ; 
 int /*<<< orphan*/  panfrost_device_reset (struct panfrost_device*) ; 
 int panfrost_job_get_slot (struct panfrost_job*) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct panfrost_job* to_panfrost_job (struct drm_sched_job*) ; 

__attribute__((used)) static void panfrost_job_timedout(struct drm_sched_job *sched_job)
{
	struct panfrost_job *job = to_panfrost_job(sched_job);
	struct panfrost_device *pfdev = job->pfdev;
	int js = panfrost_job_get_slot(job);
	unsigned long flags;
	int i;

	/*
	 * If the GPU managed to complete this jobs fence, the timeout is
	 * spurious. Bail out.
	 */
	if (dma_fence_is_signaled(job->done_fence))
		return;

	dev_err(pfdev->dev, "gpu sched timeout, js=%d, config=0x%x, status=0x%x, head=0x%x, tail=0x%x, sched_job=%p",
		js,
		job_read(pfdev, JS_CONFIG(js)),
		job_read(pfdev, JS_STATUS(js)),
		job_read(pfdev, JS_HEAD_LO(js)),
		job_read(pfdev, JS_TAIL_LO(js)),
		sched_job);

	if (!mutex_trylock(&pfdev->reset_lock))
		return;

	for (i = 0; i < NUM_JOB_SLOTS; i++) {
		struct drm_gpu_scheduler *sched = &pfdev->js->queue[i].sched;

		drm_sched_stop(sched, sched_job);
		if (js != i)
			/* Ensure any timeouts on other slots have finished */
			cancel_delayed_work_sync(&sched->work_tdr);
	}

	drm_sched_increase_karma(sched_job);

	spin_lock_irqsave(&pfdev->js->job_lock, flags);
	for (i = 0; i < NUM_JOB_SLOTS; i++) {
		if (pfdev->jobs[i]) {
			pm_runtime_put_noidle(pfdev->dev);
			pfdev->jobs[i] = NULL;
		}
	}
	spin_unlock_irqrestore(&pfdev->js->job_lock, flags);

	/* panfrost_core_dump(pfdev); */

	panfrost_devfreq_record_transition(pfdev, js);
	panfrost_device_reset(pfdev);

	for (i = 0; i < NUM_JOB_SLOTS; i++)
		drm_sched_resubmit_jobs(&pfdev->js->queue[i].sched);

	/* restart scheduler after GPU is usable again */
	for (i = 0; i < NUM_JOB_SLOTS; i++)
		drm_sched_start(&pfdev->js->queue[i].sched, true);

	mutex_unlock(&pfdev->reset_lock);
}
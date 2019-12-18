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
struct TYPE_4__ {TYPE_3__* s_fence; } ;
struct panfrost_job {scalar_t__ done_fence; TYPE_1__ base; struct panfrost_device* pfdev; } ;
struct panfrost_device {struct panfrost_job** jobs; } ;
struct drm_sched_job {int dummy; } ;
struct dma_fence {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  error; } ;
struct TYPE_6__ {TYPE_2__ finished; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct dma_fence*) ; 
 scalar_t__ dma_fence_get (struct dma_fence*) ; 
 int /*<<< orphan*/  dma_fence_put (scalar_t__) ; 
 struct dma_fence* panfrost_fence_create (struct panfrost_device*,int) ; 
 int panfrost_job_get_slot (struct panfrost_job*) ; 
 int /*<<< orphan*/  panfrost_job_hw_submit (struct panfrost_job*,int) ; 
 struct panfrost_job* to_panfrost_job (struct drm_sched_job*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dma_fence *panfrost_job_run(struct drm_sched_job *sched_job)
{
	struct panfrost_job *job = to_panfrost_job(sched_job);
	struct panfrost_device *pfdev = job->pfdev;
	int slot = panfrost_job_get_slot(job);
	struct dma_fence *fence = NULL;

	if (unlikely(job->base.s_fence->finished.error))
		return NULL;

	pfdev->jobs[slot] = job;

	fence = panfrost_fence_create(pfdev, slot);
	if (IS_ERR(fence))
		return NULL;

	if (job->done_fence)
		dma_fence_put(job->done_fence);
	job->done_fence = dma_fence_get(fence);

	panfrost_job_hw_submit(job, slot);

	return fence;
}
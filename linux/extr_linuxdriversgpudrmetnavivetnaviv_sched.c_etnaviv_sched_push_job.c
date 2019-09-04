#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_2__* s_fence; } ;
struct TYPE_6__ {int /*<<< orphan*/  ctx; } ;
struct etnaviv_gem_submit {scalar_t__ out_fence_id; TYPE_3__* gpu; TYPE_4__ sched_job; int /*<<< orphan*/  refcount; int /*<<< orphan*/  out_fence; TYPE_1__ cmdbuf; } ;
struct drm_sched_entity {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  fence_lock; int /*<<< orphan*/  fence_idr; } ;
struct TYPE_7__ {int /*<<< orphan*/  finished; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INT_MAX ; 
 int /*<<< orphan*/  dma_fence_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_sched_entity_push_job (TYPE_4__*,struct drm_sched_entity*) ; 
 int drm_sched_job_init (TYPE_4__*,struct drm_sched_entity*,int /*<<< orphan*/ ) ; 
 scalar_t__ idr_alloc_cyclic (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int etnaviv_sched_push_job(struct drm_sched_entity *sched_entity,
			   struct etnaviv_gem_submit *submit)
{
	int ret = 0;

	/*
	 * Hold the fence lock across the whole operation to avoid jobs being
	 * pushed out of order with regard to their sched fence seqnos as
	 * allocated in drm_sched_job_init.
	 */
	mutex_lock(&submit->gpu->fence_lock);

	ret = drm_sched_job_init(&submit->sched_job, sched_entity,
				 submit->cmdbuf.ctx);
	if (ret)
		goto out_unlock;

	submit->out_fence = dma_fence_get(&submit->sched_job.s_fence->finished);
	submit->out_fence_id = idr_alloc_cyclic(&submit->gpu->fence_idr,
						submit->out_fence, 0,
						INT_MAX, GFP_KERNEL);
	if (submit->out_fence_id < 0) {
		ret = -ENOMEM;
		goto out_unlock;
	}

	/* the scheduler holds on to the job now */
	kref_get(&submit->refcount);

	drm_sched_entity_push_job(&submit->sched_job, sched_entity);

out_unlock:
	mutex_unlock(&submit->gpu->fence_lock);

	return ret;
}
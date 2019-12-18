#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ww_acquire_ctx {int dummy; } ;
struct TYPE_7__ {TYPE_2__* s_fence; } ;
struct panfrost_job {int /*<<< orphan*/  bo_count; int /*<<< orphan*/  bos; int /*<<< orphan*/  render_done_fence; TYPE_3__ base; int /*<<< orphan*/  implicit_fences; int /*<<< orphan*/  refcount; TYPE_1__* file_priv; struct panfrost_device* pfdev; } ;
struct panfrost_device {int /*<<< orphan*/  sched_lock; } ;
struct drm_sched_entity {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  finished; } ;
struct TYPE_5__ {struct drm_sched_entity* sched_entity; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_fence_get (int /*<<< orphan*/ *) ; 
 int drm_gem_lock_reservations (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ww_acquire_ctx*) ; 
 int /*<<< orphan*/  drm_gem_unlock_reservations (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ww_acquire_ctx*) ; 
 int /*<<< orphan*/  drm_sched_entity_push_job (TYPE_3__*,struct drm_sched_entity*) ; 
 int drm_sched_job_init (TYPE_3__*,struct drm_sched_entity*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panfrost_acquire_object_fences (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panfrost_attach_object_fences (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int panfrost_job_get_slot (struct panfrost_job*) ; 

int panfrost_job_push(struct panfrost_job *job)
{
	struct panfrost_device *pfdev = job->pfdev;
	int slot = panfrost_job_get_slot(job);
	struct drm_sched_entity *entity = &job->file_priv->sched_entity[slot];
	struct ww_acquire_ctx acquire_ctx;
	int ret = 0;

	mutex_lock(&pfdev->sched_lock);

	ret = drm_gem_lock_reservations(job->bos, job->bo_count,
					    &acquire_ctx);
	if (ret) {
		mutex_unlock(&pfdev->sched_lock);
		return ret;
	}

	ret = drm_sched_job_init(&job->base, entity, NULL);
	if (ret) {
		mutex_unlock(&pfdev->sched_lock);
		goto unlock;
	}

	job->render_done_fence = dma_fence_get(&job->base.s_fence->finished);

	kref_get(&job->refcount); /* put by scheduler job completion */

	panfrost_acquire_object_fences(job->bos, job->bo_count,
				       job->implicit_fences);

	drm_sched_entity_push_job(&job->base, entity);

	mutex_unlock(&pfdev->sched_lock);

	panfrost_attach_object_fences(job->bos, job->bo_count,
				      job->render_done_fence);

unlock:
	drm_gem_unlock_reservations(job->bos, job->bo_count, &acquire_ctx);

	return ret;
}
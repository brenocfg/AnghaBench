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
struct v3d_job {int /*<<< orphan*/  last_dep; int /*<<< orphan*/  deps; } ;
struct drm_sched_job {int dummy; } ;
struct drm_sched_entity {int dummy; } ;
struct dma_fence {int dummy; } ;

/* Variables and functions */
 struct v3d_job* to_v3d_job (struct drm_sched_job*) ; 
 int /*<<< orphan*/  xa_empty (int /*<<< orphan*/ *) ; 
 struct dma_fence* xa_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dma_fence *
v3d_job_dependency(struct drm_sched_job *sched_job,
		   struct drm_sched_entity *s_entity)
{
	struct v3d_job *job = to_v3d_job(sched_job);

	/* XXX: Wait on a fence for switching the GMP if necessary,
	 * and then do so.
	 */

	if (!xa_empty(&job->deps))
		return xa_erase(&job->deps, job->last_dep++);

	return NULL;
}
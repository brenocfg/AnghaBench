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
struct v3d_job {struct dma_fence* in_fence; struct v3d_exec_info* exec; } ;
struct v3d_exec_info {struct dma_fence* bin_done_fence; struct v3d_job bin; } ;
struct drm_sched_job {int dummy; } ;
struct drm_sched_entity {int dummy; } ;
struct dma_fence {int dummy; } ;
typedef  enum v3d_queue { ____Placeholder_v3d_queue } v3d_queue ;

/* Variables and functions */
 int V3D_BIN ; 
 int V3D_RENDER ; 
 struct v3d_job* to_v3d_job (struct drm_sched_job*) ; 

__attribute__((used)) static struct dma_fence *
v3d_job_dependency(struct drm_sched_job *sched_job,
		   struct drm_sched_entity *s_entity)
{
	struct v3d_job *job = to_v3d_job(sched_job);
	struct v3d_exec_info *exec = job->exec;
	enum v3d_queue q = job == &exec->bin ? V3D_BIN : V3D_RENDER;
	struct dma_fence *fence;

	fence = job->in_fence;
	if (fence) {
		job->in_fence = NULL;
		return fence;
	}

	if (q == V3D_RENDER) {
		/* If we had a bin job, the render job definitely depends on
		 * it. We first have to wait for bin to be scheduled, so that
		 * its done_fence is created.
		 */
		fence = exec->bin_done_fence;
		if (fence) {
			exec->bin_done_fence = NULL;
			return fence;
		}
	}

	/* XXX: Wait on a fence for switching the GMP if necessary,
	 * and then do so.
	 */

	return fence;
}
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
struct dma_fence {int dummy; } ;
struct amdgpu_ring {int /*<<< orphan*/  sched; } ;
struct TYPE_2__ {int /*<<< orphan*/ * sched; } ;
struct amdgpu_job {int /*<<< orphan*/  fence; int /*<<< orphan*/  ibs; int /*<<< orphan*/  num_ibs; TYPE_1__ base; } ;

/* Variables and functions */
 int amdgpu_ib_schedule (struct amdgpu_ring*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct dma_fence**) ; 
 int /*<<< orphan*/  amdgpu_job_free (struct amdgpu_job*) ; 
 int /*<<< orphan*/  dma_fence_get (struct dma_fence*) ; 

int amdgpu_job_submit_direct(struct amdgpu_job *job, struct amdgpu_ring *ring,
			     struct dma_fence **fence)
{
	int r;

	job->base.sched = &ring->sched;
	r = amdgpu_ib_schedule(ring, job->num_ibs, job->ibs, NULL, fence);
	job->fence = dma_fence_get(*fence);
	if (r)
		return r;

	amdgpu_job_free(job);
	return 0;
}
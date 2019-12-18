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
struct dma_fence {int dummy; } ;
struct amdgpu_ring {int /*<<< orphan*/  adev; } ;
struct TYPE_4__ {TYPE_1__* s_fence; int /*<<< orphan*/  sched; } ;
struct amdgpu_job {unsigned int num_ibs; int /*<<< orphan*/ * ibs; struct dma_fence* fence; TYPE_2__ base; } ;
struct TYPE_3__ {struct dma_fence finished; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_ib_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct dma_fence*) ; 
 struct amdgpu_ring* to_amdgpu_ring (int /*<<< orphan*/ ) ; 

void amdgpu_job_free_resources(struct amdgpu_job *job)
{
	struct amdgpu_ring *ring = to_amdgpu_ring(job->base.sched);
	struct dma_fence *f;
	unsigned i;

	/* use sched fence if available */
	f = job->base.s_fence ? &job->base.s_fence->finished : job->fence;

	for (i = 0; i < job->num_ibs; ++i)
		amdgpu_ib_free(ring->adev, &job->ibs[i], f);
}
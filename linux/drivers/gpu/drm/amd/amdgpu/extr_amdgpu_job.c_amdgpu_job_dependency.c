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
struct drm_sched_job {int dummy; } ;
struct drm_sched_entity {TYPE_1__* rq; } ;
struct dma_fence {int dummy; } ;
struct amdgpu_vm {int dummy; } ;
struct amdgpu_ring {int /*<<< orphan*/  adev; } ;
struct TYPE_6__ {TYPE_2__* s_fence; } ;
struct amdgpu_job {int /*<<< orphan*/  sync; TYPE_3__ base; int /*<<< orphan*/  vmid; int /*<<< orphan*/  sched_sync; struct amdgpu_vm* vm; } ;
struct TYPE_5__ {int /*<<< orphan*/  finished; } ;
struct TYPE_4__ {int /*<<< orphan*/  sched; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int amdgpu_sync_fence (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct dma_fence*,int) ; 
 struct dma_fence* amdgpu_sync_get_fence (int /*<<< orphan*/ *,int*) ; 
 int amdgpu_vmid_grab (struct amdgpu_vm*,struct amdgpu_ring*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct amdgpu_job*) ; 
 scalar_t__ drm_sched_dependency_optimized (struct dma_fence*,struct drm_sched_entity*) ; 
 struct amdgpu_job* to_amdgpu_job (struct drm_sched_job*) ; 
 struct amdgpu_ring* to_amdgpu_ring (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dma_fence *amdgpu_job_dependency(struct drm_sched_job *sched_job,
					       struct drm_sched_entity *s_entity)
{
	struct amdgpu_ring *ring = to_amdgpu_ring(s_entity->rq->sched);
	struct amdgpu_job *job = to_amdgpu_job(sched_job);
	struct amdgpu_vm *vm = job->vm;
	struct dma_fence *fence;
	bool explicit = false;
	int r;

	fence = amdgpu_sync_get_fence(&job->sync, &explicit);
	if (fence && explicit) {
		if (drm_sched_dependency_optimized(fence, s_entity)) {
			r = amdgpu_sync_fence(ring->adev, &job->sched_sync,
					      fence, false);
			if (r)
				DRM_ERROR("Error adding fence (%d)\n", r);
		}
	}

	while (fence == NULL && vm && !job->vmid) {
		r = amdgpu_vmid_grab(vm, ring, &job->sync,
				     &job->base.s_fence->finished,
				     job);
		if (r)
			DRM_ERROR("Error getting VM ID (%d)\n", r);

		fence = amdgpu_sync_get_fence(&job->sync, NULL);
	}

	return fence;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct dma_fence {scalar_t__ context; } ;
struct amdgpu_sync {struct dma_fence* last_vm_update; } ;
struct amdgpu_vmid {scalar_t__ owner; scalar_t__ pd_gpu_addr; TYPE_3__* flushed_updates; struct amdgpu_sync active; TYPE_4__* last_flush; } ;
struct TYPE_8__ {scalar_t__ fence_context; } ;
struct amdgpu_vm {int use_cpu_for_update; TYPE_2__ entity; struct amdgpu_vmid** reserved_vmid; } ;
struct amdgpu_ring {scalar_t__ idx; struct amdgpu_device* adev; TYPE_1__* funcs; } ;
struct amdgpu_job {scalar_t__ vm_pd_addr; int vm_needs_flush; } ;
struct amdgpu_device {scalar_t__ fence_context; } ;
struct TYPE_10__ {scalar_t__ context; } ;
struct TYPE_9__ {scalar_t__ context; } ;
struct TYPE_7__ {unsigned int vmhub; } ;

/* Variables and functions */
 int amdgpu_sync_fence (struct amdgpu_device*,struct amdgpu_sync*,struct dma_fence*,int) ; 
 struct dma_fence* amdgpu_sync_peek_fence (struct amdgpu_sync*,struct amdgpu_ring*) ; 
 TYPE_3__* dma_fence_get (struct dma_fence*) ; 
 int /*<<< orphan*/  dma_fence_is_later (struct dma_fence*,TYPE_3__*) ; 
 int /*<<< orphan*/  dma_fence_is_signaled (TYPE_4__*) ; 
 int /*<<< orphan*/  dma_fence_put (TYPE_3__*) ; 

__attribute__((used)) static int amdgpu_vmid_grab_reserved(struct amdgpu_vm *vm,
				     struct amdgpu_ring *ring,
				     struct amdgpu_sync *sync,
				     struct dma_fence *fence,
				     struct amdgpu_job *job,
				     struct amdgpu_vmid **id)
{
	struct amdgpu_device *adev = ring->adev;
	unsigned vmhub = ring->funcs->vmhub;
	uint64_t fence_context = adev->fence_context + ring->idx;
	struct dma_fence *updates = sync->last_vm_update;
	bool needs_flush = vm->use_cpu_for_update;
	int r = 0;

	*id = vm->reserved_vmid[vmhub];
	if (updates && (*id)->flushed_updates &&
	    updates->context == (*id)->flushed_updates->context &&
	    !dma_fence_is_later(updates, (*id)->flushed_updates))
	    updates = NULL;

	if ((*id)->owner != vm->entity.fence_context ||
	    job->vm_pd_addr != (*id)->pd_gpu_addr ||
	    updates || !(*id)->last_flush ||
	    ((*id)->last_flush->context != fence_context &&
	     !dma_fence_is_signaled((*id)->last_flush))) {
		struct dma_fence *tmp;

		/* to prevent one context starved by another context */
		(*id)->pd_gpu_addr = 0;
		tmp = amdgpu_sync_peek_fence(&(*id)->active, ring);
		if (tmp) {
			*id = NULL;
			r = amdgpu_sync_fence(adev, sync, tmp, false);
			return r;
		}
		needs_flush = true;
	}

	/* Good we can use this VMID. Remember this submission as
	* user of the VMID.
	*/
	r = amdgpu_sync_fence(ring->adev, &(*id)->active, fence, false);
	if (r)
		return r;

	if (updates) {
		dma_fence_put((*id)->flushed_updates);
		(*id)->flushed_updates = dma_fence_get(updates);
	}
	job->vm_needs_flush = needs_flush;
	return 0;
}
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
struct dma_fence {int dummy; } ;
struct amdgpu_vmid_mgr {int ids; int /*<<< orphan*/  lock; int /*<<< orphan*/  ids_lru; } ;
struct amdgpu_vmid {int /*<<< orphan*/ * last_flush; int /*<<< orphan*/  owner; int /*<<< orphan*/  pd_gpu_addr; int /*<<< orphan*/  list; int /*<<< orphan*/ * flushed_updates; int /*<<< orphan*/  active; } ;
struct TYPE_6__ {int /*<<< orphan*/  fence_context; } ;
struct amdgpu_vm {int /*<<< orphan*/  pasid; TYPE_3__ entity; scalar_t__* reserved_vmid; } ;
struct amdgpu_sync {struct dma_fence* last_vm_update; } ;
struct amdgpu_ring {struct amdgpu_device* adev; TYPE_1__* funcs; } ;
struct amdgpu_job {int vm_needs_flush; int /*<<< orphan*/  pasid; struct amdgpu_vmid* vmid; int /*<<< orphan*/  vm_pd_addr; } ;
struct TYPE_5__ {struct amdgpu_vmid_mgr* id_mgr; } ;
struct amdgpu_device {TYPE_2__ vm_manager; } ;
struct TYPE_4__ {unsigned int vmhub; } ;

/* Variables and functions */
 int amdgpu_sync_fence (struct amdgpu_device*,int /*<<< orphan*/ *,struct dma_fence*,int) ; 
 int amdgpu_vmid_grab_idle (struct amdgpu_vm*,struct amdgpu_ring*,struct amdgpu_sync*,struct amdgpu_vmid**) ; 
 int amdgpu_vmid_grab_reserved (struct amdgpu_vm*,struct amdgpu_ring*,struct amdgpu_sync*,struct dma_fence*,struct amdgpu_job*,struct amdgpu_vmid**) ; 
 int amdgpu_vmid_grab_used (struct amdgpu_vm*,struct amdgpu_ring*,struct amdgpu_sync*,struct dma_fence*,struct amdgpu_job*,struct amdgpu_vmid**) ; 
 int /*<<< orphan*/ * dma_fence_get (struct dma_fence*) ; 
 int /*<<< orphan*/  dma_fence_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_amdgpu_vm_grab_id (struct amdgpu_vm*,struct amdgpu_ring*,struct amdgpu_job*) ; 

int amdgpu_vmid_grab(struct amdgpu_vm *vm, struct amdgpu_ring *ring,
		     struct amdgpu_sync *sync, struct dma_fence *fence,
		     struct amdgpu_job *job)
{
	struct amdgpu_device *adev = ring->adev;
	unsigned vmhub = ring->funcs->vmhub;
	struct amdgpu_vmid_mgr *id_mgr = &adev->vm_manager.id_mgr[vmhub];
	struct amdgpu_vmid *idle = NULL;
	struct amdgpu_vmid *id = NULL;
	int r = 0;

	mutex_lock(&id_mgr->lock);
	r = amdgpu_vmid_grab_idle(vm, ring, sync, &idle);
	if (r || !idle)
		goto error;

	if (vm->reserved_vmid[vmhub]) {
		r = amdgpu_vmid_grab_reserved(vm, ring, sync, fence, job, &id);
		if (r || !id)
			goto error;
	} else {
		r = amdgpu_vmid_grab_used(vm, ring, sync, fence, job, &id);
		if (r)
			goto error;

		if (!id) {
			struct dma_fence *updates = sync->last_vm_update;

			/* Still no ID to use? Then use the idle one found earlier */
			id = idle;

			/* Remember this submission as user of the VMID */
			r = amdgpu_sync_fence(ring->adev, &id->active,
					      fence, false);
			if (r)
				goto error;

			dma_fence_put(id->flushed_updates);
			id->flushed_updates = dma_fence_get(updates);
			job->vm_needs_flush = true;
		}

		list_move_tail(&id->list, &id_mgr->ids_lru);
	}

	id->pd_gpu_addr = job->vm_pd_addr;
	id->owner = vm->entity.fence_context;

	if (job->vm_needs_flush) {
		dma_fence_put(id->last_flush);
		id->last_flush = NULL;
	}
	job->vmid = id - id_mgr->ids;
	job->pasid = vm->pasid;
	trace_amdgpu_vm_grab_id(vm, ring, job);

error:
	mutex_unlock(&id_mgr->lock);
	return r;
}
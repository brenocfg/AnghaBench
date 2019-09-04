#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct dma_fence {int dummy; } ;
struct amdgpu_vmid_mgr {int /*<<< orphan*/  lock; struct amdgpu_vmid* ids; } ;
struct amdgpu_vmid {scalar_t__ gds_base; scalar_t__ gds_size; scalar_t__ gws_base; scalar_t__ gws_size; scalar_t__ oa_base; scalar_t__ oa_size; scalar_t__ pasid; struct dma_fence* pasid_mapping; int /*<<< orphan*/  current_gpu_reset_count; struct dma_fence* last_flush; } ;
struct amdgpu_ring {TYPE_4__* funcs; struct amdgpu_device* adev; } ;
struct amdgpu_job {size_t vmid; scalar_t__ gds_base; scalar_t__ gds_size; scalar_t__ gws_base; scalar_t__ gws_size; scalar_t__ oa_base; scalar_t__ oa_size; int vm_needs_flush; scalar_t__ pasid; scalar_t__ vm_pd_addr; } ;
struct TYPE_7__ {TYPE_2__* gmc_funcs; } ;
struct TYPE_5__ {struct amdgpu_vmid_mgr* id_mgr; } ;
struct amdgpu_device {int /*<<< orphan*/  gpu_reset_counter; TYPE_3__ gmc; TYPE_1__ vm_manager; } ;
struct TYPE_8__ {unsigned int vmhub; scalar_t__ emit_switch_buffer; scalar_t__ patch_cond_exec; scalar_t__ emit_gds_switch; scalar_t__ init_cond_exec; scalar_t__ emit_wreg; int /*<<< orphan*/  emit_vm_flush; } ;
struct TYPE_6__ {scalar_t__ emit_pasid_mapping; } ;

/* Variables and functions */
 scalar_t__ AMDGPU_BO_INVALID_OFFSET ; 
 int amdgpu_fence_emit (struct amdgpu_ring*,struct dma_fence**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_gmc_emit_pasid_mapping (struct amdgpu_ring*,size_t,scalar_t__) ; 
 int /*<<< orphan*/  amdgpu_ring_emit_gds_switch (struct amdgpu_ring*,size_t,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  amdgpu_ring_emit_pipeline_sync (struct amdgpu_ring*) ; 
 int /*<<< orphan*/  amdgpu_ring_emit_switch_buffer (struct amdgpu_ring*) ; 
 int /*<<< orphan*/  amdgpu_ring_emit_vm_flush (struct amdgpu_ring*,size_t,scalar_t__) ; 
 unsigned int amdgpu_ring_init_cond_exec (struct amdgpu_ring*) ; 
 int /*<<< orphan*/  amdgpu_ring_patch_cond_exec (struct amdgpu_ring*,unsigned int) ; 
 scalar_t__ amdgpu_vmid_had_gpu_reset (struct amdgpu_device*,struct amdgpu_vmid*) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 void* dma_fence_get (struct dma_fence*) ; 
 int /*<<< orphan*/  dma_fence_is_signaled (struct dma_fence*) ; 
 int /*<<< orphan*/  dma_fence_put (struct dma_fence*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_amdgpu_vm_flush (struct amdgpu_ring*,size_t,scalar_t__) ; 

int amdgpu_vm_flush(struct amdgpu_ring *ring, struct amdgpu_job *job, bool need_pipe_sync)
{
	struct amdgpu_device *adev = ring->adev;
	unsigned vmhub = ring->funcs->vmhub;
	struct amdgpu_vmid_mgr *id_mgr = &adev->vm_manager.id_mgr[vmhub];
	struct amdgpu_vmid *id = &id_mgr->ids[job->vmid];
	bool gds_switch_needed = ring->funcs->emit_gds_switch && (
		id->gds_base != job->gds_base ||
		id->gds_size != job->gds_size ||
		id->gws_base != job->gws_base ||
		id->gws_size != job->gws_size ||
		id->oa_base != job->oa_base ||
		id->oa_size != job->oa_size);
	bool vm_flush_needed = job->vm_needs_flush;
	bool pasid_mapping_needed = id->pasid != job->pasid ||
		!id->pasid_mapping ||
		!dma_fence_is_signaled(id->pasid_mapping);
	struct dma_fence *fence = NULL;
	unsigned patch_offset = 0;
	int r;

	if (amdgpu_vmid_had_gpu_reset(adev, id)) {
		gds_switch_needed = true;
		vm_flush_needed = true;
		pasid_mapping_needed = true;
	}

	gds_switch_needed &= !!ring->funcs->emit_gds_switch;
	vm_flush_needed &= !!ring->funcs->emit_vm_flush  &&
			job->vm_pd_addr != AMDGPU_BO_INVALID_OFFSET;
	pasid_mapping_needed &= adev->gmc.gmc_funcs->emit_pasid_mapping &&
		ring->funcs->emit_wreg;

	if (!vm_flush_needed && !gds_switch_needed && !need_pipe_sync)
		return 0;

	if (ring->funcs->init_cond_exec)
		patch_offset = amdgpu_ring_init_cond_exec(ring);

	if (need_pipe_sync)
		amdgpu_ring_emit_pipeline_sync(ring);

	if (vm_flush_needed) {
		trace_amdgpu_vm_flush(ring, job->vmid, job->vm_pd_addr);
		amdgpu_ring_emit_vm_flush(ring, job->vmid, job->vm_pd_addr);
	}

	if (pasid_mapping_needed)
		amdgpu_gmc_emit_pasid_mapping(ring, job->vmid, job->pasid);

	if (vm_flush_needed || pasid_mapping_needed) {
		r = amdgpu_fence_emit(ring, &fence, 0);
		if (r)
			return r;
	}

	if (vm_flush_needed) {
		mutex_lock(&id_mgr->lock);
		dma_fence_put(id->last_flush);
		id->last_flush = dma_fence_get(fence);
		id->current_gpu_reset_count =
			atomic_read(&adev->gpu_reset_counter);
		mutex_unlock(&id_mgr->lock);
	}

	if (pasid_mapping_needed) {
		id->pasid = job->pasid;
		dma_fence_put(id->pasid_mapping);
		id->pasid_mapping = dma_fence_get(fence);
	}
	dma_fence_put(fence);

	if (ring->funcs->emit_gds_switch && gds_switch_needed) {
		id->gds_base = job->gds_base;
		id->gds_size = job->gds_size;
		id->gws_base = job->gws_base;
		id->gws_size = job->gws_size;
		id->oa_base = job->oa_base;
		id->oa_size = job->oa_size;
		amdgpu_ring_emit_gds_switch(ring, job->vmid, job->gds_base,
					    job->gds_size, job->gws_base,
					    job->gws_size, job->oa_base,
					    job->oa_size);
	}

	if (ring->funcs->patch_cond_exec)
		amdgpu_ring_patch_cond_exec(ring, patch_offset);

	/* the double SWITCH_BUFFER here *cannot* be skipped by COND_EXEC */
	if (ring->funcs->emit_switch_buffer) {
		amdgpu_ring_emit_switch_buffer(ring);
		amdgpu_ring_emit_switch_buffer(ring);
	}
	return 0;
}
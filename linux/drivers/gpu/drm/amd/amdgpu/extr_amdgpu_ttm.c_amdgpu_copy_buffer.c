#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ uint32_t ;
struct dma_resv {int dummy; } ;
struct dma_fence {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  ready; } ;
struct amdgpu_ring {TYPE_1__ sched; struct amdgpu_device* adev; } ;
struct amdgpu_job {int vm_needs_flush; TYPE_5__* ibs; int /*<<< orphan*/  sync; int /*<<< orphan*/  vm_pd_addr; } ;
struct TYPE_10__ {int /*<<< orphan*/  entity; TYPE_2__* buffer_funcs; } ;
struct TYPE_9__ {int /*<<< orphan*/  bo; } ;
struct amdgpu_device {TYPE_4__ mman; TYPE_3__ gart; } ;
struct TYPE_11__ {unsigned int length_dw; } ;
struct TYPE_8__ {unsigned int copy_num_dw; scalar_t__ copy_max_bytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_FENCE_OWNER_UNDEFINED ; 
 unsigned int DIV_ROUND_UP (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int EINVAL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  amdgpu_emit_copy_buffer (struct amdgpu_device*,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  amdgpu_gmc_pd_addr (int /*<<< orphan*/ ) ; 
 int amdgpu_job_alloc_with_ib (struct amdgpu_device*,unsigned int,struct amdgpu_job**) ; 
 int /*<<< orphan*/  amdgpu_job_free (struct amdgpu_job*) ; 
 int amdgpu_job_submit (struct amdgpu_job*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct dma_fence**) ; 
 int amdgpu_job_submit_direct (struct amdgpu_job*,struct amdgpu_ring*,struct dma_fence**) ; 
 int /*<<< orphan*/  amdgpu_ring_pad_ib (struct amdgpu_ring*,TYPE_5__*) ; 
 int amdgpu_sync_resv (struct amdgpu_device*,int /*<<< orphan*/ *,struct dma_resv*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 

int amdgpu_copy_buffer(struct amdgpu_ring *ring, uint64_t src_offset,
		       uint64_t dst_offset, uint32_t byte_count,
		       struct dma_resv *resv,
		       struct dma_fence **fence, bool direct_submit,
		       bool vm_needs_flush)
{
	struct amdgpu_device *adev = ring->adev;
	struct amdgpu_job *job;

	uint32_t max_bytes;
	unsigned num_loops, num_dw;
	unsigned i;
	int r;

	if (direct_submit && !ring->sched.ready) {
		DRM_ERROR("Trying to move memory with ring turned off.\n");
		return -EINVAL;
	}

	max_bytes = adev->mman.buffer_funcs->copy_max_bytes;
	num_loops = DIV_ROUND_UP(byte_count, max_bytes);
	num_dw = num_loops * adev->mman.buffer_funcs->copy_num_dw;

	/* for IB padding */
	while (num_dw & 0x7)
		num_dw++;

	r = amdgpu_job_alloc_with_ib(adev, num_dw * 4, &job);
	if (r)
		return r;

	if (vm_needs_flush) {
		job->vm_pd_addr = amdgpu_gmc_pd_addr(adev->gart.bo);
		job->vm_needs_flush = true;
	}
	if (resv) {
		r = amdgpu_sync_resv(adev, &job->sync, resv,
				     AMDGPU_FENCE_OWNER_UNDEFINED,
				     false);
		if (r) {
			DRM_ERROR("sync failed (%d).\n", r);
			goto error_free;
		}
	}

	for (i = 0; i < num_loops; i++) {
		uint32_t cur_size_in_bytes = min(byte_count, max_bytes);

		amdgpu_emit_copy_buffer(adev, &job->ibs[0], src_offset,
					dst_offset, cur_size_in_bytes);

		src_offset += cur_size_in_bytes;
		dst_offset += cur_size_in_bytes;
		byte_count -= cur_size_in_bytes;
	}

	amdgpu_ring_pad_ib(ring, &job->ibs[0]);
	WARN_ON(job->ibs[0].length_dw > num_dw);
	if (direct_submit)
		r = amdgpu_job_submit_direct(job, ring, fence);
	else
		r = amdgpu_job_submit(job, &adev->mman.entity,
				      AMDGPU_FENCE_OWNER_UNDEFINED, fence);
	if (r)
		goto error_free;

	return r;

error_free:
	amdgpu_job_free(job);
	DRM_ERROR("Error scheduling IBs (%d)\n", r);
	return r;
}
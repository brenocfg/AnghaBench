#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
struct reservation_object {int dummy; } ;
struct drm_mm_node {int size; } ;
struct dma_fence {int dummy; } ;
struct amdgpu_ring {int dummy; } ;
struct amdgpu_job {TYPE_4__* ibs; int /*<<< orphan*/  sync; } ;
struct TYPE_9__ {int /*<<< orphan*/  entity; TYPE_1__* buffer_funcs; int /*<<< orphan*/  buffer_funcs_enabled; struct amdgpu_ring* buffer_funcs_ring; } ;
struct amdgpu_device {TYPE_2__ mman; } ;
struct TYPE_12__ {scalar_t__ mem_type; struct drm_mm_node* mm_node; } ;
struct TYPE_10__ {unsigned long num_pages; TYPE_6__ mem; int /*<<< orphan*/  bdev; } ;
struct amdgpu_bo {TYPE_3__ tbo; } ;
struct TYPE_11__ {unsigned int length_dw; } ;
struct TYPE_8__ {int fill_max_bytes; unsigned int fill_num_dw; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_FENCE_OWNER_UNDEFINED ; 
 scalar_t__ DIV_ROUND_UP (int,int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int EINVAL ; 
 int PAGE_SHIFT ; 
 scalar_t__ TTM_PL_TT ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  amdgpu_emit_fill_buffer (struct amdgpu_device*,TYPE_4__*,int,int /*<<< orphan*/ ,int) ; 
 int amdgpu_job_alloc_with_ib (struct amdgpu_device*,unsigned int,struct amdgpu_job**) ; 
 int /*<<< orphan*/  amdgpu_job_free (struct amdgpu_job*) ; 
 int amdgpu_job_submit (struct amdgpu_job*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct dma_fence**) ; 
 int /*<<< orphan*/  amdgpu_mm_node_addr (TYPE_3__*,struct drm_mm_node*,TYPE_6__*) ; 
 int /*<<< orphan*/  amdgpu_ring_pad_ib (struct amdgpu_ring*,TYPE_4__*) ; 
 int amdgpu_sync_resv (struct amdgpu_device*,int /*<<< orphan*/ *,struct reservation_object*,int /*<<< orphan*/ ,int) ; 
 struct amdgpu_device* amdgpu_ttm_adev (int /*<<< orphan*/ ) ; 
 int amdgpu_ttm_alloc_gart (TYPE_3__*) ; 
 int min (int,int) ; 

int amdgpu_fill_buffer(struct amdgpu_bo *bo,
		       uint32_t src_data,
		       struct reservation_object *resv,
		       struct dma_fence **fence)
{
	struct amdgpu_device *adev = amdgpu_ttm_adev(bo->tbo.bdev);
	uint32_t max_bytes = adev->mman.buffer_funcs->fill_max_bytes;
	struct amdgpu_ring *ring = adev->mman.buffer_funcs_ring;

	struct drm_mm_node *mm_node;
	unsigned long num_pages;
	unsigned int num_loops, num_dw;

	struct amdgpu_job *job;
	int r;

	if (!adev->mman.buffer_funcs_enabled) {
		DRM_ERROR("Trying to clear memory with ring turned off.\n");
		return -EINVAL;
	}

	if (bo->tbo.mem.mem_type == TTM_PL_TT) {
		r = amdgpu_ttm_alloc_gart(&bo->tbo);
		if (r)
			return r;
	}

	num_pages = bo->tbo.num_pages;
	mm_node = bo->tbo.mem.mm_node;
	num_loops = 0;
	while (num_pages) {
		uint32_t byte_count = mm_node->size << PAGE_SHIFT;

		num_loops += DIV_ROUND_UP(byte_count, max_bytes);
		num_pages -= mm_node->size;
		++mm_node;
	}
	num_dw = num_loops * adev->mman.buffer_funcs->fill_num_dw;

	/* for IB padding */
	num_dw += 64;

	r = amdgpu_job_alloc_with_ib(adev, num_dw * 4, &job);
	if (r)
		return r;

	if (resv) {
		r = amdgpu_sync_resv(adev, &job->sync, resv,
				     AMDGPU_FENCE_OWNER_UNDEFINED, false);
		if (r) {
			DRM_ERROR("sync failed (%d).\n", r);
			goto error_free;
		}
	}

	num_pages = bo->tbo.num_pages;
	mm_node = bo->tbo.mem.mm_node;

	while (num_pages) {
		uint32_t byte_count = mm_node->size << PAGE_SHIFT;
		uint64_t dst_addr;

		dst_addr = amdgpu_mm_node_addr(&bo->tbo, mm_node, &bo->tbo.mem);
		while (byte_count) {
			uint32_t cur_size_in_bytes = min(byte_count, max_bytes);

			amdgpu_emit_fill_buffer(adev, &job->ibs[0], src_data,
						dst_addr, cur_size_in_bytes);

			dst_addr += cur_size_in_bytes;
			byte_count -= cur_size_in_bytes;
		}

		num_pages -= mm_node->size;
		++mm_node;
	}

	amdgpu_ring_pad_ib(ring, &job->ibs[0]);
	WARN_ON(job->ibs[0].length_dw > num_dw);
	r = amdgpu_job_submit(job, &adev->mman.entity,
			      AMDGPU_FENCE_OWNER_UNDEFINED, fence);
	if (r)
		goto error_free;

	return 0;

error_free:
	amdgpu_job_free(job);
	return r;
}
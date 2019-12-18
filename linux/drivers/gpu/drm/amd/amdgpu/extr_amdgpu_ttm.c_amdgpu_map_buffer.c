#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int u64 ;
struct ttm_tt {int dummy; } ;
struct ttm_mem_reg {int dummy; } ;
struct ttm_buffer_object {struct ttm_tt* ttm; } ;
struct dma_fence {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/ * dma_address; } ;
struct amdgpu_ttm_tt {TYPE_4__ ttm; } ;
struct amdgpu_ring {struct amdgpu_device* adev; } ;
struct amdgpu_job {TYPE_6__* ibs; } ;
struct TYPE_12__ {int /*<<< orphan*/  entity; TYPE_2__* buffer_funcs; } ;
struct TYPE_10__ {int /*<<< orphan*/  bo; } ;
struct TYPE_8__ {int gart_start; } ;
struct amdgpu_device {TYPE_5__ mman; TYPE_3__ gart; TYPE_1__ gmc; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_13__ {unsigned int length_dw; int /*<<< orphan*/ * ptr; scalar_t__ gpu_addr; } ;
struct TYPE_9__ {int copy_max_bytes; unsigned int copy_num_dw; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_FENCE_OWNER_UNDEFINED ; 
 int AMDGPU_GPU_PAGE_SIZE ; 
 int AMDGPU_GTT_MAX_TRANSFER_SIZE ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int amdgpu_bo_gpu_offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_emit_copy_buffer (struct amdgpu_device*,TYPE_6__*,int,int,unsigned int) ; 
 int amdgpu_gart_map (struct amdgpu_device*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int amdgpu_job_alloc_with_ib (struct amdgpu_device*,unsigned int,struct amdgpu_job**) ; 
 int /*<<< orphan*/  amdgpu_job_free (struct amdgpu_job*) ; 
 int amdgpu_job_submit (struct amdgpu_job*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct dma_fence**) ; 
 int /*<<< orphan*/  amdgpu_ring_pad_ib (struct amdgpu_ring*,TYPE_6__*) ; 
 int amdgpu_ttm_tt_pte_flags (struct amdgpu_device*,struct ttm_tt*,struct ttm_mem_reg*) ; 
 int /*<<< orphan*/  dma_fence_put (struct dma_fence*) ; 

__attribute__((used)) static int amdgpu_map_buffer(struct ttm_buffer_object *bo,
			     struct ttm_mem_reg *mem, unsigned num_pages,
			     uint64_t offset, unsigned window,
			     struct amdgpu_ring *ring,
			     uint64_t *addr)
{
	struct amdgpu_ttm_tt *gtt = (void *)bo->ttm;
	struct amdgpu_device *adev = ring->adev;
	struct ttm_tt *ttm = bo->ttm;
	struct amdgpu_job *job;
	unsigned num_dw, num_bytes;
	dma_addr_t *dma_address;
	struct dma_fence *fence;
	uint64_t src_addr, dst_addr;
	uint64_t flags;
	int r;

	BUG_ON(adev->mman.buffer_funcs->copy_max_bytes <
	       AMDGPU_GTT_MAX_TRANSFER_SIZE * 8);

	*addr = adev->gmc.gart_start;
	*addr += (u64)window * AMDGPU_GTT_MAX_TRANSFER_SIZE *
		AMDGPU_GPU_PAGE_SIZE;

	num_dw = adev->mman.buffer_funcs->copy_num_dw;
	while (num_dw & 0x7)
		num_dw++;

	num_bytes = num_pages * 8;

	r = amdgpu_job_alloc_with_ib(adev, num_dw * 4 + num_bytes, &job);
	if (r)
		return r;

	src_addr = num_dw * 4;
	src_addr += job->ibs[0].gpu_addr;

	dst_addr = amdgpu_bo_gpu_offset(adev->gart.bo);
	dst_addr += window * AMDGPU_GTT_MAX_TRANSFER_SIZE * 8;
	amdgpu_emit_copy_buffer(adev, &job->ibs[0], src_addr,
				dst_addr, num_bytes);

	amdgpu_ring_pad_ib(ring, &job->ibs[0]);
	WARN_ON(job->ibs[0].length_dw > num_dw);

	dma_address = &gtt->ttm.dma_address[offset >> PAGE_SHIFT];
	flags = amdgpu_ttm_tt_pte_flags(adev, ttm, mem);
	r = amdgpu_gart_map(adev, 0, num_pages, dma_address, flags,
			    &job->ibs[0].ptr[num_dw]);
	if (r)
		goto error_free;

	r = amdgpu_job_submit(job, &adev->mman.entity,
			      AMDGPU_FENCE_OWNER_UNDEFINED, &fence);
	if (r)
		goto error_free;

	dma_fence_put(fence);

	return r;

error_free:
	amdgpu_job_free(job);
	return r;
}
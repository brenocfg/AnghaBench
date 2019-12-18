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
typedef  int uint64_t ;
typedef  void* uint32_t ;
struct ttm_operation_ctx {int member_0; int member_1; } ;
struct dma_fence {int dummy; } ;
struct amdgpu_ring {int me; struct amdgpu_device* adev; } ;
struct amdgpu_job {int /*<<< orphan*/  sync; struct amdgpu_ib* ibs; } ;
struct amdgpu_ib {int* ptr; int length_dw; } ;
struct TYPE_5__ {int /*<<< orphan*/  entity; int /*<<< orphan*/  address_64_bit; } ;
struct amdgpu_device {scalar_t__ asic_type; unsigned int*** reg_offset; TYPE_2__ uvd; } ;
struct TYPE_4__ {int /*<<< orphan*/  resv; } ;
struct TYPE_6__ {TYPE_1__ base; } ;
struct amdgpu_bo {TYPE_3__ tbo; int /*<<< orphan*/  placement; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_FENCE_OWNER_UNDEFINED ; 
 int /*<<< orphan*/  AMDGPU_GEM_DOMAIN_VRAM ; 
 scalar_t__ CHIP_VEGA10 ; 
 long ETIMEDOUT ; 
 void* PACKET0 (scalar_t__,int /*<<< orphan*/ ) ; 
 unsigned int UVD_BASE_SI ; 
 scalar_t__ UVD_GPCOM_VCPU_CMD ; 
 scalar_t__ UVD_GPCOM_VCPU_DATA0 ; 
 scalar_t__ UVD_GPCOM_VCPU_DATA1 ; 
 size_t UVD_HWIP ; 
 scalar_t__ UVD_NO_OP ; 
 int /*<<< orphan*/  amdgpu_bo_fence (struct amdgpu_bo*,struct dma_fence*,int) ; 
 int amdgpu_bo_gpu_offset (struct amdgpu_bo*) ; 
 int /*<<< orphan*/  amdgpu_bo_kunmap (struct amdgpu_bo*) ; 
 int /*<<< orphan*/  amdgpu_bo_placement_from_domain (struct amdgpu_bo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_bo_unpin (struct amdgpu_bo*) ; 
 int /*<<< orphan*/  amdgpu_bo_unref (struct amdgpu_bo**) ; 
 int /*<<< orphan*/  amdgpu_bo_unreserve (struct amdgpu_bo*) ; 
 long amdgpu_job_alloc_with_ib (struct amdgpu_device*,int,struct amdgpu_job**) ; 
 int /*<<< orphan*/  amdgpu_job_free (struct amdgpu_job*) ; 
 long amdgpu_job_submit (struct amdgpu_job*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct dma_fence**) ; 
 long amdgpu_job_submit_direct (struct amdgpu_job*,struct amdgpu_ring*,struct dma_fence**) ; 
 long amdgpu_sync_resv (struct amdgpu_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  amdgpu_uvd_force_into_uvd_segment (struct amdgpu_bo*) ; 
 struct dma_fence* dma_fence_get (struct dma_fence*) ; 
 int /*<<< orphan*/  dma_fence_put (struct dma_fence*) ; 
 long dma_resv_wait_timeout_rcu (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 long ttm_bo_validate (TYPE_3__*,int /*<<< orphan*/ *,struct ttm_operation_ctx*) ; 

__attribute__((used)) static int amdgpu_uvd_send_msg(struct amdgpu_ring *ring, struct amdgpu_bo *bo,
			       bool direct, struct dma_fence **fence)
{
	struct amdgpu_device *adev = ring->adev;
	struct dma_fence *f = NULL;
	struct amdgpu_job *job;
	struct amdgpu_ib *ib;
	uint32_t data[4];
	uint64_t addr;
	long r;
	int i;
	unsigned offset_idx = 0;
	unsigned offset[3] = { UVD_BASE_SI, 0, 0 };

	amdgpu_bo_kunmap(bo);
	amdgpu_bo_unpin(bo);

	if (!ring->adev->uvd.address_64_bit) {
		struct ttm_operation_ctx ctx = { true, false };

		amdgpu_bo_placement_from_domain(bo, AMDGPU_GEM_DOMAIN_VRAM);
		amdgpu_uvd_force_into_uvd_segment(bo);
		r = ttm_bo_validate(&bo->tbo, &bo->placement, &ctx);
		if (r)
			goto err;
	}

	r = amdgpu_job_alloc_with_ib(adev, 64, &job);
	if (r)
		goto err;

	if (adev->asic_type >= CHIP_VEGA10) {
		offset_idx = 1 + ring->me;
		offset[1] = adev->reg_offset[UVD_HWIP][0][1];
		offset[2] = adev->reg_offset[UVD_HWIP][1][1];
	}

	data[0] = PACKET0(offset[offset_idx] + UVD_GPCOM_VCPU_DATA0, 0);
	data[1] = PACKET0(offset[offset_idx] + UVD_GPCOM_VCPU_DATA1, 0);
	data[2] = PACKET0(offset[offset_idx] + UVD_GPCOM_VCPU_CMD, 0);
	data[3] = PACKET0(offset[offset_idx] + UVD_NO_OP, 0);

	ib = &job->ibs[0];
	addr = amdgpu_bo_gpu_offset(bo);
	ib->ptr[0] = data[0];
	ib->ptr[1] = addr;
	ib->ptr[2] = data[1];
	ib->ptr[3] = addr >> 32;
	ib->ptr[4] = data[2];
	ib->ptr[5] = 0;
	for (i = 6; i < 16; i += 2) {
		ib->ptr[i] = data[3];
		ib->ptr[i+1] = 0;
	}
	ib->length_dw = 16;

	if (direct) {
		r = dma_resv_wait_timeout_rcu(bo->tbo.base.resv,
							true, false,
							msecs_to_jiffies(10));
		if (r == 0)
			r = -ETIMEDOUT;
		if (r < 0)
			goto err_free;

		r = amdgpu_job_submit_direct(job, ring, &f);
		if (r)
			goto err_free;
	} else {
		r = amdgpu_sync_resv(adev, &job->sync, bo->tbo.base.resv,
				     AMDGPU_FENCE_OWNER_UNDEFINED, false);
		if (r)
			goto err_free;

		r = amdgpu_job_submit(job, &adev->uvd.entity,
				      AMDGPU_FENCE_OWNER_UNDEFINED, &f);
		if (r)
			goto err_free;
	}

	amdgpu_bo_fence(bo, f, false);
	amdgpu_bo_unreserve(bo);
	amdgpu_bo_unref(&bo);

	if (fence)
		*fence = dma_fence_get(f);
	dma_fence_put(f);

	return 0;

err_free:
	amdgpu_job_free(job);

err:
	amdgpu_bo_unreserve(bo);
	amdgpu_bo_unref(&bo);
	return r;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint64_t ;
struct dma_fence {int dummy; } ;
struct amdgpu_ring {struct amdgpu_device* adev; } ;
struct amdgpu_job {struct amdgpu_ib* ibs; } ;
struct amdgpu_ib {int* ptr; int length_dw; } ;
struct amdgpu_device {int dummy; } ;
struct amdgpu_bo {int dummy; } ;

/* Variables and functions */
 void* PACKET0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOC15_REG_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UVD ; 
 int /*<<< orphan*/  amdgpu_bo_fence (struct amdgpu_bo*,struct dma_fence*,int) ; 
 int amdgpu_bo_gpu_offset (struct amdgpu_bo*) ; 
 int /*<<< orphan*/  amdgpu_bo_unref (struct amdgpu_bo**) ; 
 int /*<<< orphan*/  amdgpu_bo_unreserve (struct amdgpu_bo*) ; 
 int amdgpu_job_alloc_with_ib (struct amdgpu_device*,int,struct amdgpu_job**) ; 
 int /*<<< orphan*/  amdgpu_job_free (struct amdgpu_job*) ; 
 int amdgpu_job_submit_direct (struct amdgpu_job*,struct amdgpu_ring*,struct dma_fence**) ; 
 struct dma_fence* dma_fence_get (struct dma_fence*) ; 
 int /*<<< orphan*/  dma_fence_put (struct dma_fence*) ; 
 int /*<<< orphan*/  mmUVD_GPCOM_VCPU_CMD ; 
 int /*<<< orphan*/  mmUVD_GPCOM_VCPU_DATA0 ; 
 int /*<<< orphan*/  mmUVD_GPCOM_VCPU_DATA1 ; 
 int /*<<< orphan*/  mmUVD_NO_OP ; 

__attribute__((used)) static int amdgpu_vcn_dec_send_msg(struct amdgpu_ring *ring,
				   struct amdgpu_bo *bo,
				   struct dma_fence **fence)
{
	struct amdgpu_device *adev = ring->adev;
	struct dma_fence *f = NULL;
	struct amdgpu_job *job;
	struct amdgpu_ib *ib;
	uint64_t addr;
	int i, r;

	r = amdgpu_job_alloc_with_ib(adev, 64, &job);
	if (r)
		goto err;

	ib = &job->ibs[0];
	addr = amdgpu_bo_gpu_offset(bo);
	ib->ptr[0] = PACKET0(SOC15_REG_OFFSET(UVD, 0, mmUVD_GPCOM_VCPU_DATA0), 0);
	ib->ptr[1] = addr;
	ib->ptr[2] = PACKET0(SOC15_REG_OFFSET(UVD, 0, mmUVD_GPCOM_VCPU_DATA1), 0);
	ib->ptr[3] = addr >> 32;
	ib->ptr[4] = PACKET0(SOC15_REG_OFFSET(UVD, 0, mmUVD_GPCOM_VCPU_CMD), 0);
	ib->ptr[5] = 0;
	for (i = 6; i < 16; i += 2) {
		ib->ptr[i] = PACKET0(SOC15_REG_OFFSET(UVD, 0, mmUVD_NO_OP), 0);
		ib->ptr[i+1] = 0;
	}
	ib->length_dw = 16;

	r = amdgpu_job_submit_direct(job, ring, &f);
	if (r)
		goto err_free;

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
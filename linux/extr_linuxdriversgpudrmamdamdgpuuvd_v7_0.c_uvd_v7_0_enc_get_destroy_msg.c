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
typedef  int uint64_t ;
typedef  int uint32_t ;
struct dma_fence {int dummy; } ;
struct amdgpu_ring {TYPE_2__* adev; } ;
struct amdgpu_job {struct amdgpu_ib* ibs; } ;
struct amdgpu_ib {int gpu_addr; int length_dw; int* ptr; } ;
struct TYPE_3__ {int /*<<< orphan*/  entity; } ;
struct TYPE_4__ {TYPE_1__ vce; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_FENCE_OWNER_UNDEFINED ; 
 int amdgpu_job_alloc_with_ib (TYPE_2__*,unsigned int const,struct amdgpu_job**) ; 
 int /*<<< orphan*/  amdgpu_job_free (struct amdgpu_job*) ; 
 int amdgpu_job_submit (struct amdgpu_job*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct dma_fence**) ; 
 int amdgpu_job_submit_direct (struct amdgpu_job*,struct amdgpu_ring*,struct dma_fence**) ; 
 struct dma_fence* dma_fence_get (struct dma_fence*) ; 
 int /*<<< orphan*/  dma_fence_put (struct dma_fence*) ; 
 int upper_32_bits (int) ; 

int uvd_v7_0_enc_get_destroy_msg(struct amdgpu_ring *ring, uint32_t handle,
				 bool direct, struct dma_fence **fence)
{
	const unsigned ib_size_dw = 16;
	struct amdgpu_job *job;
	struct amdgpu_ib *ib;
	struct dma_fence *f = NULL;
	uint64_t dummy;
	int i, r;

	r = amdgpu_job_alloc_with_ib(ring->adev, ib_size_dw * 4, &job);
	if (r)
		return r;

	ib = &job->ibs[0];
	dummy = ib->gpu_addr + 1024;

	ib->length_dw = 0;
	ib->ptr[ib->length_dw++] = 0x00000018;
	ib->ptr[ib->length_dw++] = 0x00000001;
	ib->ptr[ib->length_dw++] = handle;
	ib->ptr[ib->length_dw++] = 0x00000000;
	ib->ptr[ib->length_dw++] = upper_32_bits(dummy);
	ib->ptr[ib->length_dw++] = dummy;

	ib->ptr[ib->length_dw++] = 0x00000014;
	ib->ptr[ib->length_dw++] = 0x00000002;
	ib->ptr[ib->length_dw++] = 0x0000001c;
	ib->ptr[ib->length_dw++] = 0x00000000;
	ib->ptr[ib->length_dw++] = 0x00000000;

	ib->ptr[ib->length_dw++] = 0x00000008;
	ib->ptr[ib->length_dw++] = 0x08000002; /* op close session */

	for (i = ib->length_dw; i < ib_size_dw; ++i)
		ib->ptr[i] = 0x0;

	if (direct)
		r = amdgpu_job_submit_direct(job, ring, &f);
	else
		r = amdgpu_job_submit(job, &ring->adev->vce.entity,
				      AMDGPU_FENCE_OWNER_UNDEFINED, &f);
	if (r)
		goto err;

	if (fence)
		*fence = dma_fence_get(f);
	dma_fence_put(f);
	return 0;

err:
	amdgpu_job_free(job);
	return r;
}
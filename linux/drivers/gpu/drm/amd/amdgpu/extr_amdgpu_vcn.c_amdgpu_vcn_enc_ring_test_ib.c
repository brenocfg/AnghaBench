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
struct dma_fence {int dummy; } ;
struct amdgpu_ring {int /*<<< orphan*/  adev; } ;
struct amdgpu_bo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_GEM_DOMAIN_VRAM ; 
 long ETIMEDOUT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 long amdgpu_bo_create_reserved (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct amdgpu_bo**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amdgpu_bo_unref (struct amdgpu_bo**) ; 
 int /*<<< orphan*/  amdgpu_bo_unreserve (struct amdgpu_bo*) ; 
 long amdgpu_vcn_enc_get_create_msg (struct amdgpu_ring*,int,struct amdgpu_bo*,int /*<<< orphan*/ *) ; 
 long amdgpu_vcn_enc_get_destroy_msg (struct amdgpu_ring*,int,struct amdgpu_bo*,struct dma_fence**) ; 
 int /*<<< orphan*/  dma_fence_put (struct dma_fence*) ; 
 long dma_fence_wait_timeout (struct dma_fence*,int,long) ; 

int amdgpu_vcn_enc_ring_test_ib(struct amdgpu_ring *ring, long timeout)
{
	struct dma_fence *fence = NULL;
	struct amdgpu_bo *bo = NULL;
	long r;

	r = amdgpu_bo_create_reserved(ring->adev, 128 * 1024, PAGE_SIZE,
				      AMDGPU_GEM_DOMAIN_VRAM,
				      &bo, NULL, NULL);
	if (r)
		return r;

	r = amdgpu_vcn_enc_get_create_msg(ring, 1, bo, NULL);
	if (r)
		goto error;

	r = amdgpu_vcn_enc_get_destroy_msg(ring, 1, bo, &fence);
	if (r)
		goto error;

	r = dma_fence_wait_timeout(fence, false, timeout);
	if (r == 0)
		r = -ETIMEDOUT;
	else if (r > 0)
		r = 0;

error:
	dma_fence_put(fence);
	amdgpu_bo_unreserve(bo);
	amdgpu_bo_unref(&bo);
	return r;
}
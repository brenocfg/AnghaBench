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
struct dma_fence {int dummy; } ;
struct amdgpu_ring {TYPE_2__* adev; } ;
struct amdgpu_bo {int dummy; } ;
struct TYPE_3__ {struct amdgpu_ring* ring; } ;
struct TYPE_4__ {TYPE_1__ vce; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_GEM_DOMAIN_VRAM ; 
 long ETIMEDOUT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 long amdgpu_bo_create_reserved (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct amdgpu_bo**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amdgpu_bo_unref (struct amdgpu_bo**) ; 
 int /*<<< orphan*/  amdgpu_bo_unreserve (struct amdgpu_bo*) ; 
 long amdgpu_vce_get_create_msg (struct amdgpu_ring*,int,struct amdgpu_bo*,int /*<<< orphan*/ *) ; 
 long amdgpu_vce_get_destroy_msg (struct amdgpu_ring*,int,int,struct dma_fence**) ; 
 int /*<<< orphan*/  dma_fence_put (struct dma_fence*) ; 
 long dma_fence_wait_timeout (struct dma_fence*,int,long) ; 

int amdgpu_vce_ring_test_ib(struct amdgpu_ring *ring, long timeout)
{
	struct dma_fence *fence = NULL;
	struct amdgpu_bo *bo = NULL;
	long r;

	/* skip vce ring1/2 ib test for now, since it's not reliable */
	if (ring != &ring->adev->vce.ring[0])
		return 0;

	r = amdgpu_bo_create_reserved(ring->adev, 512, PAGE_SIZE,
				      AMDGPU_GEM_DOMAIN_VRAM,
				      &bo, NULL, NULL);
	if (r)
		return r;

	r = amdgpu_vce_get_create_msg(ring, 1, bo, NULL);
	if (r)
		goto error;

	r = amdgpu_vce_get_destroy_msg(ring, 1, true, &fence);
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
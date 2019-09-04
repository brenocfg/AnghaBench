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
struct amdgpu_ring {int /*<<< orphan*/  idx; TYPE_2__* adev; } ;
struct TYPE_3__ {struct amdgpu_ring* ring; } ;
struct TYPE_4__ {TYPE_1__ vce; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 long ETIMEDOUT ; 
 long amdgpu_vce_get_create_msg (struct amdgpu_ring*,int,int /*<<< orphan*/ *) ; 
 long amdgpu_vce_get_destroy_msg (struct amdgpu_ring*,int,int,struct dma_fence**) ; 
 int /*<<< orphan*/  dma_fence_put (struct dma_fence*) ; 
 long dma_fence_wait_timeout (struct dma_fence*,int,long) ; 

int amdgpu_vce_ring_test_ib(struct amdgpu_ring *ring, long timeout)
{
	struct dma_fence *fence = NULL;
	long r;

	/* skip vce ring1/2 ib test for now, since it's not reliable */
	if (ring != &ring->adev->vce.ring[0])
		return 0;

	r = amdgpu_vce_get_create_msg(ring, 1, NULL);
	if (r) {
		DRM_ERROR("amdgpu: failed to get create msg (%ld).\n", r);
		goto error;
	}

	r = amdgpu_vce_get_destroy_msg(ring, 1, true, &fence);
	if (r) {
		DRM_ERROR("amdgpu: failed to get destroy ib (%ld).\n", r);
		goto error;
	}

	r = dma_fence_wait_timeout(fence, false, timeout);
	if (r == 0) {
		DRM_ERROR("amdgpu: IB test timed out.\n");
		r = -ETIMEDOUT;
	} else if (r < 0) {
		DRM_ERROR("amdgpu: fence wait failed (%ld).\n", r);
	} else {
		DRM_DEBUG("ib test on ring %d succeeded\n", ring->idx);
		r = 0;
	}
error:
	dma_fence_put(fence);
	return r;
}
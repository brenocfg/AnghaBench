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
struct amdgpu_ring {int /*<<< orphan*/  idx; int /*<<< orphan*/  me; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ,...) ; 
 long ETIMEDOUT ; 
 int /*<<< orphan*/  dma_fence_put (struct dma_fence*) ; 
 long dma_fence_wait_timeout (struct dma_fence*,int,long) ; 
 long uvd_v7_0_enc_get_create_msg (struct amdgpu_ring*,int,int /*<<< orphan*/ *) ; 
 long uvd_v7_0_enc_get_destroy_msg (struct amdgpu_ring*,int,int,struct dma_fence**) ; 

__attribute__((used)) static int uvd_v7_0_enc_ring_test_ib(struct amdgpu_ring *ring, long timeout)
{
	struct dma_fence *fence = NULL;
	long r;

	r = uvd_v7_0_enc_get_create_msg(ring, 1, NULL);
	if (r) {
		DRM_ERROR("amdgpu: (%d)failed to get create msg (%ld).\n", ring->me, r);
		goto error;
	}

	r = uvd_v7_0_enc_get_destroy_msg(ring, 1, true, &fence);
	if (r) {
		DRM_ERROR("amdgpu: (%d)failed to get destroy ib (%ld).\n", ring->me, r);
		goto error;
	}

	r = dma_fence_wait_timeout(fence, false, timeout);
	if (r == 0) {
		DRM_ERROR("amdgpu: (%d)IB test timed out.\n", ring->me);
		r = -ETIMEDOUT;
	} else if (r < 0) {
		DRM_ERROR("amdgpu: (%d)fence wait failed (%ld).\n", ring->me, r);
	} else {
		DRM_DEBUG("ib test on (%d)ring %d succeeded\n", ring->me, ring->idx);
		r = 0;
	}
error:
	dma_fence_put(fence);
	return r;
}
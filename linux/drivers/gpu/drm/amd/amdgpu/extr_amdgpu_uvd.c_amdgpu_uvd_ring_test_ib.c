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
struct amdgpu_ring {int dummy; } ;

/* Variables and functions */
 long ETIMEDOUT ; 
 long amdgpu_uvd_get_create_msg (struct amdgpu_ring*,int,int /*<<< orphan*/ *) ; 
 long amdgpu_uvd_get_destroy_msg (struct amdgpu_ring*,int,int,struct dma_fence**) ; 
 int /*<<< orphan*/  dma_fence_put (struct dma_fence*) ; 
 long dma_fence_wait_timeout (struct dma_fence*,int,long) ; 

int amdgpu_uvd_ring_test_ib(struct amdgpu_ring *ring, long timeout)
{
	struct dma_fence *fence;
	long r;

	r = amdgpu_uvd_get_create_msg(ring, 1, NULL);
	if (r)
		goto error;

	r = amdgpu_uvd_get_destroy_msg(ring, 1, true, &fence);
	if (r)
		goto error;

	r = dma_fence_wait_timeout(fence, false, timeout);
	if (r == 0)
		r = -ETIMEDOUT;
	else if (r > 0)
		r = 0;

	dma_fence_put(fence);

error:
	return r;
}
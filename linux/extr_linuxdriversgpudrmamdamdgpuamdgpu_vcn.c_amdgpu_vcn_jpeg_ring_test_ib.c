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
typedef  int uint32_t ;
struct dma_fence {int dummy; } ;
struct amdgpu_ring {int /*<<< orphan*/  idx; struct amdgpu_device* adev; } ;
struct amdgpu_device {unsigned int usec_timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int /*<<< orphan*/  DRM_UDELAY (int) ; 
 long EINVAL ; 
 long ETIMEDOUT ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOC15_REG_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UVD ; 
 long amdgpu_vcn_jpeg_set_reg (struct amdgpu_ring*,int,struct dma_fence**) ; 
 int /*<<< orphan*/  dma_fence_put (struct dma_fence*) ; 
 long dma_fence_wait_timeout (struct dma_fence*,int,long) ; 
 int /*<<< orphan*/  mmUVD_JPEG_PITCH ; 

int amdgpu_vcn_jpeg_ring_test_ib(struct amdgpu_ring *ring, long timeout)
{
	struct amdgpu_device *adev = ring->adev;
	uint32_t tmp = 0;
	unsigned i;
	struct dma_fence *fence = NULL;
	long r = 0;

	r = amdgpu_vcn_jpeg_set_reg(ring, 1, &fence);
	if (r) {
		DRM_ERROR("amdgpu: failed to set jpeg register (%ld).\n", r);
		goto error;
	}

	r = dma_fence_wait_timeout(fence, false, timeout);
	if (r == 0) {
		DRM_ERROR("amdgpu: IB test timed out.\n");
		r = -ETIMEDOUT;
		goto error;
	} else if (r < 0) {
		DRM_ERROR("amdgpu: fence wait failed (%ld).\n", r);
		goto error;
	} else
		r = 0;

	for (i = 0; i < adev->usec_timeout; i++) {
		tmp = RREG32(SOC15_REG_OFFSET(UVD, 0, mmUVD_JPEG_PITCH));
		if (tmp == 0xDEADBEEF)
			break;
		DRM_UDELAY(1);
	}

	if (i < adev->usec_timeout)
		DRM_DEBUG("ib test on ring %d succeeded\n", ring->idx);
	else {
		DRM_ERROR("ib test failed (0x%08X)\n", tmp);
		r = -EINVAL;
	}

	dma_fence_put(fence);

error:
	return r;
}
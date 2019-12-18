#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct radeon_ring {int /*<<< orphan*/  idx; } ;
struct radeon_ib {int* ptr; int length_dw; TYPE_1__* fence; } ;
struct radeon_device {unsigned int usec_timeout; } ;
struct TYPE_2__ {int /*<<< orphan*/  ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int /*<<< orphan*/  DRM_INFO (char*,int /*<<< orphan*/ ,unsigned int) ; 
 int EINVAL ; 
 int ETIMEDOUT ; 
 int PACKET3 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PACKET3_SET_UCONFIG_REG ; 
 int PACKET3_SET_UCONFIG_REG_START ; 
 int /*<<< orphan*/  RADEON_USEC_IB_TEST_TIMEOUT ; 
 int RREG32 (int) ; 
 int /*<<< orphan*/  WREG32 (int,int) ; 
 int radeon_fence_wait_timeout (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_ib_free (struct radeon_device*,struct radeon_ib*) ; 
 int radeon_ib_get (struct radeon_device*,int /*<<< orphan*/ ,struct radeon_ib*,int /*<<< orphan*/ *,int) ; 
 int radeon_ib_schedule (struct radeon_device*,struct radeon_ib*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  radeon_scratch_free (struct radeon_device*,int) ; 
 int radeon_scratch_get (struct radeon_device*,int*) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  usecs_to_jiffies (int /*<<< orphan*/ ) ; 

int cik_ib_test(struct radeon_device *rdev, struct radeon_ring *ring)
{
	struct radeon_ib ib;
	uint32_t scratch;
	uint32_t tmp = 0;
	unsigned i;
	int r;

	r = radeon_scratch_get(rdev, &scratch);
	if (r) {
		DRM_ERROR("radeon: failed to get scratch reg (%d).\n", r);
		return r;
	}
	WREG32(scratch, 0xCAFEDEAD);
	r = radeon_ib_get(rdev, ring->idx, &ib, NULL, 256);
	if (r) {
		DRM_ERROR("radeon: failed to get ib (%d).\n", r);
		radeon_scratch_free(rdev, scratch);
		return r;
	}
	ib.ptr[0] = PACKET3(PACKET3_SET_UCONFIG_REG, 1);
	ib.ptr[1] = ((scratch - PACKET3_SET_UCONFIG_REG_START) >> 2);
	ib.ptr[2] = 0xDEADBEEF;
	ib.length_dw = 3;
	r = radeon_ib_schedule(rdev, &ib, NULL, false);
	if (r) {
		radeon_scratch_free(rdev, scratch);
		radeon_ib_free(rdev, &ib);
		DRM_ERROR("radeon: failed to schedule ib (%d).\n", r);
		return r;
	}
	r = radeon_fence_wait_timeout(ib.fence, false, usecs_to_jiffies(
		RADEON_USEC_IB_TEST_TIMEOUT));
	if (r < 0) {
		DRM_ERROR("radeon: fence wait failed (%d).\n", r);
		radeon_scratch_free(rdev, scratch);
		radeon_ib_free(rdev, &ib);
		return r;
	} else if (r == 0) {
		DRM_ERROR("radeon: fence wait timed out.\n");
		radeon_scratch_free(rdev, scratch);
		radeon_ib_free(rdev, &ib);
		return -ETIMEDOUT;
	}
	r = 0;
	for (i = 0; i < rdev->usec_timeout; i++) {
		tmp = RREG32(scratch);
		if (tmp == 0xDEADBEEF)
			break;
		udelay(1);
	}
	if (i < rdev->usec_timeout) {
		DRM_INFO("ib test on ring %d succeeded in %u usecs\n", ib.fence->ring, i);
	} else {
		DRM_ERROR("radeon: ib test failed (scratch(0x%04X)=0x%08X)\n",
			  scratch, tmp);
		r = -EINVAL;
	}
	radeon_scratch_free(rdev, scratch);
	radeon_ib_free(rdev, &ib);
	return r;
}
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
struct radeon_ring {int dummy; } ;
struct radeon_ib {int* ptr; int length_dw; int /*<<< orphan*/  fence; } ;
struct radeon_device {unsigned int usec_timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int /*<<< orphan*/  DRM_INFO (char*,unsigned int) ; 
 int EINVAL ; 
 int ETIMEDOUT ; 
 int PACKET0 (int,int /*<<< orphan*/ ) ; 
 void* PACKET2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RADEON_RING_TYPE_GFX_INDEX ; 
 int /*<<< orphan*/  RADEON_USEC_IB_TEST_TIMEOUT ; 
 int RREG32 (int) ; 
 int /*<<< orphan*/  WREG32 (int,int) ; 
 int radeon_fence_wait_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_ib_free (struct radeon_device*,struct radeon_ib*) ; 
 int radeon_ib_get (struct radeon_device*,int /*<<< orphan*/ ,struct radeon_ib*,int /*<<< orphan*/ *,int) ; 
 int radeon_ib_schedule (struct radeon_device*,struct radeon_ib*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  radeon_scratch_free (struct radeon_device*,int) ; 
 int radeon_scratch_get (struct radeon_device*,int*) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  usecs_to_jiffies (int /*<<< orphan*/ ) ; 

int r100_ib_test(struct radeon_device *rdev, struct radeon_ring *ring)
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
	r = radeon_ib_get(rdev, RADEON_RING_TYPE_GFX_INDEX, &ib, NULL, 256);
	if (r) {
		DRM_ERROR("radeon: failed to get ib (%d).\n", r);
		goto free_scratch;
	}
	ib.ptr[0] = PACKET0(scratch, 0);
	ib.ptr[1] = 0xDEADBEEF;
	ib.ptr[2] = PACKET2(0);
	ib.ptr[3] = PACKET2(0);
	ib.ptr[4] = PACKET2(0);
	ib.ptr[5] = PACKET2(0);
	ib.ptr[6] = PACKET2(0);
	ib.ptr[7] = PACKET2(0);
	ib.length_dw = 8;
	r = radeon_ib_schedule(rdev, &ib, NULL, false);
	if (r) {
		DRM_ERROR("radeon: failed to schedule ib (%d).\n", r);
		goto free_ib;
	}
	r = radeon_fence_wait_timeout(ib.fence, false, usecs_to_jiffies(
		RADEON_USEC_IB_TEST_TIMEOUT));
	if (r < 0) {
		DRM_ERROR("radeon: fence wait failed (%d).\n", r);
		goto free_ib;
	} else if (r == 0) {
		DRM_ERROR("radeon: fence wait timed out.\n");
		r = -ETIMEDOUT;
		goto free_ib;
	}
	r = 0;
	for (i = 0; i < rdev->usec_timeout; i++) {
		tmp = RREG32(scratch);
		if (tmp == 0xDEADBEEF) {
			break;
		}
		udelay(1);
	}
	if (i < rdev->usec_timeout) {
		DRM_INFO("ib test succeeded in %u usecs\n", i);
	} else {
		DRM_ERROR("radeon: ib test failed (scratch(0x%04X)=0x%08X)\n",
			  scratch, tmp);
		r = -EINVAL;
	}
free_ib:
	radeon_ib_free(rdev, &ib);
free_scratch:
	radeon_scratch_free(rdev, scratch);
	return r;
}
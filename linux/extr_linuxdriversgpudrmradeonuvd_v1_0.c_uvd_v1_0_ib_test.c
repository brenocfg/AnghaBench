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
struct radeon_ring {int /*<<< orphan*/  idx; } ;
struct radeon_fence {int dummy; } ;
struct radeon_device {scalar_t__ family; } ;

/* Variables and functions */
 scalar_t__ CHIP_RV740 ; 
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int /*<<< orphan*/  DRM_INFO (char*,int /*<<< orphan*/ ) ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  RADEON_USEC_IB_TEST_TIMEOUT ; 
 int /*<<< orphan*/  radeon_fence_unref (struct radeon_fence**) ; 
 int radeon_fence_wait_timeout (struct radeon_fence*,int,int /*<<< orphan*/ ) ; 
 int radeon_set_uvd_clocks (struct radeon_device*,int,int) ; 
 int radeon_uvd_get_create_msg (struct radeon_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int radeon_uvd_get_destroy_msg (struct radeon_device*,int /*<<< orphan*/ ,int,struct radeon_fence**) ; 
 int /*<<< orphan*/  usecs_to_jiffies (int /*<<< orphan*/ ) ; 

int uvd_v1_0_ib_test(struct radeon_device *rdev, struct radeon_ring *ring)
{
	struct radeon_fence *fence = NULL;
	int r;

	if (rdev->family < CHIP_RV740)
		r = radeon_set_uvd_clocks(rdev, 10000, 10000);
	else
		r = radeon_set_uvd_clocks(rdev, 53300, 40000);
	if (r) {
		DRM_ERROR("radeon: failed to raise UVD clocks (%d).\n", r);
		return r;
	}

	r = radeon_uvd_get_create_msg(rdev, ring->idx, 1, NULL);
	if (r) {
		DRM_ERROR("radeon: failed to get create msg (%d).\n", r);
		goto error;
	}

	r = radeon_uvd_get_destroy_msg(rdev, ring->idx, 1, &fence);
	if (r) {
		DRM_ERROR("radeon: failed to get destroy ib (%d).\n", r);
		goto error;
	}

	r = radeon_fence_wait_timeout(fence, false, usecs_to_jiffies(
		RADEON_USEC_IB_TEST_TIMEOUT));
	if (r < 0) {
		DRM_ERROR("radeon: fence wait failed (%d).\n", r);
		goto error;
	} else if (r == 0) {
		DRM_ERROR("radeon: fence wait timed out.\n");
		r = -ETIMEDOUT;
		goto error;
	}
	r = 0;
	DRM_INFO("ib test on ring %d succeeded\n",  ring->idx);
error:
	radeon_fence_unref(&fence);
	radeon_set_uvd_clocks(rdev, 0, 0);
	return r;
}
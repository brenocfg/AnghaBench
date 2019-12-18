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
struct radeon_ring {int /*<<< orphan*/  idx; } ;
struct radeon_device {unsigned int usec_timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DRM_INFO (char*,int /*<<< orphan*/ ,unsigned int) ; 
 int EINVAL ; 
 int PACKET0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UVD_CONTEXT_ID ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int radeon_ring_lock (struct radeon_device*,struct radeon_ring*,int) ; 
 int /*<<< orphan*/  radeon_ring_unlock_commit (struct radeon_device*,struct radeon_ring*,int) ; 
 int /*<<< orphan*/  radeon_ring_write (struct radeon_ring*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

int uvd_v1_0_ring_test(struct radeon_device *rdev, struct radeon_ring *ring)
{
	uint32_t tmp = 0;
	unsigned i;
	int r;

	WREG32(UVD_CONTEXT_ID, 0xCAFEDEAD);
	r = radeon_ring_lock(rdev, ring, 3);
	if (r) {
		DRM_ERROR("radeon: cp failed to lock ring %d (%d).\n",
			  ring->idx, r);
		return r;
	}
	radeon_ring_write(ring, PACKET0(UVD_CONTEXT_ID, 0));
	radeon_ring_write(ring, 0xDEADBEEF);
	radeon_ring_unlock_commit(rdev, ring, false);
	for (i = 0; i < rdev->usec_timeout; i++) {
		tmp = RREG32(UVD_CONTEXT_ID);
		if (tmp == 0xDEADBEEF)
			break;
		udelay(1);
	}

	if (i < rdev->usec_timeout) {
		DRM_INFO("ring test on %d succeeded in %d usecs\n",
			 ring->idx, i);
	} else {
		DRM_ERROR("radeon: ring %d test failed (0x%08X)\n",
			  ring->idx, tmp);
		r = -EINVAL;
	}
	return r;
}
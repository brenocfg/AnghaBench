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
 int /*<<< orphan*/  DRM_ERROR (char*,int,...) ; 
 int /*<<< orphan*/  DRM_INFO (char*,int /*<<< orphan*/ ,unsigned int) ; 
 int EINVAL ; 
 int PACKET3 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PACKET3_SET_UCONFIG_REG ; 
 int PACKET3_SET_UCONFIG_REG_START ; 
 int RREG32 (int) ; 
 int /*<<< orphan*/  WREG32 (int,int) ; 
 int radeon_ring_lock (struct radeon_device*,struct radeon_ring*,int) ; 
 int /*<<< orphan*/  radeon_ring_unlock_commit (struct radeon_device*,struct radeon_ring*,int) ; 
 int /*<<< orphan*/  radeon_ring_write (struct radeon_ring*,int) ; 
 int /*<<< orphan*/  radeon_scratch_free (struct radeon_device*,int) ; 
 int radeon_scratch_get (struct radeon_device*,int*) ; 
 int /*<<< orphan*/  udelay (int) ; 

int cik_ring_test(struct radeon_device *rdev, struct radeon_ring *ring)
{
	uint32_t scratch;
	uint32_t tmp = 0;
	unsigned i;
	int r;

	r = radeon_scratch_get(rdev, &scratch);
	if (r) {
		DRM_ERROR("radeon: cp failed to get scratch reg (%d).\n", r);
		return r;
	}
	WREG32(scratch, 0xCAFEDEAD);
	r = radeon_ring_lock(rdev, ring, 3);
	if (r) {
		DRM_ERROR("radeon: cp failed to lock ring %d (%d).\n", ring->idx, r);
		radeon_scratch_free(rdev, scratch);
		return r;
	}
	radeon_ring_write(ring, PACKET3(PACKET3_SET_UCONFIG_REG, 1));
	radeon_ring_write(ring, ((scratch - PACKET3_SET_UCONFIG_REG_START) >> 2));
	radeon_ring_write(ring, 0xDEADBEEF);
	radeon_ring_unlock_commit(rdev, ring, false);

	for (i = 0; i < rdev->usec_timeout; i++) {
		tmp = RREG32(scratch);
		if (tmp == 0xDEADBEEF)
			break;
		udelay(1);
	}
	if (i < rdev->usec_timeout) {
		DRM_INFO("ring test on %d succeeded in %d usecs\n", ring->idx, i);
	} else {
		DRM_ERROR("radeon: ring %d test failed (scratch(0x%04X)=0x%08X)\n",
			  ring->idx, scratch, tmp);
		r = -EINVAL;
	}
	radeon_scratch_free(rdev, scratch);
	return r;
}
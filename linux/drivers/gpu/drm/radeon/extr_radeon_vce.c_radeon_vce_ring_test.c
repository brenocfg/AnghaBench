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
typedef  scalar_t__ uint32_t ;
struct radeon_ring {int /*<<< orphan*/  idx; } ;
struct radeon_device {unsigned int usec_timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  DRM_INFO (char*,int /*<<< orphan*/ ,unsigned int) ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  VCE_CMD_END ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int radeon_ring_lock (struct radeon_device*,struct radeon_ring*,int) ; 
 int /*<<< orphan*/  radeon_ring_unlock_commit (struct radeon_device*,struct radeon_ring*,int) ; 
 int /*<<< orphan*/  radeon_ring_write (struct radeon_ring*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 scalar_t__ vce_v1_0_get_rptr (struct radeon_device*,struct radeon_ring*) ; 

int radeon_vce_ring_test(struct radeon_device *rdev, struct radeon_ring *ring)
{
	uint32_t rptr = vce_v1_0_get_rptr(rdev, ring);
	unsigned i;
	int r;

	r = radeon_ring_lock(rdev, ring, 16);
	if (r) {
		DRM_ERROR("radeon: vce failed to lock ring %d (%d).\n",
			  ring->idx, r);
		return r;
	}
	radeon_ring_write(ring, cpu_to_le32(VCE_CMD_END));
	radeon_ring_unlock_commit(rdev, ring, false);

	for (i = 0; i < rdev->usec_timeout; i++) {
		if (vce_v1_0_get_rptr(rdev, ring) != rptr)
			break;
		udelay(1);
	}

	if (i < rdev->usec_timeout) {
		DRM_INFO("ring test on %d succeeded in %d usecs\n",
			 ring->idx, i);
	} else {
		DRM_ERROR("radeon: ring %d test failed\n",
			 ring->idx);
		r = -ETIMEDOUT;
	}

	return r;
}
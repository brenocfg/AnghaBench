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
struct amdgpu_ring {int /*<<< orphan*/  idx; struct amdgpu_device* adev; } ;
struct amdgpu_device {int usec_timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  DRM_UDELAY (int) ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  VCE_CMD_END ; 
 int amdgpu_ring_alloc (struct amdgpu_ring*,int) ; 
 int /*<<< orphan*/  amdgpu_ring_commit (struct amdgpu_ring*) ; 
 scalar_t__ amdgpu_ring_get_rptr (struct amdgpu_ring*) ; 
 int /*<<< orphan*/  amdgpu_ring_write (struct amdgpu_ring*,int /*<<< orphan*/ ) ; 
 scalar_t__ amdgpu_sriov_vf (struct amdgpu_device*) ; 

int amdgpu_vce_ring_test_ring(struct amdgpu_ring *ring)
{
	struct amdgpu_device *adev = ring->adev;
	uint32_t rptr = amdgpu_ring_get_rptr(ring);
	unsigned i;
	int r, timeout = adev->usec_timeout;

	/* skip ring test for sriov*/
	if (amdgpu_sriov_vf(adev))
		return 0;

	r = amdgpu_ring_alloc(ring, 16);
	if (r) {
		DRM_ERROR("amdgpu: vce failed to lock ring %d (%d).\n",
			  ring->idx, r);
		return r;
	}
	amdgpu_ring_write(ring, VCE_CMD_END);
	amdgpu_ring_commit(ring);

	for (i = 0; i < timeout; i++) {
		if (amdgpu_ring_get_rptr(ring) != rptr)
			break;
		DRM_UDELAY(1);
	}

	if (i < timeout) {
		DRM_DEBUG("ring test on %d succeeded in %d usecs\n",
			 ring->idx, i);
	} else {
		DRM_ERROR("amdgpu: ring %d test failed\n",
			  ring->idx);
		r = -ETIMEDOUT;
	}

	return r;
}
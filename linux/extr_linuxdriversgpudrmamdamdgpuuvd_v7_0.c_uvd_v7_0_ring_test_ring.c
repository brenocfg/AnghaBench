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
struct amdgpu_ring {int /*<<< orphan*/  idx; int /*<<< orphan*/  me; struct amdgpu_device* adev; } ;
struct amdgpu_device {unsigned int usec_timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DRM_UDELAY (int) ; 
 int EINVAL ; 
 int PACKET0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int RREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOC15_REG_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UVD ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int amdgpu_ring_alloc (struct amdgpu_ring*,int) ; 
 int /*<<< orphan*/  amdgpu_ring_commit (struct amdgpu_ring*) ; 
 int /*<<< orphan*/  amdgpu_ring_write (struct amdgpu_ring*,int) ; 
 int /*<<< orphan*/  mmUVD_CONTEXT_ID ; 

__attribute__((used)) static int uvd_v7_0_ring_test_ring(struct amdgpu_ring *ring)
{
	struct amdgpu_device *adev = ring->adev;
	uint32_t tmp = 0;
	unsigned i;
	int r;

	WREG32_SOC15(UVD, ring->me, mmUVD_CONTEXT_ID, 0xCAFEDEAD);
	r = amdgpu_ring_alloc(ring, 3);
	if (r) {
		DRM_ERROR("amdgpu: (%d)cp failed to lock ring %d (%d).\n",
			  ring->me, ring->idx, r);
		return r;
	}
	amdgpu_ring_write(ring,
		PACKET0(SOC15_REG_OFFSET(UVD, ring->me, mmUVD_CONTEXT_ID), 0));
	amdgpu_ring_write(ring, 0xDEADBEEF);
	amdgpu_ring_commit(ring);
	for (i = 0; i < adev->usec_timeout; i++) {
		tmp = RREG32_SOC15(UVD, ring->me, mmUVD_CONTEXT_ID);
		if (tmp == 0xDEADBEEF)
			break;
		DRM_UDELAY(1);
	}

	if (i < adev->usec_timeout) {
		DRM_DEBUG("(%d)ring test on %d succeeded in %d usecs\n",
			 ring->me, ring->idx, i);
	} else {
		DRM_ERROR("(%d)amdgpu: ring %d test failed (0x%08X)\n",
			  ring->me, ring->idx, tmp);
		r = -EINVAL;
	}
	return r;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct amdgpu_ring {int ready; TYPE_1__* funcs; } ;
struct TYPE_4__ {struct amdgpu_ring* gfx_ring; } ;
struct amdgpu_device {int accel_working; TYPE_2__ gfx; struct amdgpu_ring** rings; } ;
struct TYPE_3__ {scalar_t__ type; } ;

/* Variables and functions */
 int AMDGPU_IB_TEST_TIMEOUT ; 
 unsigned int AMDGPU_MAX_RINGS ; 
 scalar_t__ AMDGPU_RING_TYPE_UVD ; 
 scalar_t__ AMDGPU_RING_TYPE_UVD_ENC ; 
 scalar_t__ AMDGPU_RING_TYPE_VCE ; 
 scalar_t__ AMDGPU_RING_TYPE_VCN_DEC ; 
 scalar_t__ AMDGPU_RING_TYPE_VCN_ENC ; 
 scalar_t__ AMDGPU_RING_TYPE_VCN_JPEG ; 
 int /*<<< orphan*/  DRM_ERROR (char*,unsigned int,...) ; 
 int amdgpu_ring_test_ib (struct amdgpu_ring*,long) ; 
 scalar_t__ amdgpu_sriov_runtime (struct amdgpu_device*) ; 
 scalar_t__ amdgpu_sriov_vf (struct amdgpu_device*) ; 

int amdgpu_ib_ring_tests(struct amdgpu_device *adev)
{
	unsigned i;
	int r, ret = 0;
	long tmo_gfx, tmo_mm;

	tmo_mm = tmo_gfx = AMDGPU_IB_TEST_TIMEOUT;
	if (amdgpu_sriov_vf(adev)) {
		/* for MM engines in hypervisor side they are not scheduled together
		 * with CP and SDMA engines, so even in exclusive mode MM engine could
		 * still running on other VF thus the IB TEST TIMEOUT for MM engines
		 * under SR-IOV should be set to a long time. 8 sec should be enough
		 * for the MM comes back to this VF.
		 */
		tmo_mm = 8 * AMDGPU_IB_TEST_TIMEOUT;
	}

	if (amdgpu_sriov_runtime(adev)) {
		/* for CP & SDMA engines since they are scheduled together so
		 * need to make the timeout width enough to cover the time
		 * cost waiting for it coming back under RUNTIME only
		*/
		tmo_gfx = 8 * AMDGPU_IB_TEST_TIMEOUT;
	}

	for (i = 0; i < AMDGPU_MAX_RINGS; ++i) {
		struct amdgpu_ring *ring = adev->rings[i];
		long tmo;

		if (!ring || !ring->ready)
			continue;

		/* MM engine need more time */
		if (ring->funcs->type == AMDGPU_RING_TYPE_UVD ||
			ring->funcs->type == AMDGPU_RING_TYPE_VCE ||
			ring->funcs->type == AMDGPU_RING_TYPE_UVD_ENC ||
			ring->funcs->type == AMDGPU_RING_TYPE_VCN_DEC ||
			ring->funcs->type == AMDGPU_RING_TYPE_VCN_ENC ||
			ring->funcs->type == AMDGPU_RING_TYPE_VCN_JPEG)
			tmo = tmo_mm;
		else
			tmo = tmo_gfx;

		r = amdgpu_ring_test_ib(ring, tmo);
		if (r) {
			ring->ready = false;

			if (ring == &adev->gfx.gfx_ring[0]) {
				/* oh, oh, that's really bad */
				DRM_ERROR("amdgpu: failed testing IB on GFX ring (%d).\n", r);
				adev->accel_working = false;
				return r;

			} else {
				/* still not good, but we can live with it */
				DRM_ERROR("amdgpu: failed testing IB on ring %d (%d).\n", i, r);
				ret = r;
			}
		}
	}
	return ret;
}
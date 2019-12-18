#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int ready; } ;
struct amdgpu_ring {int /*<<< orphan*/  name; TYPE_4__ sched; TYPE_3__* funcs; } ;
struct TYPE_10__ {struct amdgpu_ring* gfx_ring; } ;
struct TYPE_6__ {scalar_t__ hive_id; } ;
struct TYPE_7__ {TYPE_1__ xgmi; } ;
struct amdgpu_device {unsigned int num_rings; int accel_working; TYPE_5__ gfx; int /*<<< orphan*/  dev; struct amdgpu_ring** rings; TYPE_2__ gmc; } ;
struct TYPE_8__ {scalar_t__ type; int /*<<< orphan*/  test_ib; } ;

/* Variables and functions */
 long AMDGPU_IB_TEST_GFX_XGMI_TIMEOUT ; 
 int AMDGPU_IB_TEST_TIMEOUT ; 
 scalar_t__ AMDGPU_RING_TYPE_UVD ; 
 scalar_t__ AMDGPU_RING_TYPE_UVD_ENC ; 
 scalar_t__ AMDGPU_RING_TYPE_VCE ; 
 scalar_t__ AMDGPU_RING_TYPE_VCN_DEC ; 
 scalar_t__ AMDGPU_RING_TYPE_VCN_ENC ; 
 scalar_t__ AMDGPU_RING_TYPE_VCN_JPEG ; 
 int /*<<< orphan*/  DRM_DEV_DEBUG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
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
	} else if (adev->gmc.xgmi.hive_id) {
		tmo_gfx = AMDGPU_IB_TEST_GFX_XGMI_TIMEOUT;
	}

	for (i = 0; i < adev->num_rings; ++i) {
		struct amdgpu_ring *ring = adev->rings[i];
		long tmo;

		/* KIQ rings don't have an IB test because we never submit IBs
		 * to them and they have no interrupt support.
		 */
		if (!ring->sched.ready || !ring->funcs->test_ib)
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
		if (!r) {
			DRM_DEV_DEBUG(adev->dev, "ib test on %s succeeded\n",
				      ring->name);
			continue;
		}

		ring->sched.ready = false;
		DRM_DEV_ERROR(adev->dev, "IB test failed on %s (%d).\n",
			  ring->name, r);

		if (ring == &adev->gfx.gfx_ring[0]) {
			/* oh, oh, that's really bad */
			adev->accel_working = false;
			return r;

		} else {
			ret = r;
		}
	}
	return ret;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int ready; } ;
struct amdgpu_ring {TYPE_1__ sched; } ;
struct TYPE_6__ {int num_enc_rings; TYPE_2__* inst; } ;
struct amdgpu_device {int pg_flags; TYPE_3__ vcn; } ;
struct TYPE_5__ {struct amdgpu_ring ring_jpeg; struct amdgpu_ring* ring_enc; struct amdgpu_ring ring_dec; } ;

/* Variables and functions */
 int AMD_PG_SUPPORT_VCN_DPG ; 
 int /*<<< orphan*/  DRM_INFO (char*,char*) ; 
 int amdgpu_ring_test_helper (struct amdgpu_ring*) ; 

__attribute__((used)) static int vcn_v1_0_hw_init(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;
	struct amdgpu_ring *ring = &adev->vcn.inst->ring_dec;
	int i, r;

	r = amdgpu_ring_test_helper(ring);
	if (r)
		goto done;

	for (i = 0; i < adev->vcn.num_enc_rings; ++i) {
		ring = &adev->vcn.inst->ring_enc[i];
		ring->sched.ready = true;
		r = amdgpu_ring_test_helper(ring);
		if (r)
			goto done;
	}

	ring = &adev->vcn.inst->ring_jpeg;
	r = amdgpu_ring_test_helper(ring);
	if (r)
		goto done;

done:
	if (!r)
		DRM_INFO("VCN decode and encode initialized successfully(under %s).\n",
			(adev->pg_flags & AMD_PG_SUPPORT_VCN_DPG)?"DPG Mode":"SPG Mode");

	return r;
}
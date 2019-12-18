#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int num_uvd_inst; int harvest_config; TYPE_4__* inst; } ;
struct amdgpu_device {TYPE_1__ uvd; } ;
struct TYPE_7__ {int ready; } ;
struct TYPE_6__ {TYPE_3__ sched; } ;
struct TYPE_8__ {TYPE_2__ ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int /*<<< orphan*/  amdgpu_sriov_vf (struct amdgpu_device*) ; 
 int /*<<< orphan*/  uvd_v7_0_stop (struct amdgpu_device*) ; 

__attribute__((used)) static int uvd_v7_0_hw_fini(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;
	int i;

	if (!amdgpu_sriov_vf(adev))
		uvd_v7_0_stop(adev);
	else {
		/* full access mode, so don't touch any UVD register */
		DRM_DEBUG("For SRIOV client, shouldn't do anything.\n");
	}

	for (i = 0; i < adev->uvd.num_uvd_inst; ++i) {
		if (adev->uvd.harvest_config & (1 << i))
			continue;
		adev->uvd.inst[i].ring.sched.ready = false;
	}

	return 0;
}
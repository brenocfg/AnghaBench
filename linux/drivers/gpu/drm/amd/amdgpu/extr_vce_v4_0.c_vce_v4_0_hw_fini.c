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
struct TYPE_6__ {int num_rings; TYPE_2__* ring; } ;
struct amdgpu_device {TYPE_3__ vce; } ;
struct TYPE_4__ {int ready; } ;
struct TYPE_5__ {TYPE_1__ sched; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int /*<<< orphan*/  amdgpu_sriov_vf (struct amdgpu_device*) ; 
 int /*<<< orphan*/  vce_v4_0_stop (struct amdgpu_device*) ; 

__attribute__((used)) static int vce_v4_0_hw_fini(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;
	int i;

	if (!amdgpu_sriov_vf(adev)) {
		/* vce_v4_0_wait_for_idle(handle); */
		vce_v4_0_stop(adev);
	} else {
		/* full access mode, so don't touch any VCE register */
		DRM_DEBUG("For SRIOV client, shouldn't do anything.\n");
	}

	for (i = 0; i < adev->vce.num_rings; i++)
		adev->vce.ring[i].sched.ready = false;

	return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int num_rings; int /*<<< orphan*/ * ring; } ;
struct amdgpu_device {TYPE_1__ vce; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_INFO (char*) ; 
 int amdgpu_ring_test_helper (int /*<<< orphan*/ *) ; 
 scalar_t__ amdgpu_sriov_vf (struct amdgpu_device*) ; 
 int vce_v4_0_sriov_start (struct amdgpu_device*) ; 
 int vce_v4_0_start (struct amdgpu_device*) ; 

__attribute__((used)) static int vce_v4_0_hw_init(void *handle)
{
	int r, i;
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	if (amdgpu_sriov_vf(adev))
		r = vce_v4_0_sriov_start(adev);
	else
		r = vce_v4_0_start(adev);
	if (r)
		return r;

	for (i = 0; i < adev->vce.num_rings; i++) {
		r = amdgpu_ring_test_helper(&adev->vce.ring[i]);
		if (r)
			return r;
	}

	DRM_INFO("VCE initialized successfully.\n");

	return 0;
}
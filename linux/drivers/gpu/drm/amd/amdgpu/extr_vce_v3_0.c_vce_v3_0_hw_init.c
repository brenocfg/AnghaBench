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
 int /*<<< orphan*/  amdgpu_asic_set_vce_clocks (struct amdgpu_device*,int,int) ; 
 int amdgpu_ring_test_helper (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vce_v3_0_override_vce_clock_gating (struct amdgpu_device*,int) ; 

__attribute__((used)) static int vce_v3_0_hw_init(void *handle)
{
	int r, i;
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	vce_v3_0_override_vce_clock_gating(adev, true);

	amdgpu_asic_set_vce_clocks(adev, 10000, 10000);

	for (i = 0; i < adev->vce.num_rings; i++) {
		r = amdgpu_ring_test_helper(&adev->vce.ring[i]);
		if (r)
			return r;
	}

	DRM_INFO("VCE initialized successfully.\n");

	return 0;
}
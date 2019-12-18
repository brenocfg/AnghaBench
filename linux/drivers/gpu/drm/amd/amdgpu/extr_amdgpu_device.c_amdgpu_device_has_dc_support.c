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
struct amdgpu_device {int /*<<< orphan*/  asic_type; } ;

/* Variables and functions */
 int amdgpu_device_asic_has_dc_support (int /*<<< orphan*/ ) ; 
 scalar_t__ amdgpu_sriov_vf (struct amdgpu_device*) ; 

bool amdgpu_device_has_dc_support(struct amdgpu_device *adev)
{
	if (amdgpu_sriov_vf(adev))
		return false;

	return amdgpu_device_asic_has_dc_support(adev->asic_type);
}
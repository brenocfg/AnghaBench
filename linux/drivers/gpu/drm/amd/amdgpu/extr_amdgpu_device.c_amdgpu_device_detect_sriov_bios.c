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
struct TYPE_2__ {int caps; } ;
struct amdgpu_device {TYPE_1__ virt; scalar_t__ is_atom_fw; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGIM_ERROR_VF_NO_VBIOS ; 
 int AMDGPU_SRIOV_CAPS_SRIOV_VBIOS ; 
 scalar_t__ amdgpu_atombios_has_gpu_virtualization_table (struct amdgpu_device*) ; 
 scalar_t__ amdgpu_atomfirmware_gpu_supports_virtualization (struct amdgpu_device*) ; 
 scalar_t__ amdgpu_sriov_vf (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_vf_error_put (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void amdgpu_device_detect_sriov_bios(struct amdgpu_device *adev)
{
	if (amdgpu_sriov_vf(adev)) {
		if (adev->is_atom_fw) {
			if (amdgpu_atomfirmware_gpu_supports_virtualization(adev))
				adev->virt.caps |= AMDGPU_SRIOV_CAPS_SRIOV_VBIOS;
		} else {
			if (amdgpu_atombios_has_gpu_virtualization_table(adev))
				adev->virt.caps |= AMDGPU_SRIOV_CAPS_SRIOV_VBIOS;
		}

		if (!(adev->virt.caps & AMDGPU_SRIOV_CAPS_SRIOV_VBIOS))
			amdgpu_vf_error_put(adev, AMDGIM_ERROR_VF_NO_VBIOS, 0, 0);
	}
}
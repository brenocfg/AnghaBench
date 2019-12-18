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
struct amdgpu_device {int asic_type; } ;

/* Variables and functions */
#define  CHIP_BONAIRE 140 
#define  CHIP_FIJI 139 
#define  CHIP_HAWAII 138 
#define  CHIP_POLARIS10 137 
#define  CHIP_POLARIS11 136 
#define  CHIP_POLARIS12 135 
#define  CHIP_RAVEN 134 
#define  CHIP_TONGA 133 
#define  CHIP_TOPAZ 132 
#define  CHIP_VEGA10 131 
#define  CHIP_VEGA12 130 
#define  CHIP_VEGA20 129 
#define  CHIP_VEGAM 128 
 int /*<<< orphan*/  DRM_INFO (char*) ; 
 int /*<<< orphan*/  amdgpu_device_ip_check_soft_reset (struct amdgpu_device*) ; 
 int amdgpu_gpu_recovery ; 
 scalar_t__ amdgpu_sriov_vf (struct amdgpu_device*) ; 

bool amdgpu_device_should_recover_gpu(struct amdgpu_device *adev)
{
	if (!amdgpu_device_ip_check_soft_reset(adev)) {
		DRM_INFO("Timeout, but no hardware hang detected.\n");
		return false;
	}

	if (amdgpu_gpu_recovery == 0)
		goto disabled;

	if (amdgpu_sriov_vf(adev))
		return true;

	if (amdgpu_gpu_recovery == -1) {
		switch (adev->asic_type) {
		case CHIP_BONAIRE:
		case CHIP_HAWAII:
		case CHIP_TOPAZ:
		case CHIP_TONGA:
		case CHIP_FIJI:
		case CHIP_POLARIS10:
		case CHIP_POLARIS11:
		case CHIP_POLARIS12:
		case CHIP_VEGAM:
		case CHIP_VEGA20:
		case CHIP_VEGA10:
		case CHIP_VEGA12:
		case CHIP_RAVEN:
			break;
		default:
			goto disabled;
		}
	}

	return true;

disabled:
		DRM_INFO("GPU recovery disabled.\n");
		return false;
}
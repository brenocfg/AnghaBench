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
#define  CHIP_CARRIZO 138 
#define  CHIP_FIJI 137 
#define  CHIP_POLARIS10 136 
#define  CHIP_POLARIS11 135 
#define  CHIP_STONEY 134 
#define  CHIP_TONGA 133 
#define  CHIP_TOPAZ 132 
#define  CHIP_VEGA10 131 
#define  CHIP_VEGA12 130 
#define  CHIP_VEGA20 129 
#define  CHIP_VEGAM 128 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int /*<<< orphan*/  dce_v10_0_disable_dce (struct amdgpu_device*) ; 
 int /*<<< orphan*/  dce_v11_0_disable_dce (struct amdgpu_device*) ; 

__attribute__((used)) static int dce_virtual_hw_init(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	switch (adev->asic_type) {
#ifdef CONFIG_DRM_AMDGPU_SI
	case CHIP_TAHITI:
	case CHIP_PITCAIRN:
	case CHIP_VERDE:
	case CHIP_OLAND:
		dce_v6_0_disable_dce(adev);
		break;
#endif
#ifdef CONFIG_DRM_AMDGPU_CIK
	case CHIP_BONAIRE:
	case CHIP_HAWAII:
	case CHIP_KAVERI:
	case CHIP_KABINI:
	case CHIP_MULLINS:
		dce_v8_0_disable_dce(adev);
		break;
#endif
	case CHIP_FIJI:
	case CHIP_TONGA:
		dce_v10_0_disable_dce(adev);
		break;
	case CHIP_CARRIZO:
	case CHIP_STONEY:
	case CHIP_POLARIS10:
	case CHIP_POLARIS11:
	case CHIP_VEGAM:
		dce_v11_0_disable_dce(adev);
		break;
	case CHIP_TOPAZ:
#ifdef CONFIG_DRM_AMDGPU_SI
	case CHIP_HAINAN:
#endif
		/* no DCE */
		break;
	case CHIP_VEGA10:
	case CHIP_VEGA12:
	case CHIP_VEGA20:
		break;
	default:
		DRM_ERROR("Virtual display unsupported ASIC type: 0x%X\n", adev->asic_type);
	}
	return 0;
}
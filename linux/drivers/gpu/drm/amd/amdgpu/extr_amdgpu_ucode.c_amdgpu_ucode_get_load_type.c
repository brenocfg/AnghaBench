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
typedef  enum amdgpu_firmware_load_type { ____Placeholder_amdgpu_firmware_load_type } amdgpu_firmware_load_type ;

/* Variables and functions */
 int AMDGPU_FW_LOAD_DIRECT ; 
 int AMDGPU_FW_LOAD_PSP ; 
 int AMDGPU_FW_LOAD_SMU ; 
#define  CHIP_ARCTURUS 155 
#define  CHIP_BONAIRE 154 
#define  CHIP_CARRIZO 153 
#define  CHIP_FIJI 152 
#define  CHIP_HAINAN 151 
#define  CHIP_HAWAII 150 
#define  CHIP_KABINI 149 
#define  CHIP_KAVERI 148 
#define  CHIP_MULLINS 147 
#define  CHIP_NAVI10 146 
#define  CHIP_NAVI12 145 
#define  CHIP_NAVI14 144 
#define  CHIP_OLAND 143 
#define  CHIP_PITCAIRN 142 
#define  CHIP_POLARIS10 141 
#define  CHIP_POLARIS11 140 
#define  CHIP_POLARIS12 139 
#define  CHIP_RAVEN 138 
#define  CHIP_RENOIR 137 
#define  CHIP_STONEY 136 
#define  CHIP_TAHITI 135 
#define  CHIP_TONGA 134 
#define  CHIP_TOPAZ 133 
#define  CHIP_VEGA10 132 
#define  CHIP_VEGA12 131 
#define  CHIP_VEGA20 130 
#define  CHIP_VEGAM 129 
#define  CHIP_VERDE 128 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 

enum amdgpu_firmware_load_type
amdgpu_ucode_get_load_type(struct amdgpu_device *adev, int load_type)
{
	switch (adev->asic_type) {
#ifdef CONFIG_DRM_AMDGPU_SI
	case CHIP_TAHITI:
	case CHIP_PITCAIRN:
	case CHIP_VERDE:
	case CHIP_OLAND:
	case CHIP_HAINAN:
		return AMDGPU_FW_LOAD_DIRECT;
#endif
#ifdef CONFIG_DRM_AMDGPU_CIK
	case CHIP_BONAIRE:
	case CHIP_KAVERI:
	case CHIP_KABINI:
	case CHIP_HAWAII:
	case CHIP_MULLINS:
		return AMDGPU_FW_LOAD_DIRECT;
#endif
	case CHIP_TOPAZ:
	case CHIP_TONGA:
	case CHIP_FIJI:
	case CHIP_CARRIZO:
	case CHIP_STONEY:
	case CHIP_POLARIS10:
	case CHIP_POLARIS11:
	case CHIP_POLARIS12:
	case CHIP_VEGAM:
		return AMDGPU_FW_LOAD_SMU;
	case CHIP_VEGA10:
	case CHIP_RAVEN:
	case CHIP_VEGA12:
	case CHIP_VEGA20:
	case CHIP_RENOIR:
	case CHIP_NAVI10:
	case CHIP_NAVI14:
	case CHIP_NAVI12:
		if (!load_type)
			return AMDGPU_FW_LOAD_DIRECT;
		else
			return AMDGPU_FW_LOAD_PSP;
	case CHIP_ARCTURUS:
		return AMDGPU_FW_LOAD_DIRECT;

	default:
		DRM_ERROR("Unknown firmware load type\n");
	}

	return AMDGPU_FW_LOAD_DIRECT;
}
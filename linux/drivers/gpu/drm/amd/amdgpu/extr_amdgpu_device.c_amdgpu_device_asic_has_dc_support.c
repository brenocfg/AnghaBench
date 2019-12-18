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
typedef  enum amd_asic_type { ____Placeholder_amd_asic_type } amd_asic_type ;

/* Variables and functions */
#define  CHIP_BONAIRE 148 
#define  CHIP_CARRIZO 147 
#define  CHIP_FIJI 146 
#define  CHIP_HAWAII 145 
#define  CHIP_KABINI 144 
#define  CHIP_KAVERI 143 
#define  CHIP_MULLINS 142 
#define  CHIP_NAVI10 141 
#define  CHIP_NAVI12 140 
#define  CHIP_NAVI14 139 
#define  CHIP_POLARIS10 138 
#define  CHIP_POLARIS11 137 
#define  CHIP_POLARIS12 136 
#define  CHIP_RAVEN 135 
#define  CHIP_RENOIR 134 
#define  CHIP_STONEY 133 
#define  CHIP_TONGA 132 
#define  CHIP_VEGA10 131 
#define  CHIP_VEGA12 130 
#define  CHIP_VEGA20 129 
#define  CHIP_VEGAM 128 
 int /*<<< orphan*/  amdgpu_dc ; 

bool amdgpu_device_asic_has_dc_support(enum amd_asic_type asic_type)
{
	switch (asic_type) {
#if defined(CONFIG_DRM_AMD_DC)
	case CHIP_BONAIRE:
	case CHIP_KAVERI:
	case CHIP_KABINI:
	case CHIP_MULLINS:
		/*
		 * We have systems in the wild with these ASICs that require
		 * LVDS and VGA support which is not supported with DC.
		 *
		 * Fallback to the non-DC driver here by default so as not to
		 * cause regressions.
		 */
		return amdgpu_dc > 0;
	case CHIP_HAWAII:
	case CHIP_CARRIZO:
	case CHIP_STONEY:
	case CHIP_POLARIS10:
	case CHIP_POLARIS11:
	case CHIP_POLARIS12:
	case CHIP_VEGAM:
	case CHIP_TONGA:
	case CHIP_FIJI:
	case CHIP_VEGA10:
	case CHIP_VEGA12:
	case CHIP_VEGA20:
#if defined(CONFIG_DRM_AMD_DC_DCN1_0)
	case CHIP_RAVEN:
#endif
#if defined(CONFIG_DRM_AMD_DC_DCN2_0)
	case CHIP_NAVI10:
	case CHIP_NAVI14:
	case CHIP_NAVI12:
#endif
#if defined(CONFIG_DRM_AMD_DC_DCN2_1)
	case CHIP_RENOIR:
#endif
		return amdgpu_dc != 0;
#endif
	default:
		return false;
	}
}
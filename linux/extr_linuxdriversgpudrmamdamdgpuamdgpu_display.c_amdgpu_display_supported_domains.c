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
typedef  int /*<<< orphan*/  uint32_t ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_GEM_DOMAIN_VRAM ; 

uint32_t amdgpu_display_supported_domains(struct amdgpu_device *adev)
{
	uint32_t domain = AMDGPU_GEM_DOMAIN_VRAM;

#if defined(CONFIG_DRM_AMD_DC)
	if (adev->asic_type >= CHIP_CARRIZO && adev->asic_type < CHIP_RAVEN &&
	    adev->flags & AMD_IS_APU &&
	    amdgpu_device_asic_has_dc_support(adev->asic_type))
		domain |= AMDGPU_GEM_DOMAIN_GTT;
#endif

	return domain;
}
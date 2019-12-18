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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct amdgpu_device {scalar_t__ asic_type; int flags; } ;

/* Variables and functions */
 int AMDGPU_GEM_CREATE_CPU_GTT_USWC ; 
 int /*<<< orphan*/  AMDGPU_GEM_DOMAIN_GTT ; 
 int /*<<< orphan*/  AMDGPU_GEM_DOMAIN_VRAM ; 
 int AMD_IS_APU ; 
 scalar_t__ CHIP_CARRIZO ; 
 scalar_t__ CHIP_RAVEN ; 
 scalar_t__ amdgpu_bo_support_uswc (int) ; 
 scalar_t__ amdgpu_device_asic_has_dc_support (scalar_t__) ; 

uint32_t amdgpu_display_supported_domains(struct amdgpu_device *adev,
					  uint64_t bo_flags)
{
	uint32_t domain = AMDGPU_GEM_DOMAIN_VRAM;

#if defined(CONFIG_DRM_AMD_DC)
	/*
	 * if amdgpu_bo_support_uswc returns false it means that USWC mappings
	 * is not supported for this board. But this mapping is required
	 * to avoid hang caused by placement of scanout BO in GTT on certain
	 * APUs. So force the BO placement to VRAM in case this architecture
	 * will not allow USWC mappings.
	 * Also, don't allow GTT domain if the BO doens't have USWC falg set.
	 */
	if (adev->asic_type >= CHIP_CARRIZO &&
	    adev->asic_type <= CHIP_RAVEN &&
	    (adev->flags & AMD_IS_APU) &&
	    (bo_flags & AMDGPU_GEM_CREATE_CPU_GTT_USWC) &&
	    amdgpu_bo_support_uswc(bo_flags) &&
	    amdgpu_device_asic_has_dc_support(adev->asic_type))
		domain |= AMDGPU_GEM_DOMAIN_GTT;
#endif

	return domain;
}
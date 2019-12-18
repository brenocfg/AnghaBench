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
typedef  int u32 ;
struct amdgpu_device {scalar_t__ asic_type; int flags; } ;

/* Variables and functions */
 int AMDGPU_VCE_HARVEST_VCE0 ; 
 int AMDGPU_VCE_HARVEST_VCE1 ; 
 int AMD_IS_APU ; 
 int CC_HARVEST_FUSES__VCE_DISABLE_MASK ; 
 int CC_HARVEST_FUSES__VCE_DISABLE__SHIFT ; 
 scalar_t__ CHIP_FIJI ; 
 scalar_t__ CHIP_POLARIS10 ; 
 scalar_t__ CHIP_POLARIS11 ; 
 scalar_t__ CHIP_POLARIS12 ; 
 scalar_t__ CHIP_STONEY ; 
 scalar_t__ CHIP_VEGAM ; 
 int RREG32_SMC (int /*<<< orphan*/ ) ; 
 int VCE_HARVEST_FUSE_MACRO__MASK ; 
 int VCE_HARVEST_FUSE_MACRO__SHIFT ; 
 int /*<<< orphan*/  ixCC_HARVEST_FUSES ; 
 int /*<<< orphan*/  ixVCE_HARVEST_FUSE_MACRO__ADDRESS ; 

__attribute__((used)) static unsigned vce_v3_0_get_harvest_config(struct amdgpu_device *adev)
{
	u32 tmp;

	if ((adev->asic_type == CHIP_FIJI) ||
	    (adev->asic_type == CHIP_STONEY))
		return AMDGPU_VCE_HARVEST_VCE1;

	if (adev->flags & AMD_IS_APU)
		tmp = (RREG32_SMC(ixVCE_HARVEST_FUSE_MACRO__ADDRESS) &
		       VCE_HARVEST_FUSE_MACRO__MASK) >>
			VCE_HARVEST_FUSE_MACRO__SHIFT;
	else
		tmp = (RREG32_SMC(ixCC_HARVEST_FUSES) &
		       CC_HARVEST_FUSES__VCE_DISABLE_MASK) >>
			CC_HARVEST_FUSES__VCE_DISABLE__SHIFT;

	switch (tmp) {
	case 1:
		return AMDGPU_VCE_HARVEST_VCE0;
	case 2:
		return AMDGPU_VCE_HARVEST_VCE1;
	case 3:
		return AMDGPU_VCE_HARVEST_VCE0 | AMDGPU_VCE_HARVEST_VCE1;
	default:
		if ((adev->asic_type == CHIP_POLARIS10) ||
		    (adev->asic_type == CHIP_POLARIS11) ||
		    (adev->asic_type == CHIP_POLARIS12) ||
		    (adev->asic_type == CHIP_VEGAM))
			return AMDGPU_VCE_HARVEST_VCE1;

		return 0;
	}
}
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
struct amdgpu_device {int flags; } ;

/* Variables and functions */
 int AMD_IS_APU ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int LC_LINK_WIDTH_MASK ; 
 int LC_LINK_WIDTH_SHIFT ; 
 int LC_LINK_WIDTH_X0 ; 
 int LC_LINK_WIDTH_X1 ; 
 int LC_LINK_WIDTH_X16 ; 
 int LC_LINK_WIDTH_X2 ; 
 int LC_LINK_WIDTH_X4 ; 
 int LC_LINK_WIDTH_X8 ; 
 int LC_RECONFIG_ARC_MISSING_ESCAPE ; 
 int LC_RECONFIG_NOW ; 
 int /*<<< orphan*/  PCIE_LC_LINK_WIDTH_CNTL ; 
 int RREG32_PCIE_PORT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_PCIE_PORT (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void si_set_pcie_lanes(struct amdgpu_device *adev, int lanes)
{
	u32 link_width_cntl, mask;

	if (adev->flags & AMD_IS_APU)
		return;

	switch (lanes) {
	case 0:
		mask = LC_LINK_WIDTH_X0;
		break;
	case 1:
		mask = LC_LINK_WIDTH_X1;
		break;
	case 2:
		mask = LC_LINK_WIDTH_X2;
		break;
	case 4:
		mask = LC_LINK_WIDTH_X4;
		break;
	case 8:
		mask = LC_LINK_WIDTH_X8;
		break;
	case 16:
		mask = LC_LINK_WIDTH_X16;
		break;
	default:
		DRM_ERROR("invalid pcie lane request: %d\n", lanes);
		return;
	}

	link_width_cntl = RREG32_PCIE_PORT(PCIE_LC_LINK_WIDTH_CNTL);
	link_width_cntl &= ~LC_LINK_WIDTH_MASK;
	link_width_cntl |= mask << LC_LINK_WIDTH_SHIFT;
	link_width_cntl |= (LC_RECONFIG_NOW |
			    LC_RECONFIG_ARC_MISSING_ESCAPE);

	WREG32_PCIE_PORT(PCIE_LC_LINK_WIDTH_CNTL, link_width_cntl);
}
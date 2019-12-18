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
struct radeon_device {int flags; } ;

/* Variables and functions */
 scalar_t__ ASIC_IS_X2 (struct radeon_device*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int R600_PCIE_LC_RECONFIG_ARC_MISSING_ESCAPE ; 
 int RADEON_IS_IGP ; 
 int RADEON_IS_PCIE ; 
 int /*<<< orphan*/  RADEON_PCIE_LC_LINK_WIDTH_CNTL ; 
 int RADEON_PCIE_LC_LINK_WIDTH_MASK ; 
 int RADEON_PCIE_LC_LINK_WIDTH_SHIFT ; 
 int RADEON_PCIE_LC_LINK_WIDTH_X0 ; 
 int RADEON_PCIE_LC_LINK_WIDTH_X1 ; 
 int RADEON_PCIE_LC_LINK_WIDTH_X12 ; 
 int RADEON_PCIE_LC_LINK_WIDTH_X16 ; 
 int RADEON_PCIE_LC_LINK_WIDTH_X2 ; 
 int RADEON_PCIE_LC_LINK_WIDTH_X4 ; 
 int RADEON_PCIE_LC_LINK_WIDTH_X8 ; 
 int RADEON_PCIE_LC_RECONFIG_NOW ; 
 int RREG32_PCIE_PORT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_PCIE_PORT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  radeon_gui_idle (struct radeon_device*) ; 

void r600_set_pcie_lanes(struct radeon_device *rdev, int lanes)
{
	u32 link_width_cntl, mask;

	if (rdev->flags & RADEON_IS_IGP)
		return;

	if (!(rdev->flags & RADEON_IS_PCIE))
		return;

	/* x2 cards have a special sequence */
	if (ASIC_IS_X2(rdev))
		return;

	radeon_gui_idle(rdev);

	switch (lanes) {
	case 0:
		mask = RADEON_PCIE_LC_LINK_WIDTH_X0;
		break;
	case 1:
		mask = RADEON_PCIE_LC_LINK_WIDTH_X1;
		break;
	case 2:
		mask = RADEON_PCIE_LC_LINK_WIDTH_X2;
		break;
	case 4:
		mask = RADEON_PCIE_LC_LINK_WIDTH_X4;
		break;
	case 8:
		mask = RADEON_PCIE_LC_LINK_WIDTH_X8;
		break;
	case 12:
		/* not actually supported */
		mask = RADEON_PCIE_LC_LINK_WIDTH_X12;
		break;
	case 16:
		mask = RADEON_PCIE_LC_LINK_WIDTH_X16;
		break;
	default:
		DRM_ERROR("invalid pcie lane request: %d\n", lanes);
		return;
	}

	link_width_cntl = RREG32_PCIE_PORT(RADEON_PCIE_LC_LINK_WIDTH_CNTL);
	link_width_cntl &= ~RADEON_PCIE_LC_LINK_WIDTH_MASK;
	link_width_cntl |= mask << RADEON_PCIE_LC_LINK_WIDTH_SHIFT;
	link_width_cntl |= (RADEON_PCIE_LC_RECONFIG_NOW |
			    R600_PCIE_LC_RECONFIG_ARC_MISSING_ESCAPE);

	WREG32_PCIE_PORT(RADEON_PCIE_LC_LINK_WIDTH_CNTL, link_width_cntl);
}
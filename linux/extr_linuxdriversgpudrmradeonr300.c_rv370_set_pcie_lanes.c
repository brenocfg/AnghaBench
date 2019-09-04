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
typedef  int uint32_t ;
struct radeon_device {int flags; } ;

/* Variables and functions */
 int RADEON_IS_IGP ; 
 int RADEON_IS_PCIE ; 
 int /*<<< orphan*/  RADEON_PCIE_LC_LINK_WIDTH_CNTL ; 
 int RADEON_PCIE_LC_LINK_WIDTH_MASK ; 
 int RADEON_PCIE_LC_LINK_WIDTH_RD_MASK ; 
 int RADEON_PCIE_LC_LINK_WIDTH_RD_SHIFT ; 
 int RADEON_PCIE_LC_LINK_WIDTH_X0 ; 
 int RADEON_PCIE_LC_LINK_WIDTH_X1 ; 
 int RADEON_PCIE_LC_LINK_WIDTH_X12 ; 
 int RADEON_PCIE_LC_LINK_WIDTH_X16 ; 
 int RADEON_PCIE_LC_LINK_WIDTH_X2 ; 
 int RADEON_PCIE_LC_LINK_WIDTH_X4 ; 
 int RADEON_PCIE_LC_LINK_WIDTH_X8 ; 
 int RADEON_PCIE_LC_RECONFIG_LATER ; 
 int RADEON_PCIE_LC_RECONFIG_NOW ; 
 int RADEON_PCIE_LC_SHORT_RECONFIG_EN ; 
 int RREG32_PCIE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_PCIE (int /*<<< orphan*/ ,int) ; 

void rv370_set_pcie_lanes(struct radeon_device *rdev, int lanes)
{
	uint32_t link_width_cntl, mask;

	if (rdev->flags & RADEON_IS_IGP)
		return;

	if (!(rdev->flags & RADEON_IS_PCIE))
		return;

	/* FIXME wait for idle */

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
		mask = RADEON_PCIE_LC_LINK_WIDTH_X12;
		break;
	case 16:
	default:
		mask = RADEON_PCIE_LC_LINK_WIDTH_X16;
		break;
	}

	link_width_cntl = RREG32_PCIE(RADEON_PCIE_LC_LINK_WIDTH_CNTL);

	if ((link_width_cntl & RADEON_PCIE_LC_LINK_WIDTH_RD_MASK) ==
	    (mask << RADEON_PCIE_LC_LINK_WIDTH_RD_SHIFT))
		return;

	link_width_cntl &= ~(RADEON_PCIE_LC_LINK_WIDTH_MASK |
			     RADEON_PCIE_LC_RECONFIG_NOW |
			     RADEON_PCIE_LC_RECONFIG_LATER |
			     RADEON_PCIE_LC_SHORT_RECONFIG_EN);
	link_width_cntl |= mask;
	WREG32_PCIE(RADEON_PCIE_LC_LINK_WIDTH_CNTL, link_width_cntl);
	WREG32_PCIE(RADEON_PCIE_LC_LINK_WIDTH_CNTL, (link_width_cntl |
						     RADEON_PCIE_LC_RECONFIG_NOW));

	/* wait for lane set to complete */
	link_width_cntl = RREG32_PCIE(RADEON_PCIE_LC_LINK_WIDTH_CNTL);
	while (link_width_cntl == 0xffffffff)
		link_width_cntl = RREG32_PCIE(RADEON_PCIE_LC_LINK_WIDTH_CNTL);

}
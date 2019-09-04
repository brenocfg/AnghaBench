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
 int RADEON_IS_IGP ; 
 int RADEON_IS_PCIE ; 
 int /*<<< orphan*/  RADEON_PCIE_LC_LINK_WIDTH_CNTL ; 
 int RADEON_PCIE_LC_LINK_WIDTH_RD_MASK ; 
 int RADEON_PCIE_LC_LINK_WIDTH_RD_SHIFT ; 
#define  RADEON_PCIE_LC_LINK_WIDTH_X0 134 
#define  RADEON_PCIE_LC_LINK_WIDTH_X1 133 
#define  RADEON_PCIE_LC_LINK_WIDTH_X12 132 
#define  RADEON_PCIE_LC_LINK_WIDTH_X16 131 
#define  RADEON_PCIE_LC_LINK_WIDTH_X2 130 
#define  RADEON_PCIE_LC_LINK_WIDTH_X4 129 
#define  RADEON_PCIE_LC_LINK_WIDTH_X8 128 
 int RREG32_PCIE_PORT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_gui_idle (struct radeon_device*) ; 

int r600_get_pcie_lanes(struct radeon_device *rdev)
{
	u32 link_width_cntl;

	if (rdev->flags & RADEON_IS_IGP)
		return 0;

	if (!(rdev->flags & RADEON_IS_PCIE))
		return 0;

	/* x2 cards have a special sequence */
	if (ASIC_IS_X2(rdev))
		return 0;

	radeon_gui_idle(rdev);

	link_width_cntl = RREG32_PCIE_PORT(RADEON_PCIE_LC_LINK_WIDTH_CNTL);

	switch ((link_width_cntl & RADEON_PCIE_LC_LINK_WIDTH_RD_MASK) >> RADEON_PCIE_LC_LINK_WIDTH_RD_SHIFT) {
	case RADEON_PCIE_LC_LINK_WIDTH_X1:
		return 1;
	case RADEON_PCIE_LC_LINK_WIDTH_X2:
		return 2;
	case RADEON_PCIE_LC_LINK_WIDTH_X4:
		return 4;
	case RADEON_PCIE_LC_LINK_WIDTH_X8:
		return 8;
	case RADEON_PCIE_LC_LINK_WIDTH_X12:
		/* not actually supported */
		return 12;
	case RADEON_PCIE_LC_LINK_WIDTH_X0:
	case RADEON_PCIE_LC_LINK_WIDTH_X16:
	default:
		return 16;
	}
}
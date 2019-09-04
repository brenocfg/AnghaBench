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
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int LC_LINK_WIDTH_RD_MASK ; 
 int LC_LINK_WIDTH_RD_SHIFT ; 
 int /*<<< orphan*/  PCIE_LC_LINK_WIDTH_CNTL ; 
#define  RADEON_PCIE_LC_LINK_WIDTH_X0 134 
#define  RADEON_PCIE_LC_LINK_WIDTH_X1 133 
#define  RADEON_PCIE_LC_LINK_WIDTH_X12 132 
#define  RADEON_PCIE_LC_LINK_WIDTH_X16 131 
#define  RADEON_PCIE_LC_LINK_WIDTH_X2 130 
#define  RADEON_PCIE_LC_LINK_WIDTH_X4 129 
#define  RADEON_PCIE_LC_LINK_WIDTH_X8 128 
 int RREG32_PCIE_PORT (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ci_get_current_pcie_lane_number(struct radeon_device *rdev)
{
	u32 link_width = 0;

	link_width = RREG32_PCIE_PORT(PCIE_LC_LINK_WIDTH_CNTL) & LC_LINK_WIDTH_RD_MASK;
	link_width >>= LC_LINK_WIDTH_RD_SHIFT;

	switch (link_width) {
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
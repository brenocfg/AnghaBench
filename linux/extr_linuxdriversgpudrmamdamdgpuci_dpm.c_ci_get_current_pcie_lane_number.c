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
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int PCIE_LC_LINK_WIDTH_CNTL__LC_LINK_WIDTH_RD_MASK ; 
 int PCIE_LC_LINK_WIDTH_CNTL__LC_LINK_WIDTH_RD__SHIFT ; 
 int RREG32_PCIE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixPCIE_LC_LINK_WIDTH_CNTL ; 

__attribute__((used)) static int ci_get_current_pcie_lane_number(struct amdgpu_device *adev)
{
	u32 link_width = 0;

	link_width = RREG32_PCIE(ixPCIE_LC_LINK_WIDTH_CNTL) &
		PCIE_LC_LINK_WIDTH_CNTL__LC_LINK_WIDTH_RD_MASK;
	link_width >>= PCIE_LC_LINK_WIDTH_CNTL__LC_LINK_WIDTH_RD__SHIFT;

	switch (link_width) {
	case 1:
		return 1;
	case 2:
		return 2;
	case 3:
		return 4;
	case 4:
		return 8;
	case 0:
	case 6:
	default:
		return 16;
	}
}
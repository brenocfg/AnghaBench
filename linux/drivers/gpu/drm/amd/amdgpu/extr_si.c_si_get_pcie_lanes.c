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
 int LC_LINK_WIDTH_RD_MASK ; 
 int LC_LINK_WIDTH_RD_SHIFT ; 
#define  LC_LINK_WIDTH_X0 133 
#define  LC_LINK_WIDTH_X1 132 
#define  LC_LINK_WIDTH_X16 131 
#define  LC_LINK_WIDTH_X2 130 
#define  LC_LINK_WIDTH_X4 129 
#define  LC_LINK_WIDTH_X8 128 
 int /*<<< orphan*/  PCIE_LC_LINK_WIDTH_CNTL ; 
 int RREG32_PCIE_PORT (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int si_get_pcie_lanes(struct amdgpu_device *adev)
{
	u32 link_width_cntl;

	if (adev->flags & AMD_IS_APU)
		return 0;

	link_width_cntl = RREG32_PCIE_PORT(PCIE_LC_LINK_WIDTH_CNTL);

	switch ((link_width_cntl & LC_LINK_WIDTH_RD_MASK) >> LC_LINK_WIDTH_RD_SHIFT) {
	case LC_LINK_WIDTH_X1:
		return 1;
	case LC_LINK_WIDTH_X2:
		return 2;
	case LC_LINK_WIDTH_X4:
		return 4;
	case LC_LINK_WIDTH_X8:
		return 8;
	case LC_LINK_WIDTH_X0:
	case LC_LINK_WIDTH_X16:
	default:
		return 16;
	}
}
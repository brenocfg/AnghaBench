#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct radeon_device {int flags; TYPE_2__* pdev; } ;
struct TYPE_4__ {TYPE_1__* bus; } ;
struct TYPE_3__ {scalar_t__ max_bus_speed; } ;

/* Variables and functions */
 scalar_t__ ASIC_IS_X2 (struct radeon_device*) ; 
 int /*<<< orphan*/  DRM_INFO (char*) ; 
 int LC_CLR_FAILED_SPD_CHANGE_CNT ; 
 int LC_GEN2_EN_STRAP ; 
 int LC_LINK_WIDTH_MASK ; 
 int LC_LINK_WIDTH_RD_MASK ; 
 int LC_LINK_WIDTH_RD_SHIFT ; 
 int LC_OTHER_SIDE_EVER_SENT_GEN2 ; 
 int LC_OTHER_SIDE_SUPPORTS_GEN2 ; 
 int LC_RECONFIG_ARC_MISSING_ESCAPE ; 
 int LC_RECONFIG_NOW ; 
 int LC_RENEGOTIATE_EN ; 
 int LC_RENEGOTIATION_SUPPORT ; 
 int LC_TARGET_LINK_SPEED_OVERRIDE_EN ; 
 int LC_UPCONFIGURE_DIS ; 
 int LC_UPCONFIGURE_SUPPORT ; 
 int MM_CFGREGS_CNTL ; 
 int MM_WR_TO_CFG_EN ; 
 int /*<<< orphan*/  PCIE_LC_LINK_WIDTH_CNTL ; 
 int /*<<< orphan*/  PCIE_LC_SPEED_CNTL ; 
 scalar_t__ PCIE_SPEED_5_0GT ; 
 scalar_t__ PCIE_SPEED_8_0GT ; 
 int RADEON_IS_IGP ; 
 int RADEON_IS_PCIE ; 
 int RREG16 (int) ; 
 int RREG32 (int) ; 
 int RREG32_PCIE_PORT (int /*<<< orphan*/ ) ; 
 int TARGET_LINK_SPEED_MASK ; 
 int /*<<< orphan*/  WREG16 (int,int) ; 
 int /*<<< orphan*/  WREG32 (int,int) ; 
 int /*<<< orphan*/  WREG32_PCIE_PORT (int /*<<< orphan*/ ,int) ; 
 scalar_t__ radeon_pcie_gen2 ; 

__attribute__((used)) static void rv770_pcie_gen2_enable(struct radeon_device *rdev)
{
	u32 link_width_cntl, lanes, speed_cntl, tmp;
	u16 link_cntl2;

	if (radeon_pcie_gen2 == 0)
		return;

	if (rdev->flags & RADEON_IS_IGP)
		return;

	if (!(rdev->flags & RADEON_IS_PCIE))
		return;

	/* x2 cards have a special sequence */
	if (ASIC_IS_X2(rdev))
		return;

	if ((rdev->pdev->bus->max_bus_speed != PCIE_SPEED_5_0GT) &&
		(rdev->pdev->bus->max_bus_speed != PCIE_SPEED_8_0GT))
		return;

	DRM_INFO("enabling PCIE gen 2 link speeds, disable with radeon.pcie_gen2=0\n");

	/* advertise upconfig capability */
	link_width_cntl = RREG32_PCIE_PORT(PCIE_LC_LINK_WIDTH_CNTL);
	link_width_cntl &= ~LC_UPCONFIGURE_DIS;
	WREG32_PCIE_PORT(PCIE_LC_LINK_WIDTH_CNTL, link_width_cntl);
	link_width_cntl = RREG32_PCIE_PORT(PCIE_LC_LINK_WIDTH_CNTL);
	if (link_width_cntl & LC_RENEGOTIATION_SUPPORT) {
		lanes = (link_width_cntl & LC_LINK_WIDTH_RD_MASK) >> LC_LINK_WIDTH_RD_SHIFT;
		link_width_cntl &= ~(LC_LINK_WIDTH_MASK |
				     LC_RECONFIG_ARC_MISSING_ESCAPE);
		link_width_cntl |= lanes | LC_RECONFIG_NOW |
			LC_RENEGOTIATE_EN | LC_UPCONFIGURE_SUPPORT;
		WREG32_PCIE_PORT(PCIE_LC_LINK_WIDTH_CNTL, link_width_cntl);
	} else {
		link_width_cntl |= LC_UPCONFIGURE_DIS;
		WREG32_PCIE_PORT(PCIE_LC_LINK_WIDTH_CNTL, link_width_cntl);
	}

	speed_cntl = RREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL);
	if ((speed_cntl & LC_OTHER_SIDE_EVER_SENT_GEN2) &&
	    (speed_cntl & LC_OTHER_SIDE_SUPPORTS_GEN2)) {

		tmp = RREG32(0x541c);
		WREG32(0x541c, tmp | 0x8);
		WREG32(MM_CFGREGS_CNTL, MM_WR_TO_CFG_EN);
		link_cntl2 = RREG16(0x4088);
		link_cntl2 &= ~TARGET_LINK_SPEED_MASK;
		link_cntl2 |= 0x2;
		WREG16(0x4088, link_cntl2);
		WREG32(MM_CFGREGS_CNTL, 0);

		speed_cntl = RREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL);
		speed_cntl &= ~LC_TARGET_LINK_SPEED_OVERRIDE_EN;
		WREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL, speed_cntl);

		speed_cntl = RREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL);
		speed_cntl |= LC_CLR_FAILED_SPD_CHANGE_CNT;
		WREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL, speed_cntl);

		speed_cntl = RREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL);
		speed_cntl &= ~LC_CLR_FAILED_SPD_CHANGE_CNT;
		WREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL, speed_cntl);

		speed_cntl = RREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL);
		speed_cntl |= LC_GEN2_EN_STRAP;
		WREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL, speed_cntl);

	} else {
		link_width_cntl = RREG32_PCIE_PORT(PCIE_LC_LINK_WIDTH_CNTL);
		/* XXX: only disable it if gen1 bridge vendor == 0x111d or 0x1106 */
		if (1)
			link_width_cntl |= LC_UPCONFIGURE_DIS;
		else
			link_width_cntl &= ~LC_UPCONFIGURE_DIS;
		WREG32_PCIE_PORT(PCIE_LC_LINK_WIDTH_CNTL, link_width_cntl);
	}
}
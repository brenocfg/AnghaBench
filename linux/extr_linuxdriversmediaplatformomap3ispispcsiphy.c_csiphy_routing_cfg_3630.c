#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct isp_csiphy {TYPE_1__* isp; } ;
typedef  enum isp_interface_type { ____Placeholder_isp_interface_type } isp_interface_type ;
struct TYPE_2__ {int /*<<< orphan*/  syscon_offset; int /*<<< orphan*/  syscon; } ;

/* Variables and functions */
#define  ISP_INTERFACE_CCP2B_PHY1 131 
#define  ISP_INTERFACE_CCP2B_PHY2 130 
#define  ISP_INTERFACE_CSI2A_PHY2 129 
#define  ISP_INTERFACE_CSI2C_PHY1 128 
 int OMAP3630_CONTROL_CAMERA_PHY_CTRL_CAMMODE_CCP2_DATA_CLOCK ; 
 int OMAP3630_CONTROL_CAMERA_PHY_CTRL_CAMMODE_CCP2_DATA_STROBE ; 
 int OMAP3630_CONTROL_CAMERA_PHY_CTRL_CAMMODE_DPHY ; 
 int OMAP3630_CONTROL_CAMERA_PHY_CTRL_CAMMODE_MASK ; 
 int OMAP3630_CONTROL_CAMERA_PHY_CTRL_CAMMODE_PHY1_SHIFT ; 
 int OMAP3630_CONTROL_CAMERA_PHY_CTRL_CAMMODE_PHY2_SHIFT ; 
 int OMAP3630_CONTROL_CAMERA_PHY_CTRL_CSI1_RX_SEL_PHY2 ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void csiphy_routing_cfg_3630(struct isp_csiphy *phy,
				    enum isp_interface_type iface,
				    bool ccp2_strobe)
{
	u32 reg;
	u32 shift, mode;

	regmap_read(phy->isp->syscon, phy->isp->syscon_offset, &reg);

	switch (iface) {
	default:
	/* Should not happen in practice, but let's keep the compiler happy. */
	case ISP_INTERFACE_CCP2B_PHY1:
		reg &= ~OMAP3630_CONTROL_CAMERA_PHY_CTRL_CSI1_RX_SEL_PHY2;
		shift = OMAP3630_CONTROL_CAMERA_PHY_CTRL_CAMMODE_PHY1_SHIFT;
		break;
	case ISP_INTERFACE_CSI2C_PHY1:
		shift = OMAP3630_CONTROL_CAMERA_PHY_CTRL_CAMMODE_PHY1_SHIFT;
		mode = OMAP3630_CONTROL_CAMERA_PHY_CTRL_CAMMODE_DPHY;
		break;
	case ISP_INTERFACE_CCP2B_PHY2:
		reg |= OMAP3630_CONTROL_CAMERA_PHY_CTRL_CSI1_RX_SEL_PHY2;
		shift = OMAP3630_CONTROL_CAMERA_PHY_CTRL_CAMMODE_PHY2_SHIFT;
		break;
	case ISP_INTERFACE_CSI2A_PHY2:
		shift = OMAP3630_CONTROL_CAMERA_PHY_CTRL_CAMMODE_PHY2_SHIFT;
		mode = OMAP3630_CONTROL_CAMERA_PHY_CTRL_CAMMODE_DPHY;
		break;
	}

	/* Select data/clock or data/strobe mode for CCP2 */
	if (iface == ISP_INTERFACE_CCP2B_PHY1 ||
	    iface == ISP_INTERFACE_CCP2B_PHY2) {
		if (ccp2_strobe)
			mode = OMAP3630_CONTROL_CAMERA_PHY_CTRL_CAMMODE_CCP2_DATA_STROBE;
		else
			mode = OMAP3630_CONTROL_CAMERA_PHY_CTRL_CAMMODE_CCP2_DATA_CLOCK;
	}

	reg &= ~(OMAP3630_CONTROL_CAMERA_PHY_CTRL_CAMMODE_MASK << shift);
	reg |= mode << shift;

	regmap_write(phy->isp->syscon, phy->isp->syscon_offset, reg);
}
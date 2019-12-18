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
struct TYPE_4__ {int type; int speeds_supported; scalar_t__ media_type; scalar_t__ sfp_type; int nw_mng_if_sel; scalar_t__ multispeed_fiber; } ;
struct TYPE_3__ {int /*<<< orphan*/  type; } ;
struct ixgbe_hw {int /*<<< orphan*/  device_id; TYPE_2__ phy; TYPE_1__ mac; } ;
typedef  int /*<<< orphan*/  s32 ;
typedef  int ixgbe_link_speed ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_DEV_ID_X550EM_A_KR_L ; 
 int IXGBE_LINK_SPEED_10GB_FULL ; 
 int IXGBE_LINK_SPEED_1GB_FULL ; 
 int IXGBE_LINK_SPEED_2_5GB_FULL ; 
 int IXGBE_NW_MNG_IF_SEL_PHY_SPEED_2_5G ; 
 int /*<<< orphan*/  ixgbe_mac_x550em_a ; 
 scalar_t__ ixgbe_media_type_fiber ; 
#define  ixgbe_phy_ext_1g_t 132 
 int ixgbe_phy_fw ; 
#define  ixgbe_phy_sgmii 131 
#define  ixgbe_phy_x550em_kr 130 
#define  ixgbe_phy_x550em_kx4 129 
#define  ixgbe_phy_x550em_xfi 128 
 scalar_t__ ixgbe_sfp_type_1g_lx_core0 ; 
 scalar_t__ ixgbe_sfp_type_1g_lx_core1 ; 
 scalar_t__ ixgbe_sfp_type_1g_sx_core0 ; 
 scalar_t__ ixgbe_sfp_type_1g_sx_core1 ; 

__attribute__((used)) static s32 ixgbe_get_link_capabilities_X550em(struct ixgbe_hw *hw,
					      ixgbe_link_speed *speed,
					      bool *autoneg)
{
	if (hw->phy.type == ixgbe_phy_fw) {
		*autoneg = true;
		*speed = hw->phy.speeds_supported;
		return 0;
	}

	/* SFP */
	if (hw->phy.media_type == ixgbe_media_type_fiber) {
		/* CS4227 SFP must not enable auto-negotiation */
		*autoneg = false;

		if (hw->phy.sfp_type == ixgbe_sfp_type_1g_sx_core0 ||
		    hw->phy.sfp_type == ixgbe_sfp_type_1g_sx_core1 ||
		    hw->phy.sfp_type == ixgbe_sfp_type_1g_lx_core0 ||
		    hw->phy.sfp_type == ixgbe_sfp_type_1g_lx_core1) {
			*speed = IXGBE_LINK_SPEED_1GB_FULL;
			return 0;
		}

		/* Link capabilities are based on SFP */
		if (hw->phy.multispeed_fiber)
			*speed = IXGBE_LINK_SPEED_10GB_FULL |
				 IXGBE_LINK_SPEED_1GB_FULL;
		else
			*speed = IXGBE_LINK_SPEED_10GB_FULL;
	} else {
		switch (hw->phy.type) {
		case ixgbe_phy_x550em_kx4:
			*speed = IXGBE_LINK_SPEED_1GB_FULL |
				 IXGBE_LINK_SPEED_2_5GB_FULL |
				 IXGBE_LINK_SPEED_10GB_FULL;
			break;
		case ixgbe_phy_x550em_xfi:
			*speed = IXGBE_LINK_SPEED_1GB_FULL |
				 IXGBE_LINK_SPEED_10GB_FULL;
			break;
		case ixgbe_phy_ext_1g_t:
		case ixgbe_phy_sgmii:
			*speed = IXGBE_LINK_SPEED_1GB_FULL;
			break;
		case ixgbe_phy_x550em_kr:
			if (hw->mac.type == ixgbe_mac_x550em_a) {
				/* check different backplane modes */
				if (hw->phy.nw_mng_if_sel &
				    IXGBE_NW_MNG_IF_SEL_PHY_SPEED_2_5G) {
					*speed = IXGBE_LINK_SPEED_2_5GB_FULL;
					break;
				} else if (hw->device_id ==
					   IXGBE_DEV_ID_X550EM_A_KR_L) {
					*speed = IXGBE_LINK_SPEED_1GB_FULL;
					break;
				}
			}
			/* fall through */
		default:
			*speed = IXGBE_LINK_SPEED_10GB_FULL |
				 IXGBE_LINK_SPEED_1GB_FULL;
			break;
		}
		*autoneg = true;
	}
	return 0;
}
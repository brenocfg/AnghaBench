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
struct TYPE_4__ {scalar_t__ sfp_type; scalar_t__ media_type; scalar_t__ multispeed_fiber; } ;
struct TYPE_3__ {int orig_autoc; scalar_t__ orig_link_settings_stored; } ;
struct ixgbe_hw {TYPE_2__ phy; TYPE_1__ mac; } ;
typedef  int /*<<< orphan*/  s32 ;
typedef  int ixgbe_link_speed ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_AUTOC ; 
 int IXGBE_AUTOC_KR_SUPP ; 
 int IXGBE_AUTOC_KX4_SUPP ; 
 int IXGBE_AUTOC_KX_SUPP ; 
#define  IXGBE_AUTOC_LMS_10G_LINK_NO_AN 135 
#define  IXGBE_AUTOC_LMS_10G_SERIAL 134 
#define  IXGBE_AUTOC_LMS_1G_AN 133 
#define  IXGBE_AUTOC_LMS_1G_LINK_NO_AN 132 
#define  IXGBE_AUTOC_LMS_KX4_KX_KR 131 
#define  IXGBE_AUTOC_LMS_KX4_KX_KR_1G_AN 130 
#define  IXGBE_AUTOC_LMS_KX4_KX_KR_SGMII 129 
 int IXGBE_AUTOC_LMS_MASK ; 
#define  IXGBE_AUTOC_LMS_SGMII_1G_100M 128 
 int /*<<< orphan*/  IXGBE_ERR_LINK_SETUP ; 
 int IXGBE_LINK_SPEED_100_FULL ; 
 int IXGBE_LINK_SPEED_10GB_FULL ; 
 int IXGBE_LINK_SPEED_1GB_FULL ; 
 int IXGBE_LINK_SPEED_UNKNOWN ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ ixgbe_media_type_fiber_qsfp ; 
 scalar_t__ ixgbe_sfp_type_1g_cu_core0 ; 
 scalar_t__ ixgbe_sfp_type_1g_cu_core1 ; 
 scalar_t__ ixgbe_sfp_type_1g_lx_core0 ; 
 scalar_t__ ixgbe_sfp_type_1g_lx_core1 ; 
 scalar_t__ ixgbe_sfp_type_1g_sx_core0 ; 
 scalar_t__ ixgbe_sfp_type_1g_sx_core1 ; 

__attribute__((used)) static s32 ixgbe_get_link_capabilities_82599(struct ixgbe_hw *hw,
					     ixgbe_link_speed *speed,
					     bool *autoneg)
{
	u32 autoc = 0;

	/* Determine 1G link capabilities off of SFP+ type */
	if (hw->phy.sfp_type == ixgbe_sfp_type_1g_cu_core0 ||
	    hw->phy.sfp_type == ixgbe_sfp_type_1g_cu_core1 ||
	    hw->phy.sfp_type == ixgbe_sfp_type_1g_lx_core0 ||
	    hw->phy.sfp_type == ixgbe_sfp_type_1g_lx_core1 ||
	    hw->phy.sfp_type == ixgbe_sfp_type_1g_sx_core0 ||
	    hw->phy.sfp_type == ixgbe_sfp_type_1g_sx_core1) {
		*speed = IXGBE_LINK_SPEED_1GB_FULL;
		*autoneg = true;
		return 0;
	}

	/*
	 * Determine link capabilities based on the stored value of AUTOC,
	 * which represents EEPROM defaults.  If AUTOC value has not been
	 * stored, use the current register value.
	 */
	if (hw->mac.orig_link_settings_stored)
		autoc = hw->mac.orig_autoc;
	else
		autoc = IXGBE_READ_REG(hw, IXGBE_AUTOC);

	switch (autoc & IXGBE_AUTOC_LMS_MASK) {
	case IXGBE_AUTOC_LMS_1G_LINK_NO_AN:
		*speed = IXGBE_LINK_SPEED_1GB_FULL;
		*autoneg = false;
		break;

	case IXGBE_AUTOC_LMS_10G_LINK_NO_AN:
		*speed = IXGBE_LINK_SPEED_10GB_FULL;
		*autoneg = false;
		break;

	case IXGBE_AUTOC_LMS_1G_AN:
		*speed = IXGBE_LINK_SPEED_1GB_FULL;
		*autoneg = true;
		break;

	case IXGBE_AUTOC_LMS_10G_SERIAL:
		*speed = IXGBE_LINK_SPEED_10GB_FULL;
		*autoneg = false;
		break;

	case IXGBE_AUTOC_LMS_KX4_KX_KR:
	case IXGBE_AUTOC_LMS_KX4_KX_KR_1G_AN:
		*speed = IXGBE_LINK_SPEED_UNKNOWN;
		if (autoc & IXGBE_AUTOC_KR_SUPP)
			*speed |= IXGBE_LINK_SPEED_10GB_FULL;
		if (autoc & IXGBE_AUTOC_KX4_SUPP)
			*speed |= IXGBE_LINK_SPEED_10GB_FULL;
		if (autoc & IXGBE_AUTOC_KX_SUPP)
			*speed |= IXGBE_LINK_SPEED_1GB_FULL;
		*autoneg = true;
		break;

	case IXGBE_AUTOC_LMS_KX4_KX_KR_SGMII:
		*speed = IXGBE_LINK_SPEED_100_FULL;
		if (autoc & IXGBE_AUTOC_KR_SUPP)
			*speed |= IXGBE_LINK_SPEED_10GB_FULL;
		if (autoc & IXGBE_AUTOC_KX4_SUPP)
			*speed |= IXGBE_LINK_SPEED_10GB_FULL;
		if (autoc & IXGBE_AUTOC_KX_SUPP)
			*speed |= IXGBE_LINK_SPEED_1GB_FULL;
		*autoneg = true;
		break;

	case IXGBE_AUTOC_LMS_SGMII_1G_100M:
		*speed = IXGBE_LINK_SPEED_1GB_FULL | IXGBE_LINK_SPEED_100_FULL;
		*autoneg = false;
		break;

	default:
		return IXGBE_ERR_LINK_SETUP;
	}

	if (hw->phy.multispeed_fiber) {
		*speed |= IXGBE_LINK_SPEED_10GB_FULL |
			  IXGBE_LINK_SPEED_1GB_FULL;

		/* QSFP must not enable auto-negotiation */
		if (hw->phy.media_type == ixgbe_media_type_fiber_qsfp)
			*autoneg = false;
		else
			*autoneg = true;
	}

	return 0;
}
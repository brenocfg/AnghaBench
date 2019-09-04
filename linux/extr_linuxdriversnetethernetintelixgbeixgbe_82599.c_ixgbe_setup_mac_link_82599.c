#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_5__ {scalar_t__ (* prot_autoc_write ) (struct ixgbe_hw*,int,int) ;scalar_t__ (* get_link_capabilities ) (struct ixgbe_hw*,int*,int*) ;} ;
struct TYPE_6__ {int orig_autoc; TYPE_2__ ops; scalar_t__ orig_link_settings_stored; } ;
struct TYPE_4__ {int smart_speed_active; } ;
struct ixgbe_hw {TYPE_3__ mac; TYPE_1__ phy; } ;
typedef  scalar_t__ s32 ;
typedef  int ixgbe_link_speed ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_AUTOC ; 
 int /*<<< orphan*/  IXGBE_AUTOC2 ; 
 int IXGBE_AUTOC2_10G_SERIAL_PMA_PMD_MASK ; 
 int IXGBE_AUTOC2_10G_SFI ; 
 int IXGBE_AUTOC_1G_PMA_PMD_MASK ; 
 int IXGBE_AUTOC_1G_SFI ; 
 int IXGBE_AUTOC_KR_SUPP ; 
 int IXGBE_AUTOC_KX4_KX_SUPP_MASK ; 
 int IXGBE_AUTOC_KX4_SUPP ; 
 int IXGBE_AUTOC_KX_SUPP ; 
 int IXGBE_AUTOC_LMS_10G_SERIAL ; 
 int IXGBE_AUTOC_LMS_1G_AN ; 
 int IXGBE_AUTOC_LMS_1G_LINK_NO_AN ; 
 int IXGBE_AUTOC_LMS_KX4_KX_KR ; 
 int IXGBE_AUTOC_LMS_KX4_KX_KR_1G_AN ; 
 int IXGBE_AUTOC_LMS_KX4_KX_KR_SGMII ; 
 int IXGBE_AUTOC_LMS_MASK ; 
 int IXGBE_AUTO_NEG_TIME ; 
 scalar_t__ IXGBE_ERR_AUTONEG_NOT_COMPLETE ; 
 scalar_t__ IXGBE_ERR_LINK_SETUP ; 
 int /*<<< orphan*/  IXGBE_LINKS ; 
 int IXGBE_LINKS_KX_AN_COMP ; 
 int IXGBE_LINK_SPEED_10GB_FULL ; 
 int IXGBE_LINK_SPEED_1GB_FULL ; 
 int IXGBE_LINK_SPEED_UNKNOWN ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_dbg (struct ixgbe_hw*,char*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ stub1 (struct ixgbe_hw*,int*,int*) ; 
 scalar_t__ stub2 (struct ixgbe_hw*,int,int) ; 

__attribute__((used)) static s32 ixgbe_setup_mac_link_82599(struct ixgbe_hw *hw,
				      ixgbe_link_speed speed,
				      bool autoneg_wait_to_complete)
{
	bool autoneg = false;
	s32 status;
	u32 pma_pmd_1g, link_mode, links_reg, i;
	u32 autoc2 = IXGBE_READ_REG(hw, IXGBE_AUTOC2);
	u32 pma_pmd_10g_serial = autoc2 & IXGBE_AUTOC2_10G_SERIAL_PMA_PMD_MASK;
	ixgbe_link_speed link_capabilities = IXGBE_LINK_SPEED_UNKNOWN;

	/* holds the value of AUTOC register at this current point in time */
	u32 current_autoc = IXGBE_READ_REG(hw, IXGBE_AUTOC);
	/* holds the cached value of AUTOC register */
	u32 orig_autoc = 0;
	/* temporary variable used for comparison purposes */
	u32 autoc = current_autoc;

	/* Check to see if speed passed in is supported. */
	status = hw->mac.ops.get_link_capabilities(hw, &link_capabilities,
						   &autoneg);
	if (status)
		return status;

	speed &= link_capabilities;

	if (speed == IXGBE_LINK_SPEED_UNKNOWN)
		return IXGBE_ERR_LINK_SETUP;

	/* Use stored value (EEPROM defaults) of AUTOC to find KR/KX4 support*/
	if (hw->mac.orig_link_settings_stored)
		orig_autoc = hw->mac.orig_autoc;
	else
		orig_autoc = autoc;

	link_mode = autoc & IXGBE_AUTOC_LMS_MASK;
	pma_pmd_1g = autoc & IXGBE_AUTOC_1G_PMA_PMD_MASK;

	if (link_mode == IXGBE_AUTOC_LMS_KX4_KX_KR ||
	    link_mode == IXGBE_AUTOC_LMS_KX4_KX_KR_1G_AN ||
	    link_mode == IXGBE_AUTOC_LMS_KX4_KX_KR_SGMII) {
		/* Set KX4/KX/KR support according to speed requested */
		autoc &= ~(IXGBE_AUTOC_KX4_KX_SUPP_MASK | IXGBE_AUTOC_KR_SUPP);
		if (speed & IXGBE_LINK_SPEED_10GB_FULL) {
			if (orig_autoc & IXGBE_AUTOC_KX4_SUPP)
				autoc |= IXGBE_AUTOC_KX4_SUPP;
			if ((orig_autoc & IXGBE_AUTOC_KR_SUPP) &&
			    (hw->phy.smart_speed_active == false))
				autoc |= IXGBE_AUTOC_KR_SUPP;
		}
		if (speed & IXGBE_LINK_SPEED_1GB_FULL)
			autoc |= IXGBE_AUTOC_KX_SUPP;
	} else if ((pma_pmd_1g == IXGBE_AUTOC_1G_SFI) &&
		   (link_mode == IXGBE_AUTOC_LMS_1G_LINK_NO_AN ||
		    link_mode == IXGBE_AUTOC_LMS_1G_AN)) {
		/* Switch from 1G SFI to 10G SFI if requested */
		if ((speed == IXGBE_LINK_SPEED_10GB_FULL) &&
		    (pma_pmd_10g_serial == IXGBE_AUTOC2_10G_SFI)) {
			autoc &= ~IXGBE_AUTOC_LMS_MASK;
			autoc |= IXGBE_AUTOC_LMS_10G_SERIAL;
		}
	} else if ((pma_pmd_10g_serial == IXGBE_AUTOC2_10G_SFI) &&
		   (link_mode == IXGBE_AUTOC_LMS_10G_SERIAL)) {
		/* Switch from 10G SFI to 1G SFI if requested */
		if ((speed == IXGBE_LINK_SPEED_1GB_FULL) &&
		    (pma_pmd_1g == IXGBE_AUTOC_1G_SFI)) {
			autoc &= ~IXGBE_AUTOC_LMS_MASK;
			if (autoneg)
				autoc |= IXGBE_AUTOC_LMS_1G_AN;
			else
				autoc |= IXGBE_AUTOC_LMS_1G_LINK_NO_AN;
		}
	}

	if (autoc != current_autoc) {
		/* Restart link */
		status = hw->mac.ops.prot_autoc_write(hw, autoc, false);
		if (status)
			return status;

		/* Only poll for autoneg to complete if specified to do so */
		if (autoneg_wait_to_complete) {
			if (link_mode == IXGBE_AUTOC_LMS_KX4_KX_KR ||
			    link_mode == IXGBE_AUTOC_LMS_KX4_KX_KR_1G_AN ||
			    link_mode == IXGBE_AUTOC_LMS_KX4_KX_KR_SGMII) {
				links_reg = 0; /*Just in case Autoneg time=0*/
				for (i = 0; i < IXGBE_AUTO_NEG_TIME; i++) {
					links_reg =
					       IXGBE_READ_REG(hw, IXGBE_LINKS);
					if (links_reg & IXGBE_LINKS_KX_AN_COMP)
						break;
					msleep(100);
				}
				if (!(links_reg & IXGBE_LINKS_KX_AN_COMP)) {
					status =
						IXGBE_ERR_AUTONEG_NOT_COMPLETE;
					hw_dbg(hw, "Autoneg did not complete.\n");
				}
			}
		}

		/* Add delay to filter out noises during initial link setup */
		msleep(50);
	}

	return status;
}
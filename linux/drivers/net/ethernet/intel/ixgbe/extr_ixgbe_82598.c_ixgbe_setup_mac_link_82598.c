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
typedef  scalar_t__ u32 ;
struct ixgbe_hw {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;
typedef  int ixgbe_link_speed ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_AUTOC ; 
 scalar_t__ IXGBE_AUTOC_KX4_KX_SUPP_MASK ; 
 scalar_t__ IXGBE_AUTOC_KX4_SUPP ; 
 scalar_t__ IXGBE_AUTOC_KX_SUPP ; 
 scalar_t__ IXGBE_AUTOC_LMS_KX4_AN ; 
 scalar_t__ IXGBE_AUTOC_LMS_KX4_AN_1G_AN ; 
 scalar_t__ IXGBE_AUTOC_LMS_MASK ; 
 int /*<<< orphan*/  IXGBE_ERR_LINK_SETUP ; 
 int IXGBE_LINK_SPEED_10GB_FULL ; 
 int IXGBE_LINK_SPEED_1GB_FULL ; 
 int IXGBE_LINK_SPEED_UNKNOWN ; 
 scalar_t__ IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ixgbe_get_link_capabilities_82598 (struct ixgbe_hw*,int*,int*) ; 
 int /*<<< orphan*/  ixgbe_start_mac_link_82598 (struct ixgbe_hw*,int) ; 

__attribute__((used)) static s32 ixgbe_setup_mac_link_82598(struct ixgbe_hw *hw,
				      ixgbe_link_speed speed,
				      bool autoneg_wait_to_complete)
{
	bool		 autoneg	   = false;
	ixgbe_link_speed link_capabilities = IXGBE_LINK_SPEED_UNKNOWN;
	u32              curr_autoc        = IXGBE_READ_REG(hw, IXGBE_AUTOC);
	u32              autoc             = curr_autoc;
	u32              link_mode         = autoc & IXGBE_AUTOC_LMS_MASK;

	/* Check to see if speed passed in is supported. */
	ixgbe_get_link_capabilities_82598(hw, &link_capabilities, &autoneg);
	speed &= link_capabilities;

	if (speed == IXGBE_LINK_SPEED_UNKNOWN)
		return IXGBE_ERR_LINK_SETUP;

	/* Set KX4/KX support according to speed requested */
	else if (link_mode == IXGBE_AUTOC_LMS_KX4_AN ||
		 link_mode == IXGBE_AUTOC_LMS_KX4_AN_1G_AN) {
		autoc &= ~IXGBE_AUTOC_KX4_KX_SUPP_MASK;
		if (speed & IXGBE_LINK_SPEED_10GB_FULL)
			autoc |= IXGBE_AUTOC_KX4_SUPP;
		if (speed & IXGBE_LINK_SPEED_1GB_FULL)
			autoc |= IXGBE_AUTOC_KX_SUPP;
		if (autoc != curr_autoc)
			IXGBE_WRITE_REG(hw, IXGBE_AUTOC, autoc);
	}

	/* Setup and restart the link based on the new values in
	 * ixgbe_hw This will write the AUTOC register based on the new
	 * stored values
	 */
	return ixgbe_start_mac_link_82598(hw, autoneg_wait_to_complete);
}
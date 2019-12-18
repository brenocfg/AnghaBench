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
struct igc_mac_info {int get_link_status; int /*<<< orphan*/  autoneg; } ;
struct igc_hw {struct igc_mac_info mac; } ;
typedef  int s32 ;

/* Variables and functions */
 int IGC_ERR_CONFIG ; 
 int /*<<< orphan*/  hw_dbg (char*) ; 
 int /*<<< orphan*/  igc_check_downshift (struct igc_hw*) ; 
 int /*<<< orphan*/  igc_config_collision_dist (struct igc_hw*) ; 
 int igc_config_fc_after_link_up (struct igc_hw*) ; 
 int igc_phy_has_link (struct igc_hw*,int,int /*<<< orphan*/ ,int*) ; 

s32 igc_check_for_copper_link(struct igc_hw *hw)
{
	struct igc_mac_info *mac = &hw->mac;
	s32 ret_val;
	bool link;

	/* We only want to go out to the PHY registers to see if Auto-Neg
	 * has completed and/or if our link status has changed.  The
	 * get_link_status flag is set upon receiving a Link Status
	 * Change or Rx Sequence Error interrupt.
	 */
	if (!mac->get_link_status) {
		ret_val = 0;
		goto out;
	}

	/* First we want to see if the MII Status Register reports
	 * link.  If so, then we want to get the current speed/duplex
	 * of the PHY.
	 */
	ret_val = igc_phy_has_link(hw, 1, 0, &link);
	if (ret_val)
		goto out;

	if (!link)
		goto out; /* No link detected */

	mac->get_link_status = false;

	/* Check if there was DownShift, must be checked
	 * immediately after link-up
	 */
	igc_check_downshift(hw);

	/* If we are forcing speed/duplex, then we simply return since
	 * we have already determined whether we have link or not.
	 */
	if (!mac->autoneg) {
		ret_val = -IGC_ERR_CONFIG;
		goto out;
	}

	/* Auto-Neg is enabled.  Auto Speed Detection takes care
	 * of MAC speed/duplex configuration.  So we only need to
	 * configure Collision Distance in the MAC.
	 */
	igc_config_collision_dist(hw);

	/* Configure Flow Control now that Auto-Neg has completed.
	 * First, we need to restore the desired flow control
	 * settings because we may have had to re-autoneg with a
	 * different link partner.
	 */
	ret_val = igc_config_fc_after_link_up(hw);
	if (ret_val)
		hw_dbg("Error configuring flow control\n");

out:
	return ret_val;
}
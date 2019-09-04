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
struct TYPE_5__ {scalar_t__ (* force_speed_duplex ) (struct e1000_hw*) ;} ;
struct TYPE_6__ {TYPE_2__ ops; } ;
struct TYPE_4__ {scalar_t__ autoneg; } ;
struct e1000_hw {TYPE_3__ phy; TYPE_1__ mac; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  COPPER_LINK_UP_LIMIT ; 
 int /*<<< orphan*/  hw_dbg (char*) ; 
 int /*<<< orphan*/  igb_config_collision_dist (struct e1000_hw*) ; 
 scalar_t__ igb_config_fc_after_link_up (struct e1000_hw*) ; 
 scalar_t__ igb_copper_link_autoneg (struct e1000_hw*) ; 
 scalar_t__ igb_phy_has_link (struct e1000_hw*,int /*<<< orphan*/ ,int,int*) ; 
 scalar_t__ stub1 (struct e1000_hw*) ; 

s32 igb_setup_copper_link(struct e1000_hw *hw)
{
	s32 ret_val;
	bool link;

	if (hw->mac.autoneg) {
		/* Setup autoneg and flow control advertisement and perform
		 * autonegotiation.
		 */
		ret_val = igb_copper_link_autoneg(hw);
		if (ret_val)
			goto out;
	} else {
		/* PHY will be set to 10H, 10F, 100H or 100F
		 * depending on user settings.
		 */
		hw_dbg("Forcing Speed and Duplex\n");
		ret_val = hw->phy.ops.force_speed_duplex(hw);
		if (ret_val) {
			hw_dbg("Error Forcing Speed and Duplex\n");
			goto out;
		}
	}

	/* Check link status. Wait up to 100 microseconds for link to become
	 * valid.
	 */
	ret_val = igb_phy_has_link(hw, COPPER_LINK_UP_LIMIT, 10, &link);
	if (ret_val)
		goto out;

	if (link) {
		hw_dbg("Valid link established!!!\n");
		igb_config_collision_dist(hw);
		ret_val = igb_config_fc_after_link_up(hw);
	} else {
		hw_dbg("Unable to establish link!!!\n");
	}

out:
	return ret_val;
}
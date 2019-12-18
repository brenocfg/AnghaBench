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
struct TYPE_2__ {int /*<<< orphan*/  (* check_for_rst ) (struct ixgbe_hw*) ;} ;
struct ixgbe_mbx_info {int /*<<< orphan*/  timeout; TYPE_1__ ops; } ;
struct ixgbe_mac_info {int get_link_status; scalar_t__ type; } ;
struct ixgbe_hw {struct ixgbe_mac_info mac; struct ixgbe_mbx_info mbx; } ;
typedef  int /*<<< orphan*/  s32 ;
typedef  int /*<<< orphan*/  ixgbe_link_speed ;

/* Variables and functions */
#define  IXGBE_LINKS_SPEED_100_82599 130 
#define  IXGBE_LINKS_SPEED_10G_82599 129 
#define  IXGBE_LINKS_SPEED_1G_82599 128 
 int IXGBE_LINKS_SPEED_82599 ; 
 int IXGBE_LINKS_UP ; 
 int /*<<< orphan*/  IXGBE_LINK_SPEED_100_FULL ; 
 int /*<<< orphan*/  IXGBE_LINK_SPEED_10GB_FULL ; 
 int /*<<< orphan*/  IXGBE_LINK_SPEED_1GB_FULL ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_VFLINKS ; 
 scalar_t__ ixgbe_mac_82599_vf ; 
 int /*<<< orphan*/  stub1 (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static s32 ixgbevf_hv_check_mac_link_vf(struct ixgbe_hw *hw,
					ixgbe_link_speed *speed,
					bool *link_up,
					bool autoneg_wait_to_complete)
{
	struct ixgbe_mbx_info *mbx = &hw->mbx;
	struct ixgbe_mac_info *mac = &hw->mac;
	u32 links_reg;

	/* If we were hit with a reset drop the link */
	if (!mbx->ops.check_for_rst(hw) || !mbx->timeout)
		mac->get_link_status = true;

	if (!mac->get_link_status)
		goto out;

	/* if link status is down no point in checking to see if pf is up */
	links_reg = IXGBE_READ_REG(hw, IXGBE_VFLINKS);
	if (!(links_reg & IXGBE_LINKS_UP))
		goto out;

	/* for SFP+ modules and DA cables on 82599 it can take up to 500usecs
	 * before the link status is correct
	 */
	if (mac->type == ixgbe_mac_82599_vf) {
		int i;

		for (i = 0; i < 5; i++) {
			udelay(100);
			links_reg = IXGBE_READ_REG(hw, IXGBE_VFLINKS);

			if (!(links_reg & IXGBE_LINKS_UP))
				goto out;
		}
	}

	switch (links_reg & IXGBE_LINKS_SPEED_82599) {
	case IXGBE_LINKS_SPEED_10G_82599:
		*speed = IXGBE_LINK_SPEED_10GB_FULL;
		break;
	case IXGBE_LINKS_SPEED_1G_82599:
		*speed = IXGBE_LINK_SPEED_1GB_FULL;
		break;
	case IXGBE_LINKS_SPEED_100_82599:
		*speed = IXGBE_LINK_SPEED_100_FULL;
		break;
	}

	/* if we passed all the tests above then the link is up and we no
	 * longer need to check for link
	 */
	mac->get_link_status = false;

out:
	*link_up = !mac->get_link_status;
	return 0;
}
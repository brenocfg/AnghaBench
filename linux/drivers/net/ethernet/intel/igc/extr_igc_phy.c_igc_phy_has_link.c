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
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct TYPE_3__ {scalar_t__ (* read_reg ) (struct igc_hw*,int /*<<< orphan*/ ,scalar_t__*) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct igc_hw {TYPE_2__ phy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ MII_SR_LINK_STATUS ; 
 int /*<<< orphan*/  PHY_STATUS ; 
 int /*<<< orphan*/  mdelay (scalar_t__) ; 
 scalar_t__ stub1 (struct igc_hw*,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ stub2 (struct igc_hw*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  udelay (scalar_t__) ; 

s32 igc_phy_has_link(struct igc_hw *hw, u32 iterations,
		     u32 usec_interval, bool *success)
{
	u16 i, phy_status;
	s32 ret_val = 0;

	for (i = 0; i < iterations; i++) {
		/* Some PHYs require the PHY_STATUS register to be read
		 * twice due to the link bit being sticky.  No harm doing
		 * it across the board.
		 */
		ret_val = hw->phy.ops.read_reg(hw, PHY_STATUS, &phy_status);
		if (ret_val && usec_interval > 0) {
			/* If the first read fails, another entity may have
			 * ownership of the resources, wait and try again to
			 * see if they have relinquished the resources yet.
			 */
			if (usec_interval >= 1000)
				mdelay(usec_interval / 1000);
			else
				udelay(usec_interval);
		}
		ret_val = hw->phy.ops.read_reg(hw, PHY_STATUS, &phy_status);
		if (ret_val)
			break;
		if (phy_status & MII_SR_LINK_STATUS)
			break;
		if (usec_interval >= 1000)
			mdelay(usec_interval / 1000);
		else
			udelay(usec_interval);
	}

	*success = (i < iterations) ? true : false;

	return ret_val;
}
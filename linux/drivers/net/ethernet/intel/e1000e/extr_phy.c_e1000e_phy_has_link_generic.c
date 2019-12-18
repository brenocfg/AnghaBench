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
typedef  scalar_t__ u16 ;
struct e1000_hw {int dummy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ BMSR_LSTATUS ; 
 int /*<<< orphan*/  MII_BMSR ; 
 scalar_t__ e1e_rphy (struct e1000_hw*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  msleep (scalar_t__) ; 
 int /*<<< orphan*/  udelay (scalar_t__) ; 

s32 e1000e_phy_has_link_generic(struct e1000_hw *hw, u32 iterations,
				u32 usec_interval, bool *success)
{
	s32 ret_val = 0;
	u16 i, phy_status;

	*success = false;
	for (i = 0; i < iterations; i++) {
		/* Some PHYs require the MII_BMSR register to be read
		 * twice due to the link bit being sticky.  No harm doing
		 * it across the board.
		 */
		ret_val = e1e_rphy(hw, MII_BMSR, &phy_status);
		if (ret_val) {
			/* If the first read fails, another entity may have
			 * ownership of the resources, wait and try again to
			 * see if they have relinquished the resources yet.
			 */
			if (usec_interval >= 1000)
				msleep(usec_interval / 1000);
			else
				udelay(usec_interval);
		}
		ret_val = e1e_rphy(hw, MII_BMSR, &phy_status);
		if (ret_val)
			break;
		if (phy_status & BMSR_LSTATUS) {
			*success = true;
			break;
		}
		if (usec_interval >= 1000)
			msleep(usec_interval / 1000);
		else
			udelay(usec_interval);
	}

	return ret_val;
}
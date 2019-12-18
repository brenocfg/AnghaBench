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
typedef  int u16 ;
struct e1000_phy_info {scalar_t__ media_type; scalar_t__ id; } ;
struct e1000_hw {struct e1000_phy_info phy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_PCS_STATUS_ADDR_I354 ; 
 int /*<<< orphan*/  E1000_PCS_STATUS_DEV_I354 ; 
 int E1000_PCS_STATUS_RX_LPI_RCVD ; 
 int E1000_PCS_STATUS_TX_LPI_RCVD ; 
 scalar_t__ M88E1512_E_PHY_ID ; 
 scalar_t__ M88E1543_E_PHY_ID ; 
 scalar_t__ e1000_media_type_copper ; 
 scalar_t__ igb_read_xmdio_reg (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

s32 igb_get_eee_status_i354(struct e1000_hw *hw, bool *status)
{
	struct e1000_phy_info *phy = &hw->phy;
	s32 ret_val = 0;
	u16 phy_data;

	/* Check if EEE is supported on this device. */
	if ((hw->phy.media_type != e1000_media_type_copper) ||
	    ((phy->id != M88E1543_E_PHY_ID) &&
	     (phy->id != M88E1512_E_PHY_ID)))
		goto out;

	ret_val = igb_read_xmdio_reg(hw, E1000_PCS_STATUS_ADDR_I354,
				     E1000_PCS_STATUS_DEV_I354,
				     &phy_data);
	if (ret_val)
		goto out;

	*status = phy_data & (E1000_PCS_STATUS_TX_LPI_RCVD |
			      E1000_PCS_STATUS_RX_LPI_RCVD) ? true : false;

out:
	return ret_val;
}
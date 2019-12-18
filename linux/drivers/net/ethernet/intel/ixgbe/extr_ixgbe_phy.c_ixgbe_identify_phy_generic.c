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
struct TYPE_5__ {int /*<<< orphan*/  prtad; } ;
struct TYPE_6__ {scalar_t__ type; int nw_mng_if_sel; TYPE_2__ mdio; scalar_t__ phy_semaphore_mask; } ;
struct TYPE_4__ {scalar_t__ lan_id; } ;
struct ixgbe_hw {TYPE_3__ phy; TYPE_1__ bus; } ;
typedef  int s32 ;

/* Variables and functions */
 int IXGBE_ERR_PHY_ADDR_INVALID ; 
 scalar_t__ IXGBE_GSSR_PHY0_SM ; 
 scalar_t__ IXGBE_GSSR_PHY1_SM ; 
 int IXGBE_MAX_PHY_ADDR ; 
 int IXGBE_NW_MNG_IF_SEL_MDIO_PHY_ADD ; 
 int IXGBE_NW_MNG_IF_SEL_MDIO_PHY_ADD_SHIFT ; 
 int /*<<< orphan*/  MDIO_PRTAD_NONE ; 
 scalar_t__ ixgbe_phy_unknown ; 
 scalar_t__ ixgbe_probe_phy (struct ixgbe_hw*,int) ; 

s32 ixgbe_identify_phy_generic(struct ixgbe_hw *hw)
{
	u32 phy_addr;
	u32 status = IXGBE_ERR_PHY_ADDR_INVALID;

	if (!hw->phy.phy_semaphore_mask) {
		if (hw->bus.lan_id)
			hw->phy.phy_semaphore_mask = IXGBE_GSSR_PHY1_SM;
		else
			hw->phy.phy_semaphore_mask = IXGBE_GSSR_PHY0_SM;
	}

	if (hw->phy.type != ixgbe_phy_unknown)
		return 0;

	if (hw->phy.nw_mng_if_sel) {
		phy_addr = (hw->phy.nw_mng_if_sel &
			    IXGBE_NW_MNG_IF_SEL_MDIO_PHY_ADD) >>
			   IXGBE_NW_MNG_IF_SEL_MDIO_PHY_ADD_SHIFT;
		if (ixgbe_probe_phy(hw, phy_addr))
			return 0;
		else
			return IXGBE_ERR_PHY_ADDR_INVALID;
	}

	for (phy_addr = 0; phy_addr < IXGBE_MAX_PHY_ADDR; phy_addr++) {
		if (ixgbe_probe_phy(hw, phy_addr)) {
			status = 0;
			break;
		}
	}

	/* Certain media types do not have a phy so an address will not
	 * be found and the code will take this path.  Caller has to
	 * decide if it is an error or not.
	 */
	if (status)
		hw->phy.mdio.prtad = MDIO_PRTAD_NONE;

	return status;
}
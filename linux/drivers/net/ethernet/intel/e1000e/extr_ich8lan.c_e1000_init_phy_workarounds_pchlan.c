#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_10__ {int type; } ;
struct TYPE_8__ {scalar_t__ (* check_reset_block ) (struct e1000_hw*) ;int /*<<< orphan*/  (* release ) (struct e1000_hw*) ;scalar_t__ (* acquire ) (struct e1000_hw*) ;} ;
struct TYPE_9__ {TYPE_3__ ops; } ;
struct TYPE_6__ {int /*<<< orphan*/  ulp_state; } ;
struct TYPE_7__ {TYPE_1__ ich8lan; } ;
struct e1000_hw {TYPE_5__ mac; TYPE_4__ phy; TYPE_2__ dev_spec; struct e1000_adapter* adapter; } ;
struct e1000_adapter {int dummy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL_EXT ; 
 int E1000_CTRL_EXT_FORCE_SMBUS ; 
 scalar_t__ E1000_ERR_PHY ; 
 int E1000_ICH_FWSM_FW_VALID ; 
 int /*<<< orphan*/  FWSM ; 
 int /*<<< orphan*/  e1000_disable_ulp_lpt_lp (struct e1000_hw*,int) ; 
 int /*<<< orphan*/  e1000_gate_hw_phy_config_ich8lan (struct e1000_hw*,int) ; 
#define  e1000_pch2lan 132 
#define  e1000_pch_cnp 131 
#define  e1000_pch_lpt 130 
#define  e1000_pch_spt 129 
#define  e1000_pchlan 128 
 int /*<<< orphan*/  e1000_phy_is_accessible_pchlan (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000_toggle_lanphypc_pch_lpt (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000_ulp_state_unknown ; 
 scalar_t__ e1000e_phy_hw_reset_generic (struct e1000_hw*) ; 
 int /*<<< orphan*/  e_dbg (char*) ; 
 int /*<<< orphan*/  e_err (char*) ; 
 int er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ stub1 (struct e1000_hw*) ; 
 scalar_t__ stub2 (struct e1000_hw*) ; 
 int /*<<< orphan*/  stub3 (struct e1000_hw*) ; 
 scalar_t__ stub4 (struct e1000_hw*) ; 
 scalar_t__ stub5 (struct e1000_hw*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static s32 e1000_init_phy_workarounds_pchlan(struct e1000_hw *hw)
{
	struct e1000_adapter *adapter = hw->adapter;
	u32 mac_reg, fwsm = er32(FWSM);
	s32 ret_val;

	/* Gate automatic PHY configuration by hardware on managed and
	 * non-managed 82579 and newer adapters.
	 */
	e1000_gate_hw_phy_config_ich8lan(hw, true);

	/* It is not possible to be certain of the current state of ULP
	 * so forcibly disable it.
	 */
	hw->dev_spec.ich8lan.ulp_state = e1000_ulp_state_unknown;
	e1000_disable_ulp_lpt_lp(hw, true);

	ret_val = hw->phy.ops.acquire(hw);
	if (ret_val) {
		e_dbg("Failed to initialize PHY flow\n");
		goto out;
	}

	/* The MAC-PHY interconnect may be in SMBus mode.  If the PHY is
	 * inaccessible and resetting the PHY is not blocked, toggle the
	 * LANPHYPC Value bit to force the interconnect to PCIe mode.
	 */
	switch (hw->mac.type) {
	case e1000_pch_lpt:
	case e1000_pch_spt:
	case e1000_pch_cnp:
		if (e1000_phy_is_accessible_pchlan(hw))
			break;

		/* Before toggling LANPHYPC, see if PHY is accessible by
		 * forcing MAC to SMBus mode first.
		 */
		mac_reg = er32(CTRL_EXT);
		mac_reg |= E1000_CTRL_EXT_FORCE_SMBUS;
		ew32(CTRL_EXT, mac_reg);

		/* Wait 50 milliseconds for MAC to finish any retries
		 * that it might be trying to perform from previous
		 * attempts to acknowledge any phy read requests.
		 */
		msleep(50);

		/* fall-through */
	case e1000_pch2lan:
		if (e1000_phy_is_accessible_pchlan(hw))
			break;

		/* fall-through */
	case e1000_pchlan:
		if ((hw->mac.type == e1000_pchlan) &&
		    (fwsm & E1000_ICH_FWSM_FW_VALID))
			break;

		if (hw->phy.ops.check_reset_block(hw)) {
			e_dbg("Required LANPHYPC toggle blocked by ME\n");
			ret_val = -E1000_ERR_PHY;
			break;
		}

		/* Toggle LANPHYPC Value bit */
		e1000_toggle_lanphypc_pch_lpt(hw);
		if (hw->mac.type >= e1000_pch_lpt) {
			if (e1000_phy_is_accessible_pchlan(hw))
				break;

			/* Toggling LANPHYPC brings the PHY out of SMBus mode
			 * so ensure that the MAC is also out of SMBus mode
			 */
			mac_reg = er32(CTRL_EXT);
			mac_reg &= ~E1000_CTRL_EXT_FORCE_SMBUS;
			ew32(CTRL_EXT, mac_reg);

			if (e1000_phy_is_accessible_pchlan(hw))
				break;

			ret_val = -E1000_ERR_PHY;
		}
		break;
	default:
		break;
	}

	hw->phy.ops.release(hw);
	if (!ret_val) {

		/* Check to see if able to reset PHY.  Print error if not */
		if (hw->phy.ops.check_reset_block(hw)) {
			e_err("Reset blocked by ME\n");
			goto out;
		}

		/* Reset the PHY before any access to it.  Doing so, ensures
		 * that the PHY is in a known good state before we read/write
		 * PHY registers.  The generic reset is sufficient here,
		 * because we haven't determined the PHY type yet.
		 */
		ret_val = e1000e_phy_hw_reset_generic(hw);
		if (ret_val)
			goto out;

		/* On a successful reset, possibly need to wait for the PHY
		 * to quiesce to an accessible state before returning control
		 * to the calling function.  If the PHY does not quiesce, then
		 * return E1000E_BLK_PHY_RESET, as this is the condition that
		 *  the PHY is in.
		 */
		ret_val = hw->phy.ops.check_reset_block(hw);
		if (ret_val)
			e_err("ME blocked access to PHY after reset\n");
	}

out:
	/* Ungate automatic PHY configuration on non-managed 82579 */
	if ((hw->mac.type == e1000_pch2lan) &&
	    !(fwsm & E1000_ICH_FWSM_FW_VALID)) {
		usleep_range(10000, 11000);
		e1000_gate_hw_phy_config_ich8lan(hw, false);
	}

	return ret_val;
}
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
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct e1000_phy_info {int addr; } ;
struct e1000_hw {struct e1000_phy_info phy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_ERR_PARAM ; 
 int /*<<< orphan*/  E1000_ERR_PHY ; 
 int E1000_GEN_POLL_TIMEOUT ; 
 int /*<<< orphan*/  E1000_MDIC ; 
 int E1000_MDIC_ERROR ; 
 int E1000_MDIC_OP_WRITE ; 
 int E1000_MDIC_PHY_SHIFT ; 
 int E1000_MDIC_READY ; 
 int E1000_MDIC_REG_SHIFT ; 
 int MAX_PHY_REG_ADDRESS ; 
 int /*<<< orphan*/  hw_dbg (char*,...) ; 
 int rd32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,int) ; 

s32 igb_write_phy_reg_mdic(struct e1000_hw *hw, u32 offset, u16 data)
{
	struct e1000_phy_info *phy = &hw->phy;
	u32 i, mdic = 0;
	s32 ret_val = 0;

	if (offset > MAX_PHY_REG_ADDRESS) {
		hw_dbg("PHY Address %d is out of range\n", offset);
		ret_val = -E1000_ERR_PARAM;
		goto out;
	}

	/* Set up Op-code, Phy Address, and register offset in the MDI
	 * Control register.  The MAC will take care of interfacing with the
	 * PHY to retrieve the desired data.
	 */
	mdic = (((u32)data) |
		(offset << E1000_MDIC_REG_SHIFT) |
		(phy->addr << E1000_MDIC_PHY_SHIFT) |
		(E1000_MDIC_OP_WRITE));

	wr32(E1000_MDIC, mdic);

	/* Poll the ready bit to see if the MDI read completed
	 * Increasing the time out as testing showed failures with
	 * the lower time out
	 */
	for (i = 0; i < (E1000_GEN_POLL_TIMEOUT * 3); i++) {
		udelay(50);
		mdic = rd32(E1000_MDIC);
		if (mdic & E1000_MDIC_READY)
			break;
	}
	if (!(mdic & E1000_MDIC_READY)) {
		hw_dbg("MDI Write did not complete\n");
		ret_val = -E1000_ERR_PHY;
		goto out;
	}
	if (mdic & E1000_MDIC_ERROR) {
		hw_dbg("MDI Error\n");
		ret_val = -E1000_ERR_PHY;
		goto out;
	}

out:
	return ret_val;
}
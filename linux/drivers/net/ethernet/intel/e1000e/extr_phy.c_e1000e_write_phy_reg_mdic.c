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
typedef  scalar_t__ u16 ;
struct e1000_phy_info {int addr; } ;
struct TYPE_2__ {scalar_t__ type; } ;
struct e1000_hw {TYPE_1__ mac; struct e1000_phy_info phy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_ERR_PARAM ; 
 int /*<<< orphan*/  E1000_ERR_PHY ; 
 int E1000_GEN_POLL_TIMEOUT ; 
 int E1000_MDIC_ERROR ; 
 int E1000_MDIC_OP_WRITE ; 
 int E1000_MDIC_PHY_SHIFT ; 
 int E1000_MDIC_READY ; 
 int E1000_MDIC_REG_MASK ; 
 int E1000_MDIC_REG_SHIFT ; 
 int MAX_PHY_REG_ADDRESS ; 
 int /*<<< orphan*/  MDIC ; 
 scalar_t__ e1000_pch2lan ; 
 int /*<<< orphan*/  e_dbg (char*,...) ; 
 int er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

s32 e1000e_write_phy_reg_mdic(struct e1000_hw *hw, u32 offset, u16 data)
{
	struct e1000_phy_info *phy = &hw->phy;
	u32 i, mdic = 0;

	if (offset > MAX_PHY_REG_ADDRESS) {
		e_dbg("PHY Address %d is out of range\n", offset);
		return -E1000_ERR_PARAM;
	}

	/* Set up Op-code, Phy Address, and register offset in the MDI
	 * Control register.  The MAC will take care of interfacing with the
	 * PHY to retrieve the desired data.
	 */
	mdic = (((u32)data) |
		(offset << E1000_MDIC_REG_SHIFT) |
		(phy->addr << E1000_MDIC_PHY_SHIFT) |
		(E1000_MDIC_OP_WRITE));

	ew32(MDIC, mdic);

	/* Poll the ready bit to see if the MDI read completed
	 * Increasing the time out as testing showed failures with
	 * the lower time out
	 */
	for (i = 0; i < (E1000_GEN_POLL_TIMEOUT * 3); i++) {
		udelay(50);
		mdic = er32(MDIC);
		if (mdic & E1000_MDIC_READY)
			break;
	}
	if (!(mdic & E1000_MDIC_READY)) {
		e_dbg("MDI Write did not complete\n");
		return -E1000_ERR_PHY;
	}
	if (mdic & E1000_MDIC_ERROR) {
		e_dbg("MDI Error\n");
		return -E1000_ERR_PHY;
	}
	if (((mdic & E1000_MDIC_REG_MASK) >> E1000_MDIC_REG_SHIFT) != offset) {
		e_dbg("MDI Write offset error - requested %d, returned %d\n",
		      offset,
		      (mdic & E1000_MDIC_REG_MASK) >> E1000_MDIC_REG_SHIFT);
		return -E1000_ERR_PHY;
	}

	/* Allow some time after each MDIC transaction to avoid
	 * reading duplicate data in the next MDIC transaction.
	 */
	if (hw->mac.type == e1000_pch2lan)
		udelay(100);

	return 0;
}
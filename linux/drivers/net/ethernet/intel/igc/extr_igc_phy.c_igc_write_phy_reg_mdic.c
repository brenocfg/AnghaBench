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
struct igc_phy_info {scalar_t__ addr; } ;
struct igc_hw {struct igc_phy_info phy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  IGC_ERR_PARAM ; 
 int /*<<< orphan*/  IGC_ERR_PHY ; 
 scalar_t__ IGC_GEN_POLL_TIMEOUT ; 
 int /*<<< orphan*/  IGC_MDIC ; 
 scalar_t__ IGC_MDIC_ERROR ; 
 scalar_t__ IGC_MDIC_OP_WRITE ; 
 scalar_t__ IGC_MDIC_PHY_SHIFT ; 
 scalar_t__ IGC_MDIC_READY ; 
 scalar_t__ IGC_MDIC_REG_SHIFT ; 
 scalar_t__ MAX_PHY_REG_ADDRESS ; 
 int /*<<< orphan*/  hw_dbg (char*,...) ; 
 scalar_t__ rd32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static s32 igc_write_phy_reg_mdic(struct igc_hw *hw, u32 offset, u16 data)
{
	struct igc_phy_info *phy = &hw->phy;
	u32 i, mdic = 0;
	s32 ret_val = 0;

	if (offset > MAX_PHY_REG_ADDRESS) {
		hw_dbg("PHY Address %d is out of range\n", offset);
		ret_val = -IGC_ERR_PARAM;
		goto out;
	}

	/* Set up Op-code, Phy Address, and register offset in the MDI
	 * Control register.  The MAC will take care of interfacing with the
	 * PHY to write the desired data.
	 */
	mdic = (((u32)data) |
		(offset << IGC_MDIC_REG_SHIFT) |
		(phy->addr << IGC_MDIC_PHY_SHIFT) |
		(IGC_MDIC_OP_WRITE));

	wr32(IGC_MDIC, mdic);

	/* Poll the ready bit to see if the MDI read completed
	 * Increasing the time out as testing showed failures with
	 * the lower time out
	 */
	for (i = 0; i < IGC_GEN_POLL_TIMEOUT; i++) {
		usleep_range(500, 1000);
		mdic = rd32(IGC_MDIC);
		if (mdic & IGC_MDIC_READY)
			break;
	}
	if (!(mdic & IGC_MDIC_READY)) {
		hw_dbg("MDI Write did not complete\n");
		ret_val = -IGC_ERR_PHY;
		goto out;
	}
	if (mdic & IGC_MDIC_ERROR) {
		hw_dbg("MDI Error\n");
		ret_val = -IGC_ERR_PHY;
		goto out;
	}

out:
	return ret_val;
}
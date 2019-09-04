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
typedef  int u16 ;
struct TYPE_2__ {int addr; } ;
struct e1000_hw {TYPE_1__ phy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int BM_PORT_CTRL_PAGE ; 
 int BM_WUC_ENABLE_BIT ; 
 int /*<<< orphan*/  BM_WUC_ENABLE_REG ; 
 int BM_WUC_HOST_WU_BIT ; 
 int BM_WUC_ME_WU_BIT ; 
 int BM_WUC_PAGE ; 
 int IGP_PAGE_SHIFT ; 
 scalar_t__ e1000_set_page_igp (struct e1000_hw*,int) ; 
 scalar_t__ e1000e_read_phy_reg_mdic (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ e1000e_write_phy_reg_mdic (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  e_dbg (char*,...) ; 

s32 e1000_enable_phy_wakeup_reg_access_bm(struct e1000_hw *hw, u16 *phy_reg)
{
	s32 ret_val;
	u16 temp;

	/* All page select, port ctrl and wakeup registers use phy address 1 */
	hw->phy.addr = 1;

	/* Select Port Control Registers page */
	ret_val = e1000_set_page_igp(hw, (BM_PORT_CTRL_PAGE << IGP_PAGE_SHIFT));
	if (ret_val) {
		e_dbg("Could not set Port Control page\n");
		return ret_val;
	}

	ret_val = e1000e_read_phy_reg_mdic(hw, BM_WUC_ENABLE_REG, phy_reg);
	if (ret_val) {
		e_dbg("Could not read PHY register %d.%d\n",
		      BM_PORT_CTRL_PAGE, BM_WUC_ENABLE_REG);
		return ret_val;
	}

	/* Enable both PHY wakeup mode and Wakeup register page writes.
	 * Prevent a power state change by disabling ME and Host PHY wakeup.
	 */
	temp = *phy_reg;
	temp |= BM_WUC_ENABLE_BIT;
	temp &= ~(BM_WUC_ME_WU_BIT | BM_WUC_HOST_WU_BIT);

	ret_val = e1000e_write_phy_reg_mdic(hw, BM_WUC_ENABLE_REG, temp);
	if (ret_val) {
		e_dbg("Could not write PHY register %d.%d\n",
		      BM_PORT_CTRL_PAGE, BM_WUC_ENABLE_REG);
		return ret_val;
	}

	/* Select Host Wakeup Registers page - caller now able to write
	 * registers on the Wakeup registers page
	 */
	return e1000_set_page_igp(hw, (BM_WUC_PAGE << IGP_PAGE_SHIFT));
}
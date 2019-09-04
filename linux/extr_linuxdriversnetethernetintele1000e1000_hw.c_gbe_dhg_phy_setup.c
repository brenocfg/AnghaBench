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
struct e1000_hw {int phy_type; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_AUX ; 
 int E1000_CTL_AUX_RMII ; 
 int /*<<< orphan*/  E1000_ERR_PHY_TYPE ; 
 int /*<<< orphan*/  E1000_SUCCESS ; 
 int /*<<< orphan*/  E1000_WRITE_FLUSH () ; 
 int /*<<< orphan*/  e1000_copper_link_rtl_setup (struct e1000_hw*) ; 
#define  e1000_phy_8201 129 
#define  e1000_phy_8211 128 
 int /*<<< orphan*/  e_dbg (char*) ; 
 int er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static s32 gbe_dhg_phy_setup(struct e1000_hw *hw)
{
	s32 ret_val;
	u32 ctrl_aux;

	switch (hw->phy_type) {
	case e1000_phy_8211:
		ret_val = e1000_copper_link_rtl_setup(hw);
		if (ret_val) {
			e_dbg("e1000_copper_link_rtl_setup failed!\n");
			return ret_val;
		}
		break;
	case e1000_phy_8201:
		/* Set RMII mode */
		ctrl_aux = er32(CTL_AUX);
		ctrl_aux |= E1000_CTL_AUX_RMII;
		ew32(CTL_AUX, ctrl_aux);
		E1000_WRITE_FLUSH();

		/* Disable the J/K bits required for receive */
		ctrl_aux = er32(CTL_AUX);
		ctrl_aux |= 0x4;
		ctrl_aux &= ~0x2;
		ew32(CTL_AUX, ctrl_aux);
		E1000_WRITE_FLUSH();
		ret_val = e1000_copper_link_rtl_setup(hw);

		if (ret_val) {
			e_dbg("e1000_copper_link_rtl_setup failed!\n");
			return ret_val;
		}
		break;
	default:
		e_dbg("Error Resetting the PHY\n");
		return E1000_ERR_PHY_TYPE;
	}

	return E1000_SUCCESS;
}
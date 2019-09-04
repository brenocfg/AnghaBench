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
typedef  int /*<<< orphan*/  u16 ;
struct e1000_hw {int dummy; } ;
struct e1000_adapter {struct e1000_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  M88E1000_EPSCR_TX_CLK_25 ; 
 int /*<<< orphan*/  M88E1000_EXT_PHY_SPEC_CTRL ; 
 int /*<<< orphan*/  M88E1000_PHY_SPEC_CTRL ; 
 int /*<<< orphan*/  M88E1000_PSCR_ASSERT_CRS_ON_TX ; 
 int /*<<< orphan*/  e1000_read_phy_reg (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  e1000_write_phy_reg (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void e1000_phy_reset_clk_and_crs(struct e1000_adapter *adapter)
{
	struct e1000_hw *hw = &adapter->hw;
	u16 phy_reg;

	/* Because we reset the PHY above, we need to re-force TX_CLK in the
	 * Extended PHY Specific Control Register to 25MHz clock.  This
	 * value defaults back to a 2.5MHz clock when the PHY is reset.
	 */
	e1000_read_phy_reg(hw, M88E1000_EXT_PHY_SPEC_CTRL, &phy_reg);
	phy_reg |= M88E1000_EPSCR_TX_CLK_25;
	e1000_write_phy_reg(hw, M88E1000_EXT_PHY_SPEC_CTRL, phy_reg);

	/* In addition, because of the s/w reset above, we need to enable
	 * CRS on TX.  This must be set for both full and half duplex
	 * operation.
	 */
	e1000_read_phy_reg(hw, M88E1000_PHY_SPEC_CTRL, &phy_reg);
	phy_reg |= M88E1000_PSCR_ASSERT_CRS_ON_TX;
	e1000_write_phy_reg(hw, M88E1000_PHY_SPEC_CTRL, phy_reg);
}
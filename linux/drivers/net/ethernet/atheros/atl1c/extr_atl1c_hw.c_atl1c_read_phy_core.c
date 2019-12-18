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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct atl1c_hw {scalar_t__ nic_type; scalar_t__ hibernate; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT_READ_REG (struct atl1c_hw*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  AT_WRITE_REG (struct atl1c_hw*,int /*<<< orphan*/ ,int) ; 
 int FIELDX (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ FIELD_GETX (int,int /*<<< orphan*/ ) ; 
 scalar_t__ MDIO_CTRL_CLK_25_128 ; 
 scalar_t__ MDIO_CTRL_CLK_25_4 ; 
 int /*<<< orphan*/  MDIO_CTRL_CLK_SEL ; 
 int /*<<< orphan*/  MDIO_CTRL_DATA ; 
 int MDIO_CTRL_MODE_EXT ; 
 int MDIO_CTRL_OP_READ ; 
 int /*<<< orphan*/  MDIO_CTRL_REG ; 
 int MDIO_CTRL_SPRES_PRMBL ; 
 int MDIO_CTRL_START ; 
 int /*<<< orphan*/  MDIO_EXTN_DEVAD ; 
 int /*<<< orphan*/  MDIO_EXTN_REG ; 
 int /*<<< orphan*/  REG_MDIO_CTRL ; 
 int /*<<< orphan*/  REG_MDIO_EXTN ; 
 scalar_t__ athr_l1d_2 ; 
 scalar_t__ athr_l2c_b2 ; 
 int /*<<< orphan*/  atl1c_start_phy_polling (struct atl1c_hw*,scalar_t__) ; 
 int /*<<< orphan*/  atl1c_stop_phy_polling (struct atl1c_hw*) ; 
 int /*<<< orphan*/  atl1c_wait_mdio_idle (struct atl1c_hw*) ; 

int atl1c_read_phy_core(struct atl1c_hw *hw, bool ext, u8 dev,
			u16 reg, u16 *phy_data)
{
	u32 val;
	u16 clk_sel = MDIO_CTRL_CLK_25_4;

	atl1c_stop_phy_polling(hw);

	*phy_data = 0;

	/* only l2c_b2 & l1d_2 could use slow clock */
	if ((hw->nic_type == athr_l2c_b2 || hw->nic_type == athr_l1d_2) &&
		hw->hibernate)
		clk_sel = MDIO_CTRL_CLK_25_128;
	if (ext) {
		val = FIELDX(MDIO_EXTN_DEVAD, dev) | FIELDX(MDIO_EXTN_REG, reg);
		AT_WRITE_REG(hw, REG_MDIO_EXTN, val);
		val = MDIO_CTRL_SPRES_PRMBL |
			FIELDX(MDIO_CTRL_CLK_SEL, clk_sel) |
			MDIO_CTRL_START |
			MDIO_CTRL_MODE_EXT |
			MDIO_CTRL_OP_READ;
	} else {
		val = MDIO_CTRL_SPRES_PRMBL |
			FIELDX(MDIO_CTRL_CLK_SEL, clk_sel) |
			FIELDX(MDIO_CTRL_REG, reg) |
			MDIO_CTRL_START |
			MDIO_CTRL_OP_READ;
	}
	AT_WRITE_REG(hw, REG_MDIO_CTRL, val);

	if (!atl1c_wait_mdio_idle(hw))
		return -1;

	AT_READ_REG(hw, REG_MDIO_CTRL, &val);
	*phy_data = (u16)FIELD_GETX(val, MDIO_CTRL_DATA);

	atl1c_start_phy_polling(hw, clk_sel);

	return 0;
}
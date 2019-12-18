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
typedef  int u16 ;
struct atl1_hw {scalar_t__ hw_addr; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  ATLX_ERR_PHY ; 
 int MDIO_BUSY ; 
 int MDIO_CLK_25_4 ; 
 int MDIO_CLK_SEL_SHIFT ; 
 int MDIO_REG_ADDR_MASK ; 
 int MDIO_REG_ADDR_SHIFT ; 
 int MDIO_RW ; 
 int MDIO_START ; 
 int MDIO_SUP_PREAMBLE ; 
 int MDIO_WAIT_TIMES ; 
 scalar_t__ REG_MDIO_CTRL ; 
 int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static s32 atl1_read_phy_reg(struct atl1_hw *hw, u16 reg_addr, u16 *phy_data)
{
	u32 val;
	int i;

	val = ((u32) (reg_addr & MDIO_REG_ADDR_MASK)) << MDIO_REG_ADDR_SHIFT |
		MDIO_START | MDIO_SUP_PREAMBLE | MDIO_RW | MDIO_CLK_25_4 <<
		MDIO_CLK_SEL_SHIFT;
	iowrite32(val, hw->hw_addr + REG_MDIO_CTRL);
	ioread32(hw->hw_addr + REG_MDIO_CTRL);

	for (i = 0; i < MDIO_WAIT_TIMES; i++) {
		udelay(2);
		val = ioread32(hw->hw_addr + REG_MDIO_CTRL);
		if (!(val & (MDIO_START | MDIO_BUSY)))
			break;
	}
	if (!(val & (MDIO_START | MDIO_BUSY))) {
		*phy_data = (u16) val;
		return 0;
	}
	return ATLX_ERR_PHY;
}
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
typedef  int /*<<< orphan*/  u32 ;
struct phy_device {scalar_t__ interface; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADIN1300_GE_RMII_CFG_REG ; 
 int ADIN1300_GE_RMII_EN ; 
 int ADIN1300_GE_RMII_FIFO_DEPTH_MSK ; 
 int ADIN1300_GE_RMII_FIFO_DEPTH_SEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ADIN1300_RMII_8_BITS ; 
 int /*<<< orphan*/  MDIO_MMD_VEND1 ; 
 scalar_t__ PHY_INTERFACE_MODE_RMII ; 
 int /*<<< orphan*/  adin_get_reg_value (struct phy_device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adin_rmii_fifo_depths ; 
 int phy_clear_bits_mmd (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int phy_read_mmd (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int phy_write_mmd (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int adin_config_rmii_mode(struct phy_device *phydev)
{
	u32 val;
	int reg;

	if (phydev->interface != PHY_INTERFACE_MODE_RMII)
		return phy_clear_bits_mmd(phydev, MDIO_MMD_VEND1,
					  ADIN1300_GE_RMII_CFG_REG,
					  ADIN1300_GE_RMII_EN);

	reg = phy_read_mmd(phydev, MDIO_MMD_VEND1, ADIN1300_GE_RMII_CFG_REG);
	if (reg < 0)
		return reg;

	reg |= ADIN1300_GE_RMII_EN;

	val = adin_get_reg_value(phydev, "adi,fifo-depth-bits",
				 adin_rmii_fifo_depths,
				 ADIN1300_RMII_8_BITS);

	reg &= ~ADIN1300_GE_RMII_FIFO_DEPTH_MSK;
	reg |= ADIN1300_GE_RMII_FIFO_DEPTH_SEL(val);

	return phy_write_mmd(phydev, MDIO_MMD_VEND1,
			     ADIN1300_GE_RMII_CFG_REG, reg);
}
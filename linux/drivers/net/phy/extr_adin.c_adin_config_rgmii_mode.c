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
 int /*<<< orphan*/  ADIN1300_GE_RGMII_CFG_REG ; 
 int ADIN1300_GE_RGMII_EN ; 
 int ADIN1300_GE_RGMII_GTX_MSK ; 
 int ADIN1300_GE_RGMII_GTX_SEL (int /*<<< orphan*/ ) ; 
 int ADIN1300_GE_RGMII_RXID_EN ; 
 int ADIN1300_GE_RGMII_RX_MSK ; 
 int ADIN1300_GE_RGMII_RX_SEL (int /*<<< orphan*/ ) ; 
 int ADIN1300_GE_RGMII_TXID_EN ; 
 int /*<<< orphan*/  ADIN1300_RGMII_2_00_NS ; 
 int /*<<< orphan*/  MDIO_MMD_VEND1 ; 
 scalar_t__ PHY_INTERFACE_MODE_RGMII_ID ; 
 scalar_t__ PHY_INTERFACE_MODE_RGMII_RXID ; 
 scalar_t__ PHY_INTERFACE_MODE_RGMII_TXID ; 
 int /*<<< orphan*/  adin_get_reg_value (struct phy_device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adin_rgmii_delays ; 
 int phy_clear_bits_mmd (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  phy_interface_is_rgmii (struct phy_device*) ; 
 int phy_read_mmd (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int phy_write_mmd (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int adin_config_rgmii_mode(struct phy_device *phydev)
{
	u32 val;
	int reg;

	if (!phy_interface_is_rgmii(phydev))
		return phy_clear_bits_mmd(phydev, MDIO_MMD_VEND1,
					  ADIN1300_GE_RGMII_CFG_REG,
					  ADIN1300_GE_RGMII_EN);

	reg = phy_read_mmd(phydev, MDIO_MMD_VEND1, ADIN1300_GE_RGMII_CFG_REG);
	if (reg < 0)
		return reg;

	reg |= ADIN1300_GE_RGMII_EN;

	if (phydev->interface == PHY_INTERFACE_MODE_RGMII_ID ||
	    phydev->interface == PHY_INTERFACE_MODE_RGMII_RXID) {
		reg |= ADIN1300_GE_RGMII_RXID_EN;

		val = adin_get_reg_value(phydev, "adi,rx-internal-delay-ps",
					 adin_rgmii_delays,
					 ADIN1300_RGMII_2_00_NS);
		reg &= ~ADIN1300_GE_RGMII_RX_MSK;
		reg |= ADIN1300_GE_RGMII_RX_SEL(val);
	} else {
		reg &= ~ADIN1300_GE_RGMII_RXID_EN;
	}

	if (phydev->interface == PHY_INTERFACE_MODE_RGMII_ID ||
	    phydev->interface == PHY_INTERFACE_MODE_RGMII_TXID) {
		reg |= ADIN1300_GE_RGMII_TXID_EN;

		val = adin_get_reg_value(phydev, "adi,tx-internal-delay-ps",
					 adin_rgmii_delays,
					 ADIN1300_RGMII_2_00_NS);
		reg &= ~ADIN1300_GE_RGMII_GTX_MSK;
		reg |= ADIN1300_GE_RGMII_GTX_SEL(val);
	} else {
		reg &= ~ADIN1300_GE_RGMII_TXID_EN;
	}

	return phy_write_mmd(phydev, MDIO_MMD_VEND1,
			     ADIN1300_GE_RGMII_CFG_REG, reg);
}
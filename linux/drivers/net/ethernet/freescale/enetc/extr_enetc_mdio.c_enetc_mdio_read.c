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
struct mii_bus {int /*<<< orphan*/  dev; struct enetc_mdio_priv* priv; } ;
struct enetc_mdio_priv {struct enetc_hw* hw; } ;
struct enetc_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENETC_MDC_DIV ; 
 int /*<<< orphan*/  MDIO_ADDR ; 
 int /*<<< orphan*/  MDIO_CFG ; 
 int MDIO_CFG_CLKDIV (int /*<<< orphan*/ ) ; 
 int MDIO_CFG_ENC45 ; 
 int MDIO_CFG_NEG ; 
 int MDIO_CFG_RD_ER ; 
 int /*<<< orphan*/  MDIO_CTL ; 
 int MDIO_CTL_DEV_ADDR (int) ; 
 int MDIO_CTL_PORT_ADDR (int) ; 
 int MDIO_CTL_READ ; 
 int /*<<< orphan*/  MDIO_DATA ; 
 int MII_ADDR_C45 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int,int) ; 
 int enetc_mdio_rd (struct enetc_hw*,int /*<<< orphan*/ ) ; 
 int enetc_mdio_wait_complete (struct enetc_hw*) ; 
 int /*<<< orphan*/  enetc_mdio_wr (struct enetc_hw*,int /*<<< orphan*/ ,int) ; 

int enetc_mdio_read(struct mii_bus *bus, int phy_id, int regnum)
{
	struct enetc_mdio_priv *mdio_priv = bus->priv;
	struct enetc_hw *hw = mdio_priv->hw;
	u32 mdio_ctl, mdio_cfg;
	u16 dev_addr, value;
	int ret;

	mdio_cfg = MDIO_CFG_CLKDIV(ENETC_MDC_DIV) | MDIO_CFG_NEG;
	if (regnum & MII_ADDR_C45) {
		dev_addr = (regnum >> 16) & 0x1f;
		mdio_cfg |= MDIO_CFG_ENC45;
	} else {
		dev_addr = regnum & 0x1f;
		mdio_cfg &= ~MDIO_CFG_ENC45;
	}

	enetc_mdio_wr(hw, MDIO_CFG, mdio_cfg);

	ret = enetc_mdio_wait_complete(hw);
	if (ret)
		return ret;

	/* set port and device addr */
	mdio_ctl = MDIO_CTL_PORT_ADDR(phy_id) | MDIO_CTL_DEV_ADDR(dev_addr);
	enetc_mdio_wr(hw, MDIO_CTL, mdio_ctl);

	/* set the register address */
	if (regnum & MII_ADDR_C45) {
		enetc_mdio_wr(hw, MDIO_ADDR, regnum & 0xffff);

		ret = enetc_mdio_wait_complete(hw);
		if (ret)
			return ret;
	}

	/* initiate the read */
	enetc_mdio_wr(hw, MDIO_CTL, mdio_ctl | MDIO_CTL_READ);

	ret = enetc_mdio_wait_complete(hw);
	if (ret)
		return ret;

	/* return all Fs if nothing was there */
	if (enetc_mdio_rd(hw, MDIO_CFG) & MDIO_CFG_RD_ER) {
		dev_dbg(&bus->dev,
			"Error while reading PHY%d reg at %d.%hhu\n",
			phy_id, dev_addr, regnum);
		return 0xffff;
	}

	value = enetc_mdio_rd(hw, MDIO_DATA) & 0xffff;

	return value;
}
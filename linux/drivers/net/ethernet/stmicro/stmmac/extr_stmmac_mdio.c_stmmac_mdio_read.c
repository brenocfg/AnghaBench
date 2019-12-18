#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct stmmac_priv {int clk_csr; scalar_t__ ioaddr; TYPE_3__* hw; TYPE_1__* plat; } ;
struct net_device {int dummy; } ;
struct mii_bus {struct net_device* priv; } ;
struct TYPE_5__ {unsigned int addr; unsigned int data; int addr_shift; int addr_mask; int reg_shift; int reg_mask; int clk_csr_shift; int clk_csr_mask; } ;
struct TYPE_6__ {TYPE_2__ mii; } ;
struct TYPE_4__ {scalar_t__ has_gmac4; } ;

/* Variables and functions */
 int EBUSY ; 
 int MII_ADDR_C45 ; 
 int MII_BUSY ; 
 int MII_DATA_MASK ; 
 int MII_DEVADDR_C45_SHIFT ; 
 int MII_GMAC4_C45E ; 
 int MII_GMAC4_READ ; 
 int MII_GMAC4_REG_ADDR_SHIFT ; 
 int MII_REGADDR_C45_MASK ; 
 struct stmmac_priv* netdev_priv (struct net_device*) ; 
 scalar_t__ readl (scalar_t__) ; 
 scalar_t__ readl_poll_timeout (scalar_t__,int,int,int,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int stmmac_mdio_read(struct mii_bus *bus, int phyaddr, int phyreg)
{
	struct net_device *ndev = bus->priv;
	struct stmmac_priv *priv = netdev_priv(ndev);
	unsigned int mii_address = priv->hw->mii.addr;
	unsigned int mii_data = priv->hw->mii.data;
	u32 value = MII_BUSY;
	int data = 0;
	u32 v;

	value |= (phyaddr << priv->hw->mii.addr_shift)
		& priv->hw->mii.addr_mask;
	value |= (phyreg << priv->hw->mii.reg_shift) & priv->hw->mii.reg_mask;
	value |= (priv->clk_csr << priv->hw->mii.clk_csr_shift)
		& priv->hw->mii.clk_csr_mask;
	if (priv->plat->has_gmac4) {
		value |= MII_GMAC4_READ;
		if (phyreg & MII_ADDR_C45) {
			value |= MII_GMAC4_C45E;
			value &= ~priv->hw->mii.reg_mask;
			value |= ((phyreg >> MII_DEVADDR_C45_SHIFT) <<
			       priv->hw->mii.reg_shift) &
			       priv->hw->mii.reg_mask;

			data |= (phyreg & MII_REGADDR_C45_MASK) <<
				MII_GMAC4_REG_ADDR_SHIFT;
		}
	}

	if (readl_poll_timeout(priv->ioaddr + mii_address, v, !(v & MII_BUSY),
			       100, 10000))
		return -EBUSY;

	writel(data, priv->ioaddr + mii_data);
	writel(value, priv->ioaddr + mii_address);

	if (readl_poll_timeout(priv->ioaddr + mii_address, v, !(v & MII_BUSY),
			       100, 10000))
		return -EBUSY;

	/* Read the data from the MII data register */
	data = (int)readl(priv->ioaddr + mii_data) & MII_DATA_MASK;

	return data;
}
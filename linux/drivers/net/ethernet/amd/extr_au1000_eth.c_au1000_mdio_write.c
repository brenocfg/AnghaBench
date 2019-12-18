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
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct net_device {int dummy; } ;
struct au1000_private {TYPE_1__* mac; } ;
struct TYPE_2__ {scalar_t__ mii_control; scalar_t__ mii_data; } ;

/* Variables and functions */
 int MAC_MII_BUSY ; 
 scalar_t__ MAC_MII_WRITE ; 
 scalar_t__ MAC_SET_MII_SELECT_PHY (int) ; 
 scalar_t__ MAC_SET_MII_SELECT_REG (int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct au1000_private* netdev_priv (struct net_device*) ; 
 int readl (scalar_t__* const) ; 
 int /*<<< orphan*/  writel (scalar_t__,scalar_t__* const) ; 

__attribute__((used)) static void au1000_mdio_write(struct net_device *dev, int phy_addr,
			      int reg, u16 value)
{
	struct au1000_private *aup = netdev_priv(dev);
	u32 *const mii_control_reg = &aup->mac->mii_control;
	u32 *const mii_data_reg = &aup->mac->mii_data;
	u32 timedout = 20;
	u32 mii_control;

	while (readl(mii_control_reg) & MAC_MII_BUSY) {
		mdelay(1);
		if (--timedout == 0) {
			netdev_err(dev, "mdio_write busy timeout!!\n");
			return;
		}
	}

	mii_control = MAC_SET_MII_SELECT_REG(reg) |
		MAC_SET_MII_SELECT_PHY(phy_addr) | MAC_MII_WRITE;

	writel(value, mii_data_reg);
	writel(mii_control, mii_control_reg);
}
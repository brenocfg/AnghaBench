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
typedef  void* u32 ;
struct smsc9420_pdata {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  addr; int /*<<< orphan*/  bus; } ;
struct phy_device {TYPE_1__ mdio; } ;
struct net_device {struct phy_device* phydev; } ;
struct ethtool_regs {void* version; } ;

/* Variables and functions */
 unsigned int ID_REV ; 
 struct smsc9420_pdata* netdev_priv (struct net_device*) ; 
 void* smsc9420_mii_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 void* smsc9420_reg_read (struct smsc9420_pdata*,unsigned int) ; 

__attribute__((used)) static void
smsc9420_ethtool_getregs(struct net_device *dev, struct ethtool_regs *regs,
			 void *buf)
{
	struct smsc9420_pdata *pd = netdev_priv(dev);
	struct phy_device *phy_dev = dev->phydev;
	unsigned int i, j = 0;
	u32 *data = buf;

	regs->version = smsc9420_reg_read(pd, ID_REV);
	for (i = 0; i < 0x100; i += (sizeof(u32)))
		data[j++] = smsc9420_reg_read(pd, i);

	// cannot read phy registers if the net device is down
	if (!phy_dev)
		return;

	for (i = 0; i <= 31; i++)
		data[j++] = smsc9420_mii_read(phy_dev->mdio.bus,
					      phy_dev->mdio.addr, i);
}
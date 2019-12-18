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
typedef  int u_int ;
struct pcnet_dev {int pna_phy; int eth_phy; } ;
struct net_device {unsigned int base_addr; } ;

/* Variables and functions */
 int AM79C9XX_ETH_PHY ; 
 int AM79C9XX_HOME_PHY ; 
 unsigned int DLINK_GPIO ; 
 int MII_PHYID_REG1 ; 
 int MII_PHYID_REG2 ; 
 int MII_PHYID_REV_MASK ; 
 struct pcnet_dev* PRIV (struct net_device*) ; 
 int mdio_read (unsigned int,int,int) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,int,int) ; 

__attribute__((used)) static void mii_phy_probe(struct net_device *dev)
{
    struct pcnet_dev *info = PRIV(dev);
    unsigned int mii_addr = dev->base_addr + DLINK_GPIO;
    int i;
    u_int tmp, phyid;

    for (i = 31; i >= 0; i--) {
	tmp = mdio_read(mii_addr, i, 1);
	if ((tmp == 0) || (tmp == 0xffff))
	    continue;
	tmp = mdio_read(mii_addr, i, MII_PHYID_REG1);
	phyid = tmp << 16;
	phyid |= mdio_read(mii_addr, i, MII_PHYID_REG2);
	phyid &= MII_PHYID_REV_MASK;
	netdev_dbg(dev, "MII at %d is 0x%08x\n", i, phyid);
	if (phyid == AM79C9XX_HOME_PHY) {
	    info->pna_phy = i;
	} else if (phyid != AM79C9XX_ETH_PHY) {
	    info->eth_phy = i;
	}
    }
}
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
typedef  int u16 ;
struct TYPE_6__ {int phy_id; int phy_id_mask; int reg_num_mask; int (* mdio_read ) (struct net_device*,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  supports_gmii; int /*<<< orphan*/  (* mdio_write ) (struct net_device*,int,int /*<<< orphan*/ ,int) ;struct net_device* dev; } ;
struct TYPE_4__ {int addr; } ;
struct TYPE_5__ {TYPE_1__ phy; } ;
struct pch_gbe_adapter {TYPE_3__ mii; struct net_device* netdev; TYPE_2__ hw; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int BMCR_ISOLATE ; 
 int EAGAIN ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  MII_BMSR ; 
 int PCH_GBE_PHY_REGS_LEN ; 
 int /*<<< orphan*/  mii_check_gmii_support (TYPE_3__*) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,int) ; 
 int pch_gbe_mdio_read (struct net_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pch_gbe_mdio_write (struct net_device*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pch_gbe_init_phy(struct pch_gbe_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;
	u32 addr;
	u16 bmcr, stat;

	/* Discover phy addr by searching addrs in order {1,0,2,..., 31} */
	for (addr = 0; addr < PCH_GBE_PHY_REGS_LEN; addr++) {
		adapter->mii.phy_id = (addr == 0) ? 1 : (addr == 1) ? 0 : addr;
		bmcr = pch_gbe_mdio_read(netdev, adapter->mii.phy_id, MII_BMCR);
		stat = pch_gbe_mdio_read(netdev, adapter->mii.phy_id, MII_BMSR);
		stat = pch_gbe_mdio_read(netdev, adapter->mii.phy_id, MII_BMSR);
		if (!((bmcr == 0xFFFF) || ((stat == 0) && (bmcr == 0))))
			break;
	}
	adapter->hw.phy.addr = adapter->mii.phy_id;
	netdev_dbg(netdev, "phy_addr = %d\n", adapter->mii.phy_id);
	if (addr == PCH_GBE_PHY_REGS_LEN)
		return -EAGAIN;
	/* Selected the phy and isolate the rest */
	for (addr = 0; addr < PCH_GBE_PHY_REGS_LEN; addr++) {
		if (addr != adapter->mii.phy_id) {
			pch_gbe_mdio_write(netdev, addr, MII_BMCR,
					   BMCR_ISOLATE);
		} else {
			bmcr = pch_gbe_mdio_read(netdev, addr, MII_BMCR);
			pch_gbe_mdio_write(netdev, addr, MII_BMCR,
					   bmcr & ~BMCR_ISOLATE);
		}
	}

	/* MII setup */
	adapter->mii.phy_id_mask = 0x1F;
	adapter->mii.reg_num_mask = 0x1F;
	adapter->mii.dev = adapter->netdev;
	adapter->mii.mdio_read = pch_gbe_mdio_read;
	adapter->mii.mdio_write = pch_gbe_mdio_write;
	adapter->mii.supports_gmii = mii_check_gmii_support(&adapter->mii);
	return 0;
}
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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct xgene_enet_pdata {int /*<<< orphan*/  ndev; } ;

/* Variables and functions */
 int BUSY_MASK ; 
 int /*<<< orphan*/  MII_MGMT_ADDRESS_ADDR ; 
 int /*<<< orphan*/  MII_MGMT_COMMAND_ADDR ; 
 int /*<<< orphan*/  MII_MGMT_INDICATORS_ADDR ; 
 int /*<<< orphan*/  MII_MGMT_STATUS_ADDR ; 
 int PHY_ADDR (int /*<<< orphan*/ ) ; 
 int READ_CYCLE_MASK ; 
 int REG_ADDR (int) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int xgene_enet_rd_mac (struct xgene_enet_pdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xgene_enet_wr_mac (struct xgene_enet_pdata*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u32 xgene_mii_phy_read(struct xgene_enet_pdata *p, u8 phy_id, u32 reg)
{
	u32 addr, data, done;
	int i;

	addr = PHY_ADDR(phy_id) | REG_ADDR(reg);
	xgene_enet_wr_mac(p, MII_MGMT_ADDRESS_ADDR, addr);
	xgene_enet_wr_mac(p, MII_MGMT_COMMAND_ADDR, READ_CYCLE_MASK);

	for (i = 0; i < 10; i++) {
		done = xgene_enet_rd_mac(p, MII_MGMT_INDICATORS_ADDR);
		if (!(done & BUSY_MASK)) {
			data = xgene_enet_rd_mac(p, MII_MGMT_STATUS_ADDR);
			xgene_enet_wr_mac(p, MII_MGMT_COMMAND_ADDR, 0);

			return data;
		}
		usleep_range(10, 20);
	}

	netdev_err(p->ndev, "MII_MGMT read failed\n");

	return 0;
}
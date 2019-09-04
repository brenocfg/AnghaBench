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
struct xgene_enet_pdata {int /*<<< orphan*/  ndev; } ;

/* Variables and functions */
 int AUTO_NEG_COMPLETE ; 
 int /*<<< orphan*/  INT_PHY_ADDR ; 
 int LINK_STATUS ; 
 int SGMII_STATUS_ADDR ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int xgene_mii_phy_read (struct xgene_enet_pdata*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xgene_sgmii_configure (struct xgene_enet_pdata*) ; 

__attribute__((used)) static void xgene_sgmii_enable_autoneg(struct xgene_enet_pdata *p)
{
	u32 data, loop = 10;

	xgene_sgmii_configure(p);

	while (loop--) {
		data = xgene_mii_phy_read(p, INT_PHY_ADDR,
					  SGMII_STATUS_ADDR >> 2);
		if ((data & AUTO_NEG_COMPLETE) && (data & LINK_STATUS))
			break;
		usleep_range(1000, 2000);
	}
	if (!(data & AUTO_NEG_COMPLETE) || !(data & LINK_STATUS))
		netdev_err(p->ndev, "Auto-negotiation failed\n");
}
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
typedef  int u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct smsc9420_pdata {struct net_device* dev; } ;
struct phy_device {scalar_t__ duplex; } ;
struct net_device {struct phy_device* phydev; } ;

/* Variables and functions */
 scalar_t__ DUPLEX_FULL ; 
 int /*<<< orphan*/  FLOW ; 
 int FLOW_CTRL_RX ; 
 int FLOW_CTRL_TX ; 
 int /*<<< orphan*/  MII_ADVERTISE ; 
 int /*<<< orphan*/  MII_LPA ; 
 int /*<<< orphan*/  link ; 
 int mii_resolve_flowctrl_fdx (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_info (struct smsc9420_pdata*,int /*<<< orphan*/ ,struct net_device*,char*,...) ; 
 int /*<<< orphan*/  phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smsc9420_reg_write (struct smsc9420_pdata*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void smsc9420_phy_update_flowcontrol(struct smsc9420_pdata *pd)
{
	struct net_device *dev = pd->dev;
	struct phy_device *phy_dev = dev->phydev;
	u32 flow;

	if (phy_dev->duplex == DUPLEX_FULL) {
		u16 lcladv = phy_read(phy_dev, MII_ADVERTISE);
		u16 rmtadv = phy_read(phy_dev, MII_LPA);
		u8 cap = mii_resolve_flowctrl_fdx(lcladv, rmtadv);

		if (cap & FLOW_CTRL_RX)
			flow = 0xFFFF0002;
		else
			flow = 0;

		netif_info(pd, link, pd->dev, "rx pause %s, tx pause %s\n",
			   cap & FLOW_CTRL_RX ? "enabled" : "disabled",
			   cap & FLOW_CTRL_TX ? "enabled" : "disabled");
	} else {
		netif_info(pd, link, pd->dev, "half duplex\n");
		flow = 0;
	}

	smsc9420_reg_write(pd, FLOW, flow);
}
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
struct smsc911x_data {int /*<<< orphan*/  mac_lock; struct net_device* dev; } ;
struct phy_device {scalar_t__ duplex; } ;
struct net_device {struct phy_device* phydev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFC_CFG ; 
 scalar_t__ DUPLEX_FULL ; 
 int /*<<< orphan*/  FLOW ; 
 int FLOW_CTRL_RX ; 
 int FLOW_CTRL_TX ; 
 int /*<<< orphan*/  MII_ADVERTISE ; 
 int /*<<< orphan*/  MII_LPA ; 
 int /*<<< orphan*/  SMSC_TRACE (struct smsc911x_data*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  hw ; 
 int mii_resolve_flowctrl_fdx (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smsc911x_mac_write (struct smsc911x_data*,int /*<<< orphan*/ ,int) ; 
 int smsc911x_reg_read (struct smsc911x_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smsc911x_reg_write (struct smsc911x_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void smsc911x_phy_update_flowcontrol(struct smsc911x_data *pdata)
{
	struct net_device *ndev = pdata->dev;
	struct phy_device *phy_dev = ndev->phydev;
	u32 afc = smsc911x_reg_read(pdata, AFC_CFG);
	u32 flow;
	unsigned long flags;

	if (phy_dev->duplex == DUPLEX_FULL) {
		u16 lcladv = phy_read(phy_dev, MII_ADVERTISE);
		u16 rmtadv = phy_read(phy_dev, MII_LPA);
		u8 cap = mii_resolve_flowctrl_fdx(lcladv, rmtadv);

		if (cap & FLOW_CTRL_RX)
			flow = 0xFFFF0002;
		else
			flow = 0;

		if (cap & FLOW_CTRL_TX)
			afc |= 0xF;
		else
			afc &= ~0xF;

		SMSC_TRACE(pdata, hw, "rx pause %s, tx pause %s",
			   (cap & FLOW_CTRL_RX ? "enabled" : "disabled"),
			   (cap & FLOW_CTRL_TX ? "enabled" : "disabled"));
	} else {
		SMSC_TRACE(pdata, hw, "half duplex");
		flow = 0;
		afc |= 0xF;
	}

	spin_lock_irqsave(&pdata->mac_lock, flags);
	smsc911x_mac_write(pdata, FLOW, flow);
	spin_unlock_irqrestore(&pdata->mac_lock, flags);

	smsc911x_reg_write(pdata, AFC_CFG, afc);
}
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
typedef  scalar_t__ u32 ;
struct phy_device {int advertising; int /*<<< orphan*/  autoneg; int /*<<< orphan*/  supported; } ;
struct net_device {int dummy; } ;
struct lan743x_phy {int fc_request_control; int /*<<< orphan*/  fc_autoneg; } ;
struct lan743x_adapter {int /*<<< orphan*/  mdiobus; struct net_device* netdev; struct lan743x_phy phy; } ;

/* Variables and functions */
 int ADVERTISED_Asym_Pause ; 
 int ADVERTISED_Pause ; 
 int EIO ; 
 int FLOW_CTRL_RX ; 
 int FLOW_CTRL_TX ; 
 int /*<<< orphan*/  PHY_INTERFACE_MODE_GMII ; 
 int /*<<< orphan*/  SUPPORTED_1000baseT_Half ; 
 int /*<<< orphan*/  lan743x_phy_link_status_change ; 
 int mii_adv_to_ethtool_adv_t (scalar_t__) ; 
 scalar_t__ mii_advertise_flowctrl (int) ; 
 int phy_connect_direct (struct net_device*,struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct phy_device* phy_find_first (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_start (struct phy_device*) ; 
 int /*<<< orphan*/  phy_start_aneg (struct phy_device*) ; 

__attribute__((used)) static int lan743x_phy_open(struct lan743x_adapter *adapter)
{
	struct lan743x_phy *phy = &adapter->phy;
	struct phy_device *phydev;
	struct net_device *netdev;
	int ret = -EIO;
	u32 mii_adv;

	netdev = adapter->netdev;
	phydev = phy_find_first(adapter->mdiobus);
	if (!phydev)
		goto return_error;

	ret = phy_connect_direct(netdev, phydev,
				 lan743x_phy_link_status_change,
				 PHY_INTERFACE_MODE_GMII);
	if (ret)
		goto return_error;

	/* MAC doesn't support 1000T Half */
	phydev->supported &= ~SUPPORTED_1000baseT_Half;

	/* support both flow controls */
	phy->fc_request_control = (FLOW_CTRL_RX | FLOW_CTRL_TX);
	phydev->advertising &= ~(ADVERTISED_Pause | ADVERTISED_Asym_Pause);
	mii_adv = (u32)mii_advertise_flowctrl(phy->fc_request_control);
	phydev->advertising |= mii_adv_to_ethtool_adv_t(mii_adv);
	phy->fc_autoneg = phydev->autoneg;

	phy_start(phydev);
	phy_start_aneg(phydev);
	return 0;

return_error:
	return ret;
}
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
struct phy_device {int /*<<< orphan*/  autoneg; } ;
struct net_device {int dummy; } ;
struct lan743x_phy {int fc_request_control; int /*<<< orphan*/  fc_autoneg; } ;
struct lan743x_adapter {int /*<<< orphan*/  mdiobus; struct net_device* netdev; struct lan743x_phy phy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_1000baseT_Half_BIT ; 
 int FLOW_CTRL_RX ; 
 int FLOW_CTRL_TX ; 
 int /*<<< orphan*/  PHY_INTERFACE_MODE_GMII ; 
 int /*<<< orphan*/  lan743x_phy_link_status_change ; 
 int phy_connect_direct (struct net_device*,struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct phy_device* phy_find_first (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_remove_link_mode (struct phy_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_start (struct phy_device*) ; 
 int /*<<< orphan*/  phy_start_aneg (struct phy_device*) ; 
 int /*<<< orphan*/  phy_support_asym_pause (struct phy_device*) ; 

__attribute__((used)) static int lan743x_phy_open(struct lan743x_adapter *adapter)
{
	struct lan743x_phy *phy = &adapter->phy;
	struct phy_device *phydev;
	struct net_device *netdev;
	int ret = -EIO;

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
	phy_remove_link_mode(phydev, ETHTOOL_LINK_MODE_1000baseT_Half_BIT);

	/* support both flow controls */
	phy_support_asym_pause(phydev);
	phy->fc_request_control = (FLOW_CTRL_RX | FLOW_CTRL_TX);
	phy->fc_autoneg = phydev->autoneg;

	phy_start(phydev);
	phy_start_aneg(phydev);
	return 0;

return_error:
	return ret;
}
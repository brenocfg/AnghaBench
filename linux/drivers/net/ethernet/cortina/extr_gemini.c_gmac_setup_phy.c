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
struct TYPE_2__ {int /*<<< orphan*/  mii_rmii; } ;
union gmac_status {int /*<<< orphan*/  bits32; TYPE_1__ bits; } ;
struct phy_device {int interface; } ;
struct net_device {struct phy_device* phydev; } ;
struct gemini_ethernet_port {scalar_t__ gmac_base; struct device* dev; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  GMAC_PHY_GMII ; 
 int /*<<< orphan*/  GMAC_PHY_MII ; 
 int /*<<< orphan*/  GMAC_PHY_RGMII_100_10 ; 
 scalar_t__ GMAC_STATUS ; 
#define  PHY_INTERFACE_MODE_GMII 130 
#define  PHY_INTERFACE_MODE_MII 129 
#define  PHY_INTERFACE_MODE_RGMII 128 
 int /*<<< orphan*/  SPEED_1000 ; 
 int /*<<< orphan*/  gmac_speed_set ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct gemini_ethernet_port* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_msg_link (struct gemini_ethernet_port*) ; 
 struct phy_device* of_phy_get_and_connect (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_attached_info (struct phy_device*) ; 
 int /*<<< orphan*/  phy_disconnect (struct phy_device*) ; 
 int /*<<< orphan*/  phy_set_max_speed (struct phy_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_support_asym_pause (struct phy_device*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int gmac_setup_phy(struct net_device *netdev)
{
	struct gemini_ethernet_port *port = netdev_priv(netdev);
	union gmac_status status = { .bits32 = 0 };
	struct device *dev = port->dev;
	struct phy_device *phy;

	phy = of_phy_get_and_connect(netdev,
				     dev->of_node,
				     gmac_speed_set);
	if (!phy)
		return -ENODEV;
	netdev->phydev = phy;

	phy_set_max_speed(phy, SPEED_1000);
	phy_support_asym_pause(phy);

	/* set PHY interface type */
	switch (phy->interface) {
	case PHY_INTERFACE_MODE_MII:
		netdev_dbg(netdev,
			   "MII: set GMAC0 to GMII mode, GMAC1 disabled\n");
		status.bits.mii_rmii = GMAC_PHY_MII;
		break;
	case PHY_INTERFACE_MODE_GMII:
		netdev_dbg(netdev,
			   "GMII: set GMAC0 to GMII mode, GMAC1 disabled\n");
		status.bits.mii_rmii = GMAC_PHY_GMII;
		break;
	case PHY_INTERFACE_MODE_RGMII:
		netdev_dbg(netdev,
			   "RGMII: set GMAC0 and GMAC1 to MII/RGMII mode\n");
		status.bits.mii_rmii = GMAC_PHY_RGMII_100_10;
		break;
	default:
		netdev_err(netdev, "Unsupported MII interface\n");
		phy_disconnect(phy);
		netdev->phydev = NULL;
		return -EINVAL;
	}
	writel(status.bits32, port->gmac_base + GMAC_STATUS);

	if (netif_msg_link(port))
		phy_attached_info(phy);

	return 0;
}
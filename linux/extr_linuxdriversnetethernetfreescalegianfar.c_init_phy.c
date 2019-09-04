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
typedef  int uint ;
struct phy_device {int supported; int advertising; } ;
struct net_device {int /*<<< orphan*/  dev; } ;
struct gfar_private {int device_flags; int oldduplex; int /*<<< orphan*/  phy_node; scalar_t__ oldspeed; scalar_t__ oldlink; } ;
struct ethtool_eee {int dummy; } ;
typedef  scalar_t__ phy_interface_t ;

/* Variables and functions */
 int ENODEV ; 
 int FSL_GIANFAR_DEV_HAS_GIGABIT ; 
 int GFAR_SUPPORTED ; 
 int GFAR_SUPPORTED_GBIT ; 
 scalar_t__ PHY_INTERFACE_MODE_SGMII ; 
 int SUPPORTED_Asym_Pause ; 
 int SUPPORTED_Pause ; 
 int /*<<< orphan*/  adjust_link ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  gfar_configure_serdes (struct net_device*) ; 
 scalar_t__ gfar_get_interface (struct net_device*) ; 
 int /*<<< orphan*/  memset (struct ethtool_eee*,int /*<<< orphan*/ ,int) ; 
 struct gfar_private* netdev_priv (struct net_device*) ; 
 struct phy_device* of_phy_connect (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  phy_ethtool_set_eee (struct phy_device*,struct ethtool_eee*) ; 

__attribute__((used)) static int init_phy(struct net_device *dev)
{
	struct gfar_private *priv = netdev_priv(dev);
	uint gigabit_support =
		priv->device_flags & FSL_GIANFAR_DEV_HAS_GIGABIT ?
		GFAR_SUPPORTED_GBIT : 0;
	phy_interface_t interface;
	struct phy_device *phydev;
	struct ethtool_eee edata;

	priv->oldlink = 0;
	priv->oldspeed = 0;
	priv->oldduplex = -1;

	interface = gfar_get_interface(dev);

	phydev = of_phy_connect(dev, priv->phy_node, &adjust_link, 0,
				interface);
	if (!phydev) {
		dev_err(&dev->dev, "could not attach to PHY\n");
		return -ENODEV;
	}

	if (interface == PHY_INTERFACE_MODE_SGMII)
		gfar_configure_serdes(dev);

	/* Remove any features not supported by the controller */
	phydev->supported &= (GFAR_SUPPORTED | gigabit_support);
	phydev->advertising = phydev->supported;

	/* Add support for flow control, but don't advertise it by default */
	phydev->supported |= (SUPPORTED_Pause | SUPPORTED_Asym_Pause);

	/* disable EEE autoneg, EEE not supported by eTSEC */
	memset(&edata, 0, sizeof(struct ethtool_eee));
	phy_ethtool_set_eee(phydev, &edata);

	return 0;
}
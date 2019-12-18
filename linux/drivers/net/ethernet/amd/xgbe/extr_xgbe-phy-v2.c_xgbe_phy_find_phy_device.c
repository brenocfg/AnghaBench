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
struct TYPE_5__ {int (* set_ext_mii_mode ) (struct xgbe_prv_data*,int /*<<< orphan*/ ,scalar_t__) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  advertising; } ;
struct ethtool_link_ksettings {TYPE_3__ link_modes; } ;
struct TYPE_4__ {struct ethtool_link_ksettings lks; } ;
struct xgbe_prv_data {int /*<<< orphan*/  netdev; TYPE_2__ hw_if; scalar_t__ an_again; struct xgbe_phy_data* phy_data; TYPE_1__ phy; } ;
struct xgbe_phy_data {scalar_t__ phydev_mode; scalar_t__ port_mode; struct phy_device* phydev; int /*<<< orphan*/  mdio_addr; int /*<<< orphan*/  mii; int /*<<< orphan*/  sfp_phy_avail; } ;
struct phy_device {int /*<<< orphan*/  advertising; int /*<<< orphan*/  dev_flags; int /*<<< orphan*/  phy_id; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ IS_ERR (struct phy_device*) ; 
 int /*<<< orphan*/  PHY_INTERFACE_MODE_SGMII ; 
 scalar_t__ XGBE_MDIO_MODE_CL45 ; 
 scalar_t__ XGBE_MDIO_MODE_NONE ; 
 scalar_t__ XGBE_PORT_MODE_SFP ; 
 int /*<<< orphan*/  drv ; 
 struct phy_device* get_phy_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  linkmode_and (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  netif_dbg (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int phy_attach_direct (int /*<<< orphan*/ ,struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_device_free (struct phy_device*) ; 
 int phy_device_register (struct phy_device*) ; 
 int /*<<< orphan*/  phy_device_remove (struct phy_device*) ; 
 int /*<<< orphan*/  phy_start_aneg (struct phy_device*) ; 
 int stub1 (struct xgbe_prv_data*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  xgbe_phy_external_phy_quirks (struct xgbe_prv_data*) ; 

__attribute__((used)) static int xgbe_phy_find_phy_device(struct xgbe_prv_data *pdata)
{
	struct ethtool_link_ksettings *lks = &pdata->phy.lks;
	struct xgbe_phy_data *phy_data = pdata->phy_data;
	struct phy_device *phydev;
	int ret;

	/* If we already have a PHY, just return */
	if (phy_data->phydev)
		return 0;

	/* Clear the extra AN flag */
	pdata->an_again = 0;

	/* Check for the use of an external PHY */
	if (phy_data->phydev_mode == XGBE_MDIO_MODE_NONE)
		return 0;

	/* For SFP, only use an external PHY if available */
	if ((phy_data->port_mode == XGBE_PORT_MODE_SFP) &&
	    !phy_data->sfp_phy_avail)
		return 0;

	/* Set the proper MDIO mode for the PHY */
	ret = pdata->hw_if.set_ext_mii_mode(pdata, phy_data->mdio_addr,
					    phy_data->phydev_mode);
	if (ret) {
		netdev_err(pdata->netdev,
			   "mdio port/clause not compatible (%u/%u)\n",
			   phy_data->mdio_addr, phy_data->phydev_mode);
		return ret;
	}

	/* Create and connect to the PHY device */
	phydev = get_phy_device(phy_data->mii, phy_data->mdio_addr,
				(phy_data->phydev_mode == XGBE_MDIO_MODE_CL45));
	if (IS_ERR(phydev)) {
		netdev_err(pdata->netdev, "get_phy_device failed\n");
		return -ENODEV;
	}
	netif_dbg(pdata, drv, pdata->netdev, "external PHY id is %#010x\n",
		  phydev->phy_id);

	/*TODO: If c45, add request_module based on one of the MMD ids? */

	ret = phy_device_register(phydev);
	if (ret) {
		netdev_err(pdata->netdev, "phy_device_register failed\n");
		phy_device_free(phydev);
		return ret;
	}

	ret = phy_attach_direct(pdata->netdev, phydev, phydev->dev_flags,
				PHY_INTERFACE_MODE_SGMII);
	if (ret) {
		netdev_err(pdata->netdev, "phy_attach_direct failed\n");
		phy_device_remove(phydev);
		phy_device_free(phydev);
		return ret;
	}
	phy_data->phydev = phydev;

	xgbe_phy_external_phy_quirks(pdata);

	linkmode_and(phydev->advertising, phydev->advertising,
		     lks->link_modes.advertising);

	phy_start_aneg(phy_data->phydev);

	return 0;
}
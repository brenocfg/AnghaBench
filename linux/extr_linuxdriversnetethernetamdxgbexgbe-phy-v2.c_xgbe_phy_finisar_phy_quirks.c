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
struct xgbe_prv_data {int /*<<< orphan*/  netdev; struct xgbe_phy_data* phy_data; } ;
struct xgbe_phy_data {scalar_t__ port_mode; TYPE_1__* phydev; } ;
struct TYPE_2__ {unsigned int phy_id; int supported; int advertising; } ;

/* Variables and functions */
 int PHY_GBIT_FEATURES ; 
 int SUPPORTED_Asym_Pause ; 
 int SUPPORTED_Pause ; 
 scalar_t__ XGBE_PORT_MODE_SFP ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  netif_dbg (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  phy_write (TYPE_1__*,int,int) ; 

__attribute__((used)) static bool xgbe_phy_finisar_phy_quirks(struct xgbe_prv_data *pdata)
{
	struct xgbe_phy_data *phy_data = pdata->phy_data;
	unsigned int phy_id = phy_data->phydev->phy_id;

	if (phy_data->port_mode != XGBE_PORT_MODE_SFP)
		return false;

	if ((phy_id & 0xfffffff0) != 0x01ff0cc0)
		return false;

	/* Enable Base-T AN */
	phy_write(phy_data->phydev, 0x16, 0x0001);
	phy_write(phy_data->phydev, 0x00, 0x9140);
	phy_write(phy_data->phydev, 0x16, 0x0000);

	/* Enable SGMII at 100Base-T/1000Base-T Full Duplex */
	phy_write(phy_data->phydev, 0x1b, 0x9084);
	phy_write(phy_data->phydev, 0x09, 0x0e00);
	phy_write(phy_data->phydev, 0x00, 0x8140);
	phy_write(phy_data->phydev, 0x04, 0x0d01);
	phy_write(phy_data->phydev, 0x00, 0x9140);

	phy_data->phydev->supported = PHY_GBIT_FEATURES;
	phy_data->phydev->supported |= SUPPORTED_Pause | SUPPORTED_Asym_Pause;
	phy_data->phydev->advertising = phy_data->phydev->supported;

	netif_dbg(pdata, drv, pdata->netdev,
		  "Finisar PHY quirk in place\n");

	return true;
}
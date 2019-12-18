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
struct TYPE_4__ {int /*<<< orphan*/  advertising; } ;
struct ethtool_link_ksettings {TYPE_1__ link_modes; } ;
struct TYPE_5__ {scalar_t__ autoneg; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; struct ethtool_link_ksettings lks; } ;
struct xgbe_prv_data {TYPE_2__ phy; struct xgbe_phy_data* phy_data; } ;
struct xgbe_phy_data {TYPE_3__* phydev; } ;
struct TYPE_6__ {scalar_t__ autoneg; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; int /*<<< orphan*/  supported; int /*<<< orphan*/  advertising; } ;

/* Variables and functions */
 scalar_t__ AUTONEG_ENABLE ; 
 int /*<<< orphan*/  linkmode_and (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int phy_start_aneg (TYPE_3__*) ; 
 int xgbe_phy_find_phy_device (struct xgbe_prv_data*) ; 

__attribute__((used)) static int xgbe_phy_an_config(struct xgbe_prv_data *pdata)
{
	struct ethtool_link_ksettings *lks = &pdata->phy.lks;
	struct xgbe_phy_data *phy_data = pdata->phy_data;
	int ret;

	ret = xgbe_phy_find_phy_device(pdata);
	if (ret)
		return ret;

	if (!phy_data->phydev)
		return 0;

	phy_data->phydev->autoneg = pdata->phy.autoneg;
	linkmode_and(phy_data->phydev->advertising,
		     phy_data->phydev->supported,
		     lks->link_modes.advertising);

	if (pdata->phy.autoneg != AUTONEG_ENABLE) {
		phy_data->phydev->speed = pdata->phy.speed;
		phy_data->phydev->duplex = pdata->phy.duplex;
	}

	ret = phy_start_aneg(phy_data->phydev);

	return ret;
}
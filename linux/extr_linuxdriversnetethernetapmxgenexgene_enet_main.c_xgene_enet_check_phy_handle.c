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
struct xgene_enet_pdata {scalar_t__ phy_mode; int mdio_driver; int /*<<< orphan*/  ndev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_MDIO_XGENE ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ PHY_INTERFACE_MODE_XGMII ; 
 int xgene_enet_phy_connect (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xgene_enet_check_phy_handle(struct xgene_enet_pdata *pdata)
{
	int ret;

	if (pdata->phy_mode == PHY_INTERFACE_MODE_XGMII)
		return;

	if (!IS_ENABLED(CONFIG_MDIO_XGENE))
		return;

	ret = xgene_enet_phy_connect(pdata->ndev);
	if (!ret)
		pdata->mdio_driver = true;
}
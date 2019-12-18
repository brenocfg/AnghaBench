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
struct phy_device {int /*<<< orphan*/  interface; int /*<<< orphan*/  mdix_ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETHTOOL_PHY_EDPD_DFLT_TX_MSECS ; 
 int /*<<< orphan*/  ETH_TP_MDI_AUTO ; 
 int adin_config_rgmii_mode (struct phy_device*) ; 
 int adin_config_rmii_mode (struct phy_device*) ; 
 int adin_set_downshift (struct phy_device*,int) ; 
 int adin_set_edpd (struct phy_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_modes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phydev_dbg (struct phy_device*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adin_config_init(struct phy_device *phydev)
{
	int rc;

	phydev->mdix_ctrl = ETH_TP_MDI_AUTO;

	rc = adin_config_rgmii_mode(phydev);
	if (rc < 0)
		return rc;

	rc = adin_config_rmii_mode(phydev);
	if (rc < 0)
		return rc;

	rc = adin_set_downshift(phydev, 4);
	if (rc < 0)
		return rc;

	rc = adin_set_edpd(phydev, ETHTOOL_PHY_EDPD_DFLT_TX_MSECS);
	if (rc < 0)
		return rc;

	phydev_dbg(phydev, "PHY is using mode '%s'\n",
		   phy_modes(phydev->interface));

	return 0;
}
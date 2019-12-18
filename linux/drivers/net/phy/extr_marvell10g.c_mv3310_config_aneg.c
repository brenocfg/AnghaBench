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
typedef  int /*<<< orphan*/  u16 ;
struct phy_device {scalar_t__ autoneg; int /*<<< orphan*/  advertising; int /*<<< orphan*/  mdix_ctrl; } ;

/* Variables and functions */
 int ADVERTISE_1000FULL ; 
 int ADVERTISE_1000HALF ; 
 scalar_t__ AUTONEG_DISABLE ; 
 int /*<<< orphan*/  ETH_TP_MDI_AUTO ; 
 int /*<<< orphan*/  MDIO_MMD_AN ; 
 int /*<<< orphan*/  MV_AN_CTRL1000 ; 
 int genphy_c45_an_config_aneg (struct phy_device*) ; 
 int genphy_c45_check_and_restart_aneg (struct phy_device*,int) ; 
 int genphy_c45_pma_setup_forced (struct phy_device*) ; 
 int /*<<< orphan*/  linkmode_adv_to_mii_ctrl1000_t (int /*<<< orphan*/ ) ; 
 int phy_modify_mmd_changed (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mv3310_config_aneg(struct phy_device *phydev)
{
	bool changed = false;
	u16 reg;
	int ret;

	/* We don't support manual MDI control */
	phydev->mdix_ctrl = ETH_TP_MDI_AUTO;

	if (phydev->autoneg == AUTONEG_DISABLE)
		return genphy_c45_pma_setup_forced(phydev);

	ret = genphy_c45_an_config_aneg(phydev);
	if (ret < 0)
		return ret;
	if (ret > 0)
		changed = true;

	/* Clause 45 has no standardized support for 1000BaseT, therefore
	 * use vendor registers for this mode.
	 */
	reg = linkmode_adv_to_mii_ctrl1000_t(phydev->advertising);
	ret = phy_modify_mmd_changed(phydev, MDIO_MMD_AN, MV_AN_CTRL1000,
			     ADVERTISE_1000FULL | ADVERTISE_1000HALF, reg);
	if (ret < 0)
		return ret;
	if (ret > 0)
		changed = true;

	return genphy_c45_check_and_restart_aneg(phydev, changed);
}
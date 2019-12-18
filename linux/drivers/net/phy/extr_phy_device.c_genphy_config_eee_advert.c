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
struct phy_device {int /*<<< orphan*/  eee_broken_modes; } ;

/* Variables and functions */
 int /*<<< orphan*/  MDIO_AN_EEE_ADV ; 
 int /*<<< orphan*/  MDIO_MMD_AN ; 
 int phy_modify_mmd_changed (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int genphy_config_eee_advert(struct phy_device *phydev)
{
	int err;

	/* Nothing to disable */
	if (!phydev->eee_broken_modes)
		return 0;

	err = phy_modify_mmd_changed(phydev, MDIO_MMD_AN, MDIO_AN_EEE_ADV,
				     phydev->eee_broken_modes, 0);
	/* If the call failed, we assume that EEE is not supported */
	return err < 0 ? 0 : err;
}
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
struct phy_device {scalar_t__ interface; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  MDIO_AN_VEND_PROV_DOWNSHIFT_DFLT ; 
 scalar_t__ PHY_INTERFACE_MODE_2500BASEX ; 
 scalar_t__ PHY_INTERFACE_MODE_SGMII ; 
 int /*<<< orphan*/  SPEED_2500 ; 
 int /*<<< orphan*/  aqr107_chip_info (struct phy_device*) ; 
 int /*<<< orphan*/  aqr107_read_downshift_event (struct phy_device*) ; 
 int aqr107_set_downshift (struct phy_device*,int /*<<< orphan*/ ) ; 
 int aqr107_wait_reset_complete (struct phy_device*) ; 
 int phy_set_max_speed (struct phy_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int aqcs109_config_init(struct phy_device *phydev)
{
	int ret;

	/* Check that the PHY interface type is compatible */
	if (phydev->interface != PHY_INTERFACE_MODE_SGMII &&
	    phydev->interface != PHY_INTERFACE_MODE_2500BASEX)
		return -ENODEV;

	ret = aqr107_wait_reset_complete(phydev);
	if (!ret)
		aqr107_chip_info(phydev);

	/* AQCS109 belongs to a chip family partially supporting 10G and 5G.
	 * PMA speed ability bits are the same for all members of the family,
	 * AQCS109 however supports speeds up to 2.5G only.
	 */
	ret = phy_set_max_speed(phydev, SPEED_2500);
	if (ret)
		return ret;

	/* ensure that a latched downshift event is cleared */
	aqr107_read_downshift_event(phydev);

	return aqr107_set_downshift(phydev, MDIO_AN_VEND_PROV_DOWNSHIFT_DFLT);
}
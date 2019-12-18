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
struct phy_device {scalar_t__ autoneg; int /*<<< orphan*/  interface; int /*<<< orphan*/  link; } ;

/* Variables and functions */
 scalar_t__ AUTONEG_DISABLE ; 
 int FIELD_GET (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MDIO_MMD_PHYXS ; 
 int /*<<< orphan*/  MDIO_PHYXS_VEND_IF_STATUS ; 
#define  MDIO_PHYXS_VEND_IF_STATUS_TYPE_KR 132 
 int /*<<< orphan*/  MDIO_PHYXS_VEND_IF_STATUS_TYPE_MASK ; 
#define  MDIO_PHYXS_VEND_IF_STATUS_TYPE_OCSGMII 131 
#define  MDIO_PHYXS_VEND_IF_STATUS_TYPE_SGMII 130 
#define  MDIO_PHYXS_VEND_IF_STATUS_TYPE_USXGMII 129 
#define  MDIO_PHYXS_VEND_IF_STATUS_TYPE_XFI 128 
 int /*<<< orphan*/  PHY_INTERFACE_MODE_10GKR ; 
 int /*<<< orphan*/  PHY_INTERFACE_MODE_2500BASEX ; 
 int /*<<< orphan*/  PHY_INTERFACE_MODE_NA ; 
 int /*<<< orphan*/  PHY_INTERFACE_MODE_SGMII ; 
 int /*<<< orphan*/  PHY_INTERFACE_MODE_USXGMII ; 
 int aqr107_read_downshift_event (struct phy_device*) ; 
 int aqr107_read_rate (struct phy_device*) ; 
 int aqr_read_status (struct phy_device*) ; 
 int phy_read_mmd (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phydev_warn (struct phy_device*,char*) ; 

__attribute__((used)) static int aqr107_read_status(struct phy_device *phydev)
{
	int val, ret;

	ret = aqr_read_status(phydev);
	if (ret)
		return ret;

	if (!phydev->link || phydev->autoneg == AUTONEG_DISABLE)
		return 0;

	val = phy_read_mmd(phydev, MDIO_MMD_PHYXS, MDIO_PHYXS_VEND_IF_STATUS);
	if (val < 0)
		return val;

	switch (FIELD_GET(MDIO_PHYXS_VEND_IF_STATUS_TYPE_MASK, val)) {
	case MDIO_PHYXS_VEND_IF_STATUS_TYPE_KR:
	case MDIO_PHYXS_VEND_IF_STATUS_TYPE_XFI:
		phydev->interface = PHY_INTERFACE_MODE_10GKR;
		break;
	case MDIO_PHYXS_VEND_IF_STATUS_TYPE_USXGMII:
		phydev->interface = PHY_INTERFACE_MODE_USXGMII;
		break;
	case MDIO_PHYXS_VEND_IF_STATUS_TYPE_SGMII:
		phydev->interface = PHY_INTERFACE_MODE_SGMII;
		break;
	case MDIO_PHYXS_VEND_IF_STATUS_TYPE_OCSGMII:
		phydev->interface = PHY_INTERFACE_MODE_2500BASEX;
		break;
	default:
		phydev->interface = PHY_INTERFACE_MODE_NA;
		break;
	}

	val = aqr107_read_downshift_event(phydev);
	if (val <= 0)
		return val;

	phydev_warn(phydev, "Downshift occurred! Cabling may be defective.\n");

	/* Read downshifted rate from vendor register */
	return aqr107_read_rate(phydev);
}
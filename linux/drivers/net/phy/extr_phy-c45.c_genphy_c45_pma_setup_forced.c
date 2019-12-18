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
struct phy_device {scalar_t__ duplex; int speed; } ;

/* Variables and functions */
 scalar_t__ DUPLEX_FULL ; 
 int EINVAL ; 
 int /*<<< orphan*/  MDIO_CTRL1 ; 
 int MDIO_CTRL1_SPEED10G ; 
 int MDIO_CTRL1_SPEED2_5G ; 
 int MDIO_CTRL1_SPEED5G ; 
 int MDIO_CTRL1_SPEEDSEL ; 
 int /*<<< orphan*/  MDIO_CTRL2 ; 
 int /*<<< orphan*/  MDIO_MMD_PMAPMD ; 
 int MDIO_PMA_CTRL1_SPEED100 ; 
 int MDIO_PMA_CTRL1_SPEED1000 ; 
 int MDIO_PMA_CTRL2_1000BT ; 
 int MDIO_PMA_CTRL2_100BTX ; 
 int MDIO_PMA_CTRL2_10BT ; 
 int MDIO_PMA_CTRL2_10GBT ; 
 int MDIO_PMA_CTRL2_2_5GBT ; 
 int MDIO_PMA_CTRL2_5GBT ; 
 int MDIO_PMA_CTRL2_TYPE ; 
#define  SPEED_10 133 
#define  SPEED_100 132 
#define  SPEED_1000 131 
#define  SPEED_10000 130 
#define  SPEED_2500 129 
#define  SPEED_5000 128 
 int genphy_c45_an_disable_aneg (struct phy_device*) ; 
 int phy_read_mmd (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int phy_write_mmd (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int genphy_c45_pma_setup_forced(struct phy_device *phydev)
{
	int ctrl1, ctrl2, ret;

	/* Half duplex is not supported */
	if (phydev->duplex != DUPLEX_FULL)
		return -EINVAL;

	ctrl1 = phy_read_mmd(phydev, MDIO_MMD_PMAPMD, MDIO_CTRL1);
	if (ctrl1 < 0)
		return ctrl1;

	ctrl2 = phy_read_mmd(phydev, MDIO_MMD_PMAPMD, MDIO_CTRL2);
	if (ctrl2 < 0)
		return ctrl2;

	ctrl1 &= ~MDIO_CTRL1_SPEEDSEL;
	/*
	 * PMA/PMD type selection is 1.7.5:0 not 1.7.3:0.  See 45.2.1.6.1
	 * in 802.3-2012 and 802.3-2015.
	 */
	ctrl2 &= ~(MDIO_PMA_CTRL2_TYPE | 0x30);

	switch (phydev->speed) {
	case SPEED_10:
		ctrl2 |= MDIO_PMA_CTRL2_10BT;
		break;
	case SPEED_100:
		ctrl1 |= MDIO_PMA_CTRL1_SPEED100;
		ctrl2 |= MDIO_PMA_CTRL2_100BTX;
		break;
	case SPEED_1000:
		ctrl1 |= MDIO_PMA_CTRL1_SPEED1000;
		/* Assume 1000base-T */
		ctrl2 |= MDIO_PMA_CTRL2_1000BT;
		break;
	case SPEED_2500:
		ctrl1 |= MDIO_CTRL1_SPEED2_5G;
		/* Assume 2.5Gbase-T */
		ctrl2 |= MDIO_PMA_CTRL2_2_5GBT;
		break;
	case SPEED_5000:
		ctrl1 |= MDIO_CTRL1_SPEED5G;
		/* Assume 5Gbase-T */
		ctrl2 |= MDIO_PMA_CTRL2_5GBT;
		break;
	case SPEED_10000:
		ctrl1 |= MDIO_CTRL1_SPEED10G;
		/* Assume 10Gbase-T */
		ctrl2 |= MDIO_PMA_CTRL2_10GBT;
		break;
	default:
		return -EINVAL;
	}

	ret = phy_write_mmd(phydev, MDIO_MMD_PMAPMD, MDIO_CTRL1, ctrl1);
	if (ret < 0)
		return ret;

	ret = phy_write_mmd(phydev, MDIO_MMD_PMAPMD, MDIO_CTRL2, ctrl2);
	if (ret < 0)
		return ret;

	return genphy_c45_an_disable_aneg(phydev);
}
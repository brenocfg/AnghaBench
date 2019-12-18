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
struct phy_device {int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int /*<<< orphan*/  DUPLEX_HALF ; 
 int FIELD_GET (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MDIO_AN_TX_VEND_STATUS1 ; 
#define  MDIO_AN_TX_VEND_STATUS1_1000BASET 133 
#define  MDIO_AN_TX_VEND_STATUS1_100BASETX 132 
#define  MDIO_AN_TX_VEND_STATUS1_10BASET 131 
#define  MDIO_AN_TX_VEND_STATUS1_10GBASET 130 
#define  MDIO_AN_TX_VEND_STATUS1_2500BASET 129 
#define  MDIO_AN_TX_VEND_STATUS1_5000BASET 128 
 int MDIO_AN_TX_VEND_STATUS1_FULL_DUPLEX ; 
 int /*<<< orphan*/  MDIO_AN_TX_VEND_STATUS1_RATE_MASK ; 
 int /*<<< orphan*/  MDIO_MMD_AN ; 
 int /*<<< orphan*/  SPEED_10 ; 
 int /*<<< orphan*/  SPEED_100 ; 
 int /*<<< orphan*/  SPEED_1000 ; 
 int /*<<< orphan*/  SPEED_10000 ; 
 int /*<<< orphan*/  SPEED_2500 ; 
 int /*<<< orphan*/  SPEED_5000 ; 
 int /*<<< orphan*/  SPEED_UNKNOWN ; 
 int phy_read_mmd (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int aqr107_read_rate(struct phy_device *phydev)
{
	int val;

	val = phy_read_mmd(phydev, MDIO_MMD_AN, MDIO_AN_TX_VEND_STATUS1);
	if (val < 0)
		return val;

	switch (FIELD_GET(MDIO_AN_TX_VEND_STATUS1_RATE_MASK, val)) {
	case MDIO_AN_TX_VEND_STATUS1_10BASET:
		phydev->speed = SPEED_10;
		break;
	case MDIO_AN_TX_VEND_STATUS1_100BASETX:
		phydev->speed = SPEED_100;
		break;
	case MDIO_AN_TX_VEND_STATUS1_1000BASET:
		phydev->speed = SPEED_1000;
		break;
	case MDIO_AN_TX_VEND_STATUS1_2500BASET:
		phydev->speed = SPEED_2500;
		break;
	case MDIO_AN_TX_VEND_STATUS1_5000BASET:
		phydev->speed = SPEED_5000;
		break;
	case MDIO_AN_TX_VEND_STATUS1_10GBASET:
		phydev->speed = SPEED_10000;
		break;
	default:
		phydev->speed = SPEED_UNKNOWN;
		break;
	}

	if (val & MDIO_AN_TX_VEND_STATUS1_FULL_DUPLEX)
		phydev->duplex = DUPLEX_FULL;
	else
		phydev->duplex = DUPLEX_HALF;

	return 0;
}
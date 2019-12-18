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
struct phy_device {int speed; int duplex; int /*<<< orphan*/  advertising; int /*<<< orphan*/  autoneg; int /*<<< orphan*/  supported; } ;
struct net_device {struct phy_device* phydev; } ;
struct mv643xx_eth_private {struct net_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTONEG_DISABLE ; 
 int /*<<< orphan*/  AUTONEG_ENABLE ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_Autoneg_BIT ; 
 int /*<<< orphan*/  linkmode_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linkmode_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linkmode_zero (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_start_aneg (struct phy_device*) ; 

__attribute__((used)) static void phy_init(struct mv643xx_eth_private *mp, int speed, int duplex)
{
	struct net_device *dev = mp->dev;
	struct phy_device *phy = dev->phydev;

	if (speed == 0) {
		phy->autoneg = AUTONEG_ENABLE;
		phy->speed = 0;
		phy->duplex = 0;
		linkmode_copy(phy->advertising, phy->supported);
		linkmode_set_bit(ETHTOOL_LINK_MODE_Autoneg_BIT,
				 phy->advertising);
	} else {
		phy->autoneg = AUTONEG_DISABLE;
		linkmode_zero(phy->advertising);
		phy->speed = speed;
		phy->duplex = duplex;
	}
	phy_start_aneg(phy);
}
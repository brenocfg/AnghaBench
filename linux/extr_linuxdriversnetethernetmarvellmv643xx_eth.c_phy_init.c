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
struct phy_device {int speed; int duplex; int advertising; int supported; int /*<<< orphan*/  autoneg; } ;
struct net_device {struct phy_device* phydev; } ;
struct mv643xx_eth_private {struct net_device* dev; } ;

/* Variables and functions */
 int ADVERTISED_Autoneg ; 
 int /*<<< orphan*/  AUTONEG_DISABLE ; 
 int /*<<< orphan*/  AUTONEG_ENABLE ; 
 int /*<<< orphan*/  phy_start_aneg (struct phy_device*) ; 

__attribute__((used)) static void phy_init(struct mv643xx_eth_private *mp, int speed, int duplex)
{
	struct net_device *dev = mp->dev;
	struct phy_device *phy = dev->phydev;

	if (speed == 0) {
		phy->autoneg = AUTONEG_ENABLE;
		phy->speed = 0;
		phy->duplex = 0;
		phy->advertising = phy->supported | ADVERTISED_Autoneg;
	} else {
		phy->autoneg = AUTONEG_DISABLE;
		phy->advertising = 0;
		phy->speed = speed;
		phy->duplex = duplex;
	}
	phy_start_aneg(phy);
}
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
struct phy_device {int /*<<< orphan*/  advertising; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; int /*<<< orphan*/  autoneg; } ;
struct mii_phy {int /*<<< orphan*/  advertising; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; int /*<<< orphan*/  autoneg; } ;

/* Variables and functions */
 int /*<<< orphan*/  ethtool_convert_legacy_u32_to_link_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int phy_start_aneg (struct phy_device*) ; 

__attribute__((used)) static int emac_mdio_phy_start_aneg(struct mii_phy *phy,
				    struct phy_device *phy_dev)
{
	phy_dev->autoneg = phy->autoneg;
	phy_dev->speed = phy->speed;
	phy_dev->duplex = phy->duplex;
	ethtool_convert_legacy_u32_to_link_mode(phy_dev->advertising,
						phy->advertising);
	return phy_start_aneg(phy_dev);
}
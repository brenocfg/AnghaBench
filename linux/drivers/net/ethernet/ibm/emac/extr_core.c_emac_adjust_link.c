#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct phy_device {int /*<<< orphan*/  advertising; int /*<<< orphan*/  asym_pause; int /*<<< orphan*/  pause; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; int /*<<< orphan*/  autoneg; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  advertising; int /*<<< orphan*/  asym_pause; int /*<<< orphan*/  pause; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; int /*<<< orphan*/  autoneg; } ;
struct emac_instance {TYPE_1__ phy; struct phy_device* phy_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ethtool_convert_link_mode_to_legacy_u32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct emac_instance* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void emac_adjust_link(struct net_device *ndev)
{
	struct emac_instance *dev = netdev_priv(ndev);
	struct phy_device *phy = dev->phy_dev;

	dev->phy.autoneg = phy->autoneg;
	dev->phy.speed = phy->speed;
	dev->phy.duplex = phy->duplex;
	dev->phy.pause = phy->pause;
	dev->phy.asym_pause = phy->asym_pause;
	ethtool_convert_link_mode_to_legacy_u32(&dev->phy.advertising,
						phy->advertising);
}
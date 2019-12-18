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
struct phy_device {scalar_t__ state; int /*<<< orphan*/  lp_advertising; int /*<<< orphan*/  advertising; } ;
struct net_device {struct phy_device* phydev; } ;
struct lan743x_adapter {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  speed; int /*<<< orphan*/  duplex; } ;
struct ethtool_link_ksettings {TYPE_1__ base; } ;
typedef  int /*<<< orphan*/  ksettings ;

/* Variables and functions */
 scalar_t__ PHY_RUNNING ; 
 int /*<<< orphan*/  lan743x_phy_update_flowcontrol (struct lan743x_adapter*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  lan743x_ptp_update_latency (struct lan743x_adapter*,int /*<<< orphan*/ ) ; 
 int linkmode_adv_to_mii_adv_t (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ethtool_link_ksettings*,int /*<<< orphan*/ ,int) ; 
 struct lan743x_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  phy_ethtool_get_link_ksettings (struct net_device*,struct ethtool_link_ksettings*) ; 
 int /*<<< orphan*/  phy_print_status (struct phy_device*) ; 

__attribute__((used)) static void lan743x_phy_link_status_change(struct net_device *netdev)
{
	struct lan743x_adapter *adapter = netdev_priv(netdev);
	struct phy_device *phydev = netdev->phydev;

	phy_print_status(phydev);
	if (phydev->state == PHY_RUNNING) {
		struct ethtool_link_ksettings ksettings;
		int remote_advertisement = 0;
		int local_advertisement = 0;

		memset(&ksettings, 0, sizeof(ksettings));
		phy_ethtool_get_link_ksettings(netdev, &ksettings);
		local_advertisement =
			linkmode_adv_to_mii_adv_t(phydev->advertising);
		remote_advertisement =
			linkmode_adv_to_mii_adv_t(phydev->lp_advertising);

		lan743x_phy_update_flowcontrol(adapter,
					       ksettings.base.duplex,
					       local_advertisement,
					       remote_advertisement);
		lan743x_ptp_update_latency(adapter, ksettings.base.speed);
	}
}
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
typedef  int u16 ;
struct net_device {int dummy; } ;
struct atl1e_adapter {int /*<<< orphan*/  link_chg_task; int /*<<< orphan*/  link_speed; int /*<<< orphan*/  mdio_lock; int /*<<< orphan*/  hw; struct net_device* netdev; } ;

/* Variables and functions */
 int BMSR_LSTATUS ; 
 int /*<<< orphan*/  MII_BMSR ; 
 int /*<<< orphan*/  SPEED_0 ; 
 int /*<<< orphan*/  atl1e_read_phy_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*) ; 
 scalar_t__ netif_carrier_ok (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void atl1e_link_chg_event(struct atl1e_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;
	u16 phy_data = 0;
	u16 link_up = 0;

	spin_lock(&adapter->mdio_lock);
	atl1e_read_phy_reg(&adapter->hw, MII_BMSR, &phy_data);
	atl1e_read_phy_reg(&adapter->hw, MII_BMSR, &phy_data);
	spin_unlock(&adapter->mdio_lock);
	link_up = phy_data & BMSR_LSTATUS;
	/* notify upper layer link down ASAP */
	if (!link_up) {
		if (netif_carrier_ok(netdev)) {
			/* old link state: Up */
			netdev_info(netdev, "NIC Link is Down\n");
			adapter->link_speed = SPEED_0;
			netif_stop_queue(netdev);
		}
	}
	schedule_work(&adapter->link_chg_task);
}
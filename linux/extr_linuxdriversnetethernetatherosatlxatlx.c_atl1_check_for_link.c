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
typedef  int u16 ;
struct net_device {int /*<<< orphan*/  name; } ;
struct atlx_adapter {int phy_timer_pending; int /*<<< orphan*/  link_chg_task; int /*<<< orphan*/  link_speed; TYPE_1__* pdev; int /*<<< orphan*/  lock; int /*<<< orphan*/  hw; struct net_device* netdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BMSR_LSTATUS ; 
 int /*<<< orphan*/  MII_BMSR ; 
 int /*<<< orphan*/  SPEED_0 ; 
 int /*<<< orphan*/  atlx_read_phy_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 scalar_t__ netif_carrier_ok (struct net_device*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void atlx_check_for_link(struct atlx_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;
	u16 phy_data = 0;

	spin_lock(&adapter->lock);
	adapter->phy_timer_pending = false;
	atlx_read_phy_reg(&adapter->hw, MII_BMSR, &phy_data);
	atlx_read_phy_reg(&adapter->hw, MII_BMSR, &phy_data);
	spin_unlock(&adapter->lock);

	/* notify upper layer link down ASAP */
	if (!(phy_data & BMSR_LSTATUS)) {
		/* Link Down */
		if (netif_carrier_ok(netdev)) {
			/* old link state: Up */
			dev_info(&adapter->pdev->dev, "%s link is down\n",
				netdev->name);
			adapter->link_speed = SPEED_0;
			netif_carrier_off(netdev);
		}
	}
	schedule_work(&adapter->link_chg_task);
}
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
struct net_device {int /*<<< orphan*/  irq; int /*<<< orphan*/  name; } ;
struct board_info {int /*<<< orphan*/  phy_poll; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm9000_shutdown (struct net_device*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 struct board_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 scalar_t__ netif_msg_ifdown (struct board_info*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 

__attribute__((used)) static int
dm9000_stop(struct net_device *ndev)
{
	struct board_info *db = netdev_priv(ndev);

	if (netif_msg_ifdown(db))
		dev_dbg(db->dev, "shutting down %s\n", ndev->name);

	cancel_delayed_work_sync(&db->phy_poll);

	netif_stop_queue(ndev);
	netif_carrier_off(ndev);

	/* free interrupt */
	free_irq(ndev->irq, ndev);

	dm9000_shutdown(ndev);

	return 0;
}
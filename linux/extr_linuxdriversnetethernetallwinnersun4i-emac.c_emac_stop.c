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
struct net_device {int /*<<< orphan*/  irq; int /*<<< orphan*/  phydev; int /*<<< orphan*/  name; } ;
struct emac_board_info {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emac_mdio_remove (struct net_device*) ; 
 int /*<<< orphan*/  emac_shutdown (struct net_device*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 struct emac_board_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 scalar_t__ netif_msg_ifdown (struct emac_board_info*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  phy_stop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int emac_stop(struct net_device *ndev)
{
	struct emac_board_info *db = netdev_priv(ndev);

	if (netif_msg_ifdown(db))
		dev_dbg(db->dev, "shutting down %s\n", ndev->name);

	netif_stop_queue(ndev);
	netif_carrier_off(ndev);

	phy_stop(ndev->phydev);

	emac_mdio_remove(ndev);

	emac_shutdown(ndev);

	free_irq(ndev->irq, ndev);

	return 0;
}
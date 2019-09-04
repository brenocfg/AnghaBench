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
struct net_device {int /*<<< orphan*/  phydev; int /*<<< orphan*/  irq; int /*<<< orphan*/  name; } ;
struct emac_board_info {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emac_init_device (struct net_device*) ; 
 int /*<<< orphan*/  emac_interrupt ; 
 int emac_mdio_probe (struct net_device*) ; 
 int /*<<< orphan*/  emac_reset (struct emac_board_info*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct emac_board_info* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_msg_ifup (struct emac_board_info*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  phy_start (int /*<<< orphan*/ ) ; 
 scalar_t__ request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 

__attribute__((used)) static int emac_open(struct net_device *dev)
{
	struct emac_board_info *db = netdev_priv(dev);
	int ret;

	if (netif_msg_ifup(db))
		dev_dbg(db->dev, "enabling %s\n", dev->name);

	if (request_irq(dev->irq, &emac_interrupt, 0, dev->name, dev))
		return -EAGAIN;

	/* Initialize EMAC board */
	emac_reset(db);
	emac_init_device(dev);

	ret = emac_mdio_probe(dev);
	if (ret < 0) {
		free_irq(dev->irq, dev);
		netdev_err(dev, "cannot probe MDIO bus\n");
		return ret;
	}

	phy_start(dev->phydev);
	netif_start_queue(dev);

	return 0;
}
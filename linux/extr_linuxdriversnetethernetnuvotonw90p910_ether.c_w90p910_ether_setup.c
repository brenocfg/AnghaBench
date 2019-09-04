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
struct TYPE_2__ {int phy_id; int phy_id_mask; int reg_num_mask; int /*<<< orphan*/  mdio_write; int /*<<< orphan*/  mdio_read; struct net_device* dev; } ;
struct w90p910_ether {int cur_tx; int cur_rx; int finish_tx; int linkflag; int /*<<< orphan*/  check_timer; TYPE_1__ mii; } ;
struct net_device {int tx_queue_len; int dma; int /*<<< orphan*/  watchdog_timeo; int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/ * netdev_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  TX_TIMEOUT ; 
 int /*<<< orphan*/  get_mac_address (struct net_device*) ; 
 struct w90p910_ether* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w90p910_check_link ; 
 int /*<<< orphan*/  w90p910_ether_ethtool_ops ; 
 int /*<<< orphan*/  w90p910_ether_netdev_ops ; 
 int /*<<< orphan*/  w90p910_mdio_read ; 
 int /*<<< orphan*/  w90p910_mdio_write ; 

__attribute__((used)) static int w90p910_ether_setup(struct net_device *dev)
{
	struct w90p910_ether *ether = netdev_priv(dev);

	dev->netdev_ops = &w90p910_ether_netdev_ops;
	dev->ethtool_ops = &w90p910_ether_ethtool_ops;

	dev->tx_queue_len = 16;
	dev->dma = 0x0;
	dev->watchdog_timeo = TX_TIMEOUT;

	get_mac_address(dev);

	ether->cur_tx = 0x0;
	ether->cur_rx = 0x0;
	ether->finish_tx = 0x0;
	ether->linkflag = 0x0;
	ether->mii.phy_id = 0x01;
	ether->mii.phy_id_mask = 0x1f;
	ether->mii.reg_num_mask = 0x1f;
	ether->mii.dev = dev;
	ether->mii.mdio_read = w90p910_mdio_read;
	ether->mii.mdio_write = w90p910_mdio_write;

	timer_setup(&ether->check_timer, w90p910_check_link, 0);

	return 0;
}
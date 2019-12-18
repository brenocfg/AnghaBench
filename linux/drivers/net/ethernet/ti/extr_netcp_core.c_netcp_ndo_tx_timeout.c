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
struct netcp_intf {int /*<<< orphan*/  tx_pool_size; int /*<<< orphan*/  ndev_dev; int /*<<< orphan*/  tx_pool; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 unsigned int knav_pool_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netcp_process_tx_compl_packets (struct netcp_intf*,int /*<<< orphan*/ ) ; 
 struct netcp_intf* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_trans_update (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_wake_all_queues (struct net_device*) ; 

__attribute__((used)) static void netcp_ndo_tx_timeout(struct net_device *ndev)
{
	struct netcp_intf *netcp = netdev_priv(ndev);
	unsigned int descs = knav_pool_count(netcp->tx_pool);

	dev_err(netcp->ndev_dev, "transmit timed out tx descs(%d)\n", descs);
	netcp_process_tx_compl_packets(netcp, netcp->tx_pool_size);
	netif_trans_update(ndev);
	netif_tx_wake_all_queues(ndev);
}
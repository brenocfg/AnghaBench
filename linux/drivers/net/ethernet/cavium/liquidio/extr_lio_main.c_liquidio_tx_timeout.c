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
struct TYPE_2__ {int /*<<< orphan*/  tx_dropped; } ;
struct net_device {TYPE_1__ stats; } ;
struct lio {int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 struct lio* GET_LIO (struct net_device*) ; 
 int /*<<< orphan*/  netif_info (struct lio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_trans_update (struct net_device*) ; 
 int /*<<< orphan*/  tx_err ; 
 int /*<<< orphan*/  wake_txqs (struct net_device*) ; 

__attribute__((used)) static void liquidio_tx_timeout(struct net_device *netdev)
{
	struct lio *lio;

	lio = GET_LIO(netdev);

	netif_info(lio, tx_err, lio->netdev,
		   "Transmit timeout tx_dropped:%ld, waking up queues now!!\n",
		   netdev->stats.tx_dropped);
	netif_trans_update(netdev);
	wake_txqs(netdev);
}
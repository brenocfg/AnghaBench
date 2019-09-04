#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* netdev; } ;
struct nfp_net {TYPE_2__ dp; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {int real_num_tx_queues; } ;

/* Variables and functions */
 int /*<<< orphan*/  netdev_get_tx_queue (struct net_device*,int) ; 
 struct nfp_net* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_queue_stopped (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_warn (struct nfp_net*,char*,...) ; 

__attribute__((used)) static void nfp_net_tx_timeout(struct net_device *netdev)
{
	struct nfp_net *nn = netdev_priv(netdev);
	int i;

	for (i = 0; i < nn->dp.netdev->real_num_tx_queues; i++) {
		if (!netif_tx_queue_stopped(netdev_get_tx_queue(netdev, i)))
			continue;
		nn_warn(nn, "TX timeout on ring: %d\n", i);
	}
	nn_warn(nn, "TX watchdog timeout\n");
}
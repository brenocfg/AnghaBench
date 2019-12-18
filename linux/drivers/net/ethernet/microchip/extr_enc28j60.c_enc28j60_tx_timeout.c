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
struct TYPE_2__ {int /*<<< orphan*/  tx_errors; } ;
struct net_device {TYPE_1__ stats; } ;
struct enc28j60_net {int /*<<< orphan*/  restart_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct enc28j60_net* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_msg_timer (struct enc28j60_net*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void enc28j60_tx_timeout(struct net_device *ndev)
{
	struct enc28j60_net *priv = netdev_priv(ndev);

	if (netif_msg_timer(priv))
		netdev_err(ndev, "tx timeout\n");

	ndev->stats.tx_errors++;
	/* can't restart safely under softirq */
	schedule_work(&priv->restart_work);
}
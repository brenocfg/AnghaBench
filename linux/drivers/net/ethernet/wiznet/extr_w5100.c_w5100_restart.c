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
struct w5100_priv {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_errors; } ;
struct net_device {TYPE_1__ stats; } ;

/* Variables and functions */
 struct w5100_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_trans_update (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  w5100_hw_reset (struct w5100_priv*) ; 
 int /*<<< orphan*/  w5100_hw_start (struct w5100_priv*) ; 

__attribute__((used)) static void w5100_restart(struct net_device *ndev)
{
	struct w5100_priv *priv = netdev_priv(ndev);

	netif_stop_queue(ndev);
	w5100_hw_reset(priv);
	w5100_hw_start(priv);
	ndev->stats.tx_errors++;
	netif_trans_update(ndev);
	netif_wake_queue(ndev);
}
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
struct netdev_queue {int dummy; } ;
struct net_device {int dummy; } ;
struct ftgmac100 {struct net_device* netdev; } ;

/* Variables and functions */
 scalar_t__ TX_THRESHOLD ; 
 int /*<<< orphan*/  __netif_tx_lock (struct netdev_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __netif_tx_unlock (struct netdev_queue*) ; 
 scalar_t__ ftgmac100_tx_buf_avail (struct ftgmac100*) ; 
 scalar_t__ ftgmac100_tx_buf_cleanable (struct ftgmac100*) ; 
 scalar_t__ ftgmac100_tx_complete_packet (struct ftgmac100*) ; 
 struct netdev_queue* netdev_get_tx_queue (struct net_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ netif_queue_stopped (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void ftgmac100_tx_complete(struct ftgmac100 *priv)
{
	struct net_device *netdev = priv->netdev;

	/* Process all completed packets */
	while (ftgmac100_tx_buf_cleanable(priv) &&
	       ftgmac100_tx_complete_packet(priv))
		;

	/* Restart queue if needed */
	smp_mb();
	if (unlikely(netif_queue_stopped(netdev) &&
		     ftgmac100_tx_buf_avail(priv) >= TX_THRESHOLD)) {
		struct netdev_queue *txq;

		txq = netdev_get_tx_queue(netdev, 0);
		__netif_tx_lock(txq, smp_processor_id());
		if (netif_queue_stopped(netdev) &&
		    ftgmac100_tx_buf_avail(priv) >= TX_THRESHOLD)
			netif_wake_queue(netdev);
		__netif_tx_unlock(txq);
	}
}
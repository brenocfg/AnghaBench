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
struct sk_buff {int dummy; } ;
struct net_local {scalar_t__ in_idx; scalar_t__ sk_count; int /*<<< orphan*/  lock; struct sk_buff** skbs; } ;
struct net_device {scalar_t__ ml_priv; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
struct TYPE_2__ {int /*<<< orphan*/  irq_queue; } ;
typedef  TYPE_1__ hysdn_card ;

/* Variables and functions */
 scalar_t__ MAX_SKB_BUFFERS ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_trans_update (struct net_device*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static netdev_tx_t
net_send_packet(struct sk_buff *skb, struct net_device *dev)
{
	struct net_local *lp = (struct net_local *) dev;

	spin_lock_irq(&lp->lock);

	lp->skbs[lp->in_idx++] = skb;	/* add to buffer list */
	if (lp->in_idx >= MAX_SKB_BUFFERS)
		lp->in_idx = 0;	/* wrap around */
	lp->sk_count++;		/* adjust counter */
	netif_trans_update(dev);

	/* If we just used up the very last entry in the
	 * TX ring on this device, tell the queueing
	 * layer to send no more.
	 */
	if (lp->sk_count >= MAX_SKB_BUFFERS)
		netif_stop_queue(dev);

	/* When the TX completion hw interrupt arrives, this
	 * is when the transmit statistics are updated.
	 */

	spin_unlock_irq(&lp->lock);

	if (lp->sk_count <= 3) {
		schedule_work(&((hysdn_card *) dev->ml_priv)->irq_queue);
	}
	return NETDEV_TX_OK;	/* success */
}
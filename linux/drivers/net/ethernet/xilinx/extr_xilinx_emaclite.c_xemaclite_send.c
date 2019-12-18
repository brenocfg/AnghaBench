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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {unsigned int len; scalar_t__ data; } ;
struct net_local {int /*<<< orphan*/  reset_lock; struct sk_buff* deferred_skb; } ;
struct TYPE_2__ {unsigned int tx_bytes; } ;
struct net_device {TYPE_1__ stats; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  dev_consume_skb_any (struct sk_buff*) ; 
 struct net_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  skb_tx_timestamp (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ xemaclite_send_data (struct net_local*,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static netdev_tx_t
xemaclite_send(struct sk_buff *orig_skb, struct net_device *dev)
{
	struct net_local *lp = netdev_priv(dev);
	struct sk_buff *new_skb;
	unsigned int len;
	unsigned long flags;

	len = orig_skb->len;

	new_skb = orig_skb;

	spin_lock_irqsave(&lp->reset_lock, flags);
	if (xemaclite_send_data(lp, (u8 *)new_skb->data, len) != 0) {
		/* If the Emaclite Tx buffer is busy, stop the Tx queue and
		 * defer the skb for transmission during the ISR, after the
		 * current transmission is complete
		 */
		netif_stop_queue(dev);
		lp->deferred_skb = new_skb;
		/* Take the time stamp now, since we can't do this in an ISR. */
		skb_tx_timestamp(new_skb);
		spin_unlock_irqrestore(&lp->reset_lock, flags);
		return NETDEV_TX_OK;
	}
	spin_unlock_irqrestore(&lp->reset_lock, flags);

	skb_tx_timestamp(new_skb);

	dev->stats.tx_bytes += len;
	dev_consume_skb_any(new_skb);

	return NETDEV_TX_OK;
}
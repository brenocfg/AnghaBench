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
struct tx_agg {int /*<<< orphan*/  list; scalar_t__ skb_num; } ;
struct r8152 {int /*<<< orphan*/  tx_lock; int /*<<< orphan*/  tx_free; struct net_device* netdev; int /*<<< orphan*/  tx_queue; } ;
struct net_device_stats {int /*<<< orphan*/  tx_dropped; } ;
struct net_device {struct net_device_stats stats; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_device_detach (struct net_device*) ; 
 int /*<<< orphan*/  netif_warn (struct r8152*,int /*<<< orphan*/ ,struct net_device*,char*,int) ; 
 struct tx_agg* r8152_get_tx_agg (struct r8152*) ; 
 int r8152_tx_agg_fill (struct r8152*,struct tx_agg*) ; 
 int /*<<< orphan*/  rtl_set_unplug (struct r8152*) ; 
 scalar_t__ skb_queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tx_err ; 

__attribute__((used)) static void tx_bottom(struct r8152 *tp)
{
	int res;

	do {
		struct tx_agg *agg;

		if (skb_queue_empty(&tp->tx_queue))
			break;

		agg = r8152_get_tx_agg(tp);
		if (!agg)
			break;

		res = r8152_tx_agg_fill(tp, agg);
		if (res) {
			struct net_device *netdev = tp->netdev;

			if (res == -ENODEV) {
				rtl_set_unplug(tp);
				netif_device_detach(netdev);
			} else {
				struct net_device_stats *stats = &netdev->stats;
				unsigned long flags;

				netif_warn(tp, tx_err, netdev,
					   "failed tx_urb %d\n", res);
				stats->tx_dropped += agg->skb_num;

				spin_lock_irqsave(&tp->tx_lock, flags);
				list_add_tail(&agg->list, &tp->tx_free);
				spin_unlock_irqrestore(&tp->tx_lock, flags);
			}
		}
	} while (res == 0);
}
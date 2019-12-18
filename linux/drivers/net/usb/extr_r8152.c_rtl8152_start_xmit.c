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
struct sk_buff {int dummy; } ;
struct r8152 {scalar_t__ tx_qlen; int /*<<< orphan*/  tx_queue; int /*<<< orphan*/  tx_tl; int /*<<< orphan*/  udev; int /*<<< orphan*/  schedule; int /*<<< orphan*/  flags; int /*<<< orphan*/  tx_free; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  SCHEDULE_TASKLET ; 
 int /*<<< orphan*/  SELECTIVE_SUSPEND ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 struct r8152* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ skb_queue_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_tx_timestamp (struct sk_buff*) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_mark_last_busy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static netdev_tx_t rtl8152_start_xmit(struct sk_buff *skb,
				      struct net_device *netdev)
{
	struct r8152 *tp = netdev_priv(netdev);

	skb_tx_timestamp(skb);

	skb_queue_tail(&tp->tx_queue, skb);

	if (!list_empty(&tp->tx_free)) {
		if (test_bit(SELECTIVE_SUSPEND, &tp->flags)) {
			set_bit(SCHEDULE_TASKLET, &tp->flags);
			schedule_delayed_work(&tp->schedule, 0);
		} else {
			usb_mark_last_busy(tp->udev);
			tasklet_schedule(&tp->tx_tl);
		}
	} else if (skb_queue_len(&tp->tx_queue) > tp->tx_qlen) {
		netif_stop_queue(netdev);
	}

	return NETDEV_TX_OK;
}
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
struct urb {int status; struct tx_agg* context; } ;
struct tx_agg {int /*<<< orphan*/  list; scalar_t__ skb_len; scalar_t__ skb_num; struct r8152* context; } ;
struct r8152 {int /*<<< orphan*/  tx_tl; int /*<<< orphan*/  tx_queue; int /*<<< orphan*/  flags; int /*<<< orphan*/  intf; int /*<<< orphan*/  tx_lock; int /*<<< orphan*/  tx_free; struct net_device* netdev; } ;
struct net_device_stats {int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_errors; } ;
struct net_device {struct net_device_stats stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTL8152_UNPLUG ; 
 int /*<<< orphan*/  WORK_ENABLE ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ net_ratelimit () ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*,int) ; 
 int /*<<< orphan*/  netif_carrier_ok (struct net_device*) ; 
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_autopm_put_interface_async (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void write_bulk_callback(struct urb *urb)
{
	struct net_device_stats *stats;
	struct net_device *netdev;
	struct tx_agg *agg;
	struct r8152 *tp;
	unsigned long flags;
	int status = urb->status;

	agg = urb->context;
	if (!agg)
		return;

	tp = agg->context;
	if (!tp)
		return;

	netdev = tp->netdev;
	stats = &netdev->stats;
	if (status) {
		if (net_ratelimit())
			netdev_warn(netdev, "Tx status %d\n", status);
		stats->tx_errors += agg->skb_num;
	} else {
		stats->tx_packets += agg->skb_num;
		stats->tx_bytes += agg->skb_len;
	}

	spin_lock_irqsave(&tp->tx_lock, flags);
	list_add_tail(&agg->list, &tp->tx_free);
	spin_unlock_irqrestore(&tp->tx_lock, flags);

	usb_autopm_put_interface_async(tp->intf);

	if (!netif_carrier_ok(netdev))
		return;

	if (!test_bit(WORK_ENABLE, &tp->flags))
		return;

	if (test_bit(RTL8152_UNPLUG, &tp->flags))
		return;

	if (!skb_queue_empty(&tp->tx_queue))
		tasklet_schedule(&tp->tx_tl);
}
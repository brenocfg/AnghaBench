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
struct usbnet {int /*<<< orphan*/  net; int /*<<< orphan*/  rxq_pause; int /*<<< orphan*/  flags; int /*<<< orphan*/  stats64; } ;
struct skb_data {int dummy; } ;
struct sk_buff {scalar_t__ protocol; int /*<<< orphan*/  cb; scalar_t__ len; } ;
struct pcpu_sw_netstats {int /*<<< orphan*/  syncp; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct ethhdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_RX_PAUSED ; 
 int NET_RX_SUCCESS ; 
 scalar_t__ eth_type_trans (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netif_dbg (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,...) ; 
 int netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  rx_err ; 
 int /*<<< orphan*/  rx_status ; 
 scalar_t__ skb_defer_rx_timestamp (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct pcpu_sw_netstats* this_cpu_ptr (int /*<<< orphan*/ ) ; 
 unsigned long u64_stats_update_begin_irqsave (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void usbnet_skb_return (struct usbnet *dev, struct sk_buff *skb)
{
	struct pcpu_sw_netstats *stats64 = this_cpu_ptr(dev->stats64);
	unsigned long flags;
	int	status;

	if (test_bit(EVENT_RX_PAUSED, &dev->flags)) {
		skb_queue_tail(&dev->rxq_pause, skb);
		return;
	}

	/* only update if unset to allow minidriver rx_fixup override */
	if (skb->protocol == 0)
		skb->protocol = eth_type_trans (skb, dev->net);

	flags = u64_stats_update_begin_irqsave(&stats64->syncp);
	stats64->rx_packets++;
	stats64->rx_bytes += skb->len;
	u64_stats_update_end_irqrestore(&stats64->syncp, flags);

	netif_dbg(dev, rx_status, dev->net, "< rx, len %zu, type 0x%x\n",
		  skb->len + sizeof (struct ethhdr), skb->protocol);
	memset (skb->cb, 0, sizeof (struct skb_data));

	if (skb_defer_rx_timestamp(skb))
		return;

	status = netif_rx (skb);
	if (status != NET_RX_SUCCESS)
		netif_dbg(dev, rx_err, dev->net,
			  "netif_rx status %d\n", status);
}
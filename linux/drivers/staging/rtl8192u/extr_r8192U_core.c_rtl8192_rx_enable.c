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
struct urb {int dummy; } ;
struct sk_buff {scalar_t__ cb; } ;
struct rtl8192_rx_info {int out_pipe; struct net_device* dev; struct urb* urb; } ;
struct r8192_priv {int /*<<< orphan*/  rx_queue; int /*<<< orphan*/  udev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ MAX_RX_URB ; 
 int /*<<< orphan*/  RX_URB_SIZE ; 
 struct sk_buff* __dev_alloc_skb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  rtl8192_rx_isr ; 
 scalar_t__ skb_queue_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_tail_pointer (struct sk_buff*) ; 
 struct urb* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (struct urb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 

void rtl8192_rx_enable(struct net_device *dev)
{
	struct r8192_priv *priv = (struct r8192_priv *)ieee80211_priv(dev);
	struct urb *entry;
	struct sk_buff *skb;
	struct rtl8192_rx_info *info;

	/* nomal packet rx procedure */
	while (skb_queue_len(&priv->rx_queue) < MAX_RX_URB) {
		skb = __dev_alloc_skb(RX_URB_SIZE, GFP_KERNEL);
		if (!skb)
			break;
		entry = usb_alloc_urb(0, GFP_KERNEL);
		if (!entry) {
			kfree_skb(skb);
			break;
		}
		usb_fill_bulk_urb(entry, priv->udev,
				  usb_rcvbulkpipe(priv->udev, 3),
				  skb_tail_pointer(skb),
				  RX_URB_SIZE, rtl8192_rx_isr, skb);
		info = (struct rtl8192_rx_info *)skb->cb;
		info->urb = entry;
		info->dev = dev;
		info->out_pipe = 3; /* denote rx normal packet queue */
		skb_queue_tail(&priv->rx_queue, skb);
		usb_submit_urb(entry, GFP_KERNEL);
	}

	/* command packet rx procedure */
	while (skb_queue_len(&priv->rx_queue) < MAX_RX_URB + 3) {
		skb = __dev_alloc_skb(RX_URB_SIZE, GFP_KERNEL);
		if (!skb)
			break;
		entry = usb_alloc_urb(0, GFP_KERNEL);
		if (!entry) {
			kfree_skb(skb);
			break;
		}
		usb_fill_bulk_urb(entry, priv->udev,
				  usb_rcvbulkpipe(priv->udev, 9),
				  skb_tail_pointer(skb),
				  RX_URB_SIZE, rtl8192_rx_isr, skb);
		info = (struct rtl8192_rx_info *)skb->cb;
		info->urb = entry;
		info->dev = dev;
		info->out_pipe = 9; /* denote rx cmd packet queue */
		skb_queue_tail(&priv->rx_queue, skb);
		usb_submit_urb(entry, GFP_KERNEL);
	}
}
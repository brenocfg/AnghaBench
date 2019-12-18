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
struct rtl8187_rx_info {struct ieee80211_hw* dev; struct urb* urb; } ;
struct rtl8187_priv {int /*<<< orphan*/  anchored; int /*<<< orphan*/  rx_queue; scalar_t__ is_rtl8187b; int /*<<< orphan*/  udev; } ;
struct ieee80211_hw {struct rtl8187_priv* priv; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  RTL8187_MAX_RX ; 
 struct sk_buff* __dev_alloc_skb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  rtl8187_rx_cb ; 
 int skb_queue_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_tail_pointer (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_unlink (struct sk_buff*,int /*<<< orphan*/ *) ; 
 struct urb* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_anchor_urb (struct urb*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (struct urb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  usb_kill_anchored_urbs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_put_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (int /*<<< orphan*/ ,int) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_unanchor_urb (struct urb*) ; 

__attribute__((used)) static int rtl8187_init_urbs(struct ieee80211_hw *dev)
{
	struct rtl8187_priv *priv = dev->priv;
	struct urb *entry = NULL;
	struct sk_buff *skb;
	struct rtl8187_rx_info *info;
	int ret = 0;

	while (skb_queue_len(&priv->rx_queue) < 32) {
		skb = __dev_alloc_skb(RTL8187_MAX_RX, GFP_KERNEL);
		if (!skb) {
			ret = -ENOMEM;
			goto err;
		}
		entry = usb_alloc_urb(0, GFP_KERNEL);
		if (!entry) {
			ret = -ENOMEM;
			goto err;
		}
		usb_fill_bulk_urb(entry, priv->udev,
				  usb_rcvbulkpipe(priv->udev,
				  priv->is_rtl8187b ? 3 : 1),
				  skb_tail_pointer(skb),
				  RTL8187_MAX_RX, rtl8187_rx_cb, skb);
		info = (struct rtl8187_rx_info *)skb->cb;
		info->urb = entry;
		info->dev = dev;
		skb_queue_tail(&priv->rx_queue, skb);
		usb_anchor_urb(entry, &priv->anchored);
		ret = usb_submit_urb(entry, GFP_KERNEL);
		if (ret) {
			skb_unlink(skb, &priv->rx_queue);
			usb_unanchor_urb(entry);
			usb_put_urb(entry);
			goto err;
		}
		usb_put_urb(entry);
	}
	return ret;

err:
	kfree_skb(skb);
	usb_kill_anchored_urbs(&priv->anchored);
	return ret;
}
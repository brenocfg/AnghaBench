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
struct urb {int status; int actual_length; void* transfer_buffer; struct sk_buff* context; } ;
struct sk_buff {scalar_t__ cb; } ;
struct p54u_rx_info {struct ieee80211_hw* dev; struct urb* urb; } ;
struct TYPE_2__ {int tx_hdr_len; scalar_t__ fw_interface; scalar_t__ rx_mtu; } ;
struct p54u_priv {scalar_t__ hw_type; int /*<<< orphan*/  rx_queue; int /*<<< orphan*/  submitted; TYPE_1__ common; } ;
struct ieee80211_hw {struct p54u_priv* priv; } ;

/* Variables and functions */
 scalar_t__ FW_LM87 ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ P54U_NET2280 ; 
 struct sk_buff* dev_alloc_skb (scalar_t__) ; 
 int /*<<< orphan*/  dev_kfree_skb_irq (struct sk_buff*) ; 
 scalar_t__ p54_rx (struct ieee80211_hw*,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_tail_pointer (struct sk_buff*) ; 
 void* skb_tail_pointer (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_unlink (struct sk_buff*,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  usb_anchor_urb (struct urb*,int /*<<< orphan*/ *) ; 
 scalar_t__ usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_unanchor_urb (struct urb*) ; 

__attribute__((used)) static void p54u_rx_cb(struct urb *urb)
{
	struct sk_buff *skb = (struct sk_buff *) urb->context;
	struct p54u_rx_info *info = (struct p54u_rx_info *)skb->cb;
	struct ieee80211_hw *dev = info->dev;
	struct p54u_priv *priv = dev->priv;

	skb_unlink(skb, &priv->rx_queue);

	if (unlikely(urb->status)) {
		dev_kfree_skb_irq(skb);
		return;
	}

	skb_put(skb, urb->actual_length);

	if (priv->hw_type == P54U_NET2280)
		skb_pull(skb, priv->common.tx_hdr_len);
	if (priv->common.fw_interface == FW_LM87) {
		skb_pull(skb, 4);
		skb_put(skb, 4);
	}

	if (p54_rx(dev, skb)) {
		skb = dev_alloc_skb(priv->common.rx_mtu + 32);
		if (unlikely(!skb)) {
			/* TODO check rx queue length and refill *somewhere* */
			return;
		}

		info = (struct p54u_rx_info *) skb->cb;
		info->urb = urb;
		info->dev = dev;
		urb->transfer_buffer = skb_tail_pointer(skb);
		urb->context = skb;
	} else {
		if (priv->hw_type == P54U_NET2280)
			skb_push(skb, priv->common.tx_hdr_len);
		if (priv->common.fw_interface == FW_LM87) {
			skb_push(skb, 4);
			skb_put(skb, 4);
		}
		skb_reset_tail_pointer(skb);
		skb_trim(skb, 0);
		urb->transfer_buffer = skb_tail_pointer(skb);
	}
	skb_queue_tail(&priv->rx_queue, skb);
	usb_anchor_urb(urb, &priv->submitted);
	if (usb_submit_urb(urb, GFP_ATOMIC)) {
		skb_unlink(skb, &priv->rx_queue);
		usb_unanchor_urb(urb);
		dev_kfree_skb_irq(skb);
	}
}
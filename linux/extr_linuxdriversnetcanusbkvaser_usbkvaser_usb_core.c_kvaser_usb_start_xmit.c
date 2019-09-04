#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct urb {int dummy; } ;
struct sk_buff {int dummy; } ;
struct net_device_stats {int /*<<< orphan*/  tx_dropped; } ;
struct net_device {struct net_device_stats stats; } ;
struct kvaser_usb_tx_urb_context {unsigned int echo_index; struct kvaser_usb_net_priv* priv; int /*<<< orphan*/  dlc; } ;
struct kvaser_usb_net_priv {int active_tx_contexts; int /*<<< orphan*/  tx_contexts_lock; int /*<<< orphan*/  tx_submitted; struct kvaser_usb_tx_urb_context* tx_contexts; struct kvaser_usb* dev; } ;
struct kvaser_usb {unsigned int max_tx_urbs; TYPE_2__* bulk_out; int /*<<< orphan*/  udev; TYPE_1__* ops; } ;
typedef  int netdev_tx_t ;
struct TYPE_4__ {int /*<<< orphan*/  bEndpointAddress; } ;
struct TYPE_3__ {void* (* dev_frame_to_cmd ) (struct kvaser_usb_net_priv*,struct sk_buff*,int /*<<< orphan*/ *,int*,unsigned int) ;} ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int NETDEV_TX_BUSY ; 
 int NETDEV_TX_OK ; 
 scalar_t__ can_dropped_invalid_skb (struct net_device*,struct sk_buff*) ; 
 int /*<<< orphan*/  can_free_echo_skb (struct net_device*,unsigned int) ; 
 int /*<<< orphan*/  can_put_echo_skb (struct sk_buff*,struct net_device*,unsigned int) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 int /*<<< orphan*/  kvaser_usb_write_bulk_callback ; 
 struct kvaser_usb_net_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*,...) ; 
 int /*<<< orphan*/  netif_device_detach (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 void* stub1 (struct kvaser_usb_net_priv*,struct sk_buff*,int /*<<< orphan*/ *,int*,unsigned int) ; 
 scalar_t__ unlikely (int) ; 
 struct urb* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_anchor_urb (struct urb*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (struct urb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ,struct kvaser_usb_tx_urb_context*) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_unanchor_urb (struct urb*) ; 

__attribute__((used)) static netdev_tx_t kvaser_usb_start_xmit(struct sk_buff *skb,
					 struct net_device *netdev)
{
	struct kvaser_usb_net_priv *priv = netdev_priv(netdev);
	struct kvaser_usb *dev = priv->dev;
	struct net_device_stats *stats = &netdev->stats;
	struct kvaser_usb_tx_urb_context *context = NULL;
	struct urb *urb;
	void *buf;
	int cmd_len = 0;
	int err, ret = NETDEV_TX_OK;
	unsigned int i;
	unsigned long flags;

	if (can_dropped_invalid_skb(netdev, skb))
		return NETDEV_TX_OK;

	urb = usb_alloc_urb(0, GFP_ATOMIC);
	if (!urb) {
		stats->tx_dropped++;
		dev_kfree_skb(skb);
		return NETDEV_TX_OK;
	}

	spin_lock_irqsave(&priv->tx_contexts_lock, flags);
	for (i = 0; i < dev->max_tx_urbs; i++) {
		if (priv->tx_contexts[i].echo_index == dev->max_tx_urbs) {
			context = &priv->tx_contexts[i];

			context->echo_index = i;
			++priv->active_tx_contexts;
			if (priv->active_tx_contexts >= (int)dev->max_tx_urbs)
				netif_stop_queue(netdev);

			break;
		}
	}
	spin_unlock_irqrestore(&priv->tx_contexts_lock, flags);

	/* This should never happen; it implies a flow control bug */
	if (!context) {
		netdev_warn(netdev, "cannot find free context\n");

		ret = NETDEV_TX_BUSY;
		goto freeurb;
	}

	buf = dev->ops->dev_frame_to_cmd(priv, skb, &context->dlc, &cmd_len,
					 context->echo_index);
	if (!buf) {
		stats->tx_dropped++;
		dev_kfree_skb(skb);
		spin_lock_irqsave(&priv->tx_contexts_lock, flags);

		context->echo_index = dev->max_tx_urbs;
		--priv->active_tx_contexts;
		netif_wake_queue(netdev);

		spin_unlock_irqrestore(&priv->tx_contexts_lock, flags);
		goto freeurb;
	}

	context->priv = priv;

	can_put_echo_skb(skb, netdev, context->echo_index);

	usb_fill_bulk_urb(urb, dev->udev,
			  usb_sndbulkpipe(dev->udev,
					  dev->bulk_out->bEndpointAddress),
			  buf, cmd_len, kvaser_usb_write_bulk_callback,
			  context);
	usb_anchor_urb(urb, &priv->tx_submitted);

	err = usb_submit_urb(urb, GFP_ATOMIC);
	if (unlikely(err)) {
		spin_lock_irqsave(&priv->tx_contexts_lock, flags);

		can_free_echo_skb(netdev, context->echo_index);
		context->echo_index = dev->max_tx_urbs;
		--priv->active_tx_contexts;
		netif_wake_queue(netdev);

		spin_unlock_irqrestore(&priv->tx_contexts_lock, flags);

		usb_unanchor_urb(urb);
		kfree(buf);

		stats->tx_dropped++;

		if (err == -ENODEV)
			netif_device_detach(netdev);
		else
			netdev_warn(netdev, "Failed tx_urb %d\n", err);

		goto freeurb;
	}

	ret = NETDEV_TX_OK;

freeurb:
	usb_free_urb(urb);
	return ret;
}
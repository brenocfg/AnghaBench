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
typedef  int /*<<< orphan*/  u8 ;
struct usb_8dev_tx_urb_context {int echo_index; int /*<<< orphan*/  dlc; struct usb_8dev_priv* priv; } ;
struct usb_8dev_tx_msg {int flags; int /*<<< orphan*/  end; int /*<<< orphan*/  data; int /*<<< orphan*/  dlc; int /*<<< orphan*/  id; int /*<<< orphan*/  begin; } ;
struct usb_8dev_priv {int /*<<< orphan*/  active_tx_urbs; int /*<<< orphan*/  udev; int /*<<< orphan*/  tx_submitted; struct usb_8dev_tx_urb_context* tx_contexts; } ;
struct urb {int /*<<< orphan*/  transfer_dma; int /*<<< orphan*/  transfer_flags; } ;
struct sk_buff {scalar_t__ data; } ;
struct net_device_stats {int /*<<< orphan*/  tx_dropped; } ;
struct net_device {struct net_device_stats stats; } ;
struct can_frame {int can_id; int /*<<< orphan*/  can_dlc; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 int CAN_EFF_FLAG ; 
 int CAN_ERR_MASK ; 
 int CAN_RTR_FLAG ; 
 int ENODEV ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int MAX_TX_URBS ; 
 int /*<<< orphan*/  NETDEV_TX_BUSY ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  URB_NO_TRANSFER_DMA_MAP ; 
 int /*<<< orphan*/  USB_8DEV_DATA_END ; 
 int /*<<< orphan*/  USB_8DEV_DATA_START ; 
 int /*<<< orphan*/  USB_8DEV_ENDP_DATA_TX ; 
 int USB_8DEV_EXTID ; 
 int USB_8DEV_RTR ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ can_dropped_invalid_skb (struct net_device*,struct sk_buff*) ; 
 int /*<<< orphan*/  can_free_echo_skb (struct net_device*,int) ; 
 int /*<<< orphan*/  can_put_echo_skb (struct sk_buff*,struct net_device*,int) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct usb_8dev_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*,...) ; 
 int /*<<< orphan*/  netif_device_detach (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  usb_8dev_write_bulk_callback ; 
 int /*<<< orphan*/ * usb_alloc_coherent (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct urb* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_anchor_urb (struct urb*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (struct urb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,struct usb_8dev_tx_urb_context*) ; 
 int /*<<< orphan*/  usb_free_coherent (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_unanchor_urb (struct urb*) ; 

__attribute__((used)) static netdev_tx_t usb_8dev_start_xmit(struct sk_buff *skb,
				      struct net_device *netdev)
{
	struct usb_8dev_priv *priv = netdev_priv(netdev);
	struct net_device_stats *stats = &netdev->stats;
	struct can_frame *cf = (struct can_frame *) skb->data;
	struct usb_8dev_tx_msg *msg;
	struct urb *urb;
	struct usb_8dev_tx_urb_context *context = NULL;
	u8 *buf;
	int i, err;
	size_t size = sizeof(struct usb_8dev_tx_msg);

	if (can_dropped_invalid_skb(netdev, skb))
		return NETDEV_TX_OK;

	/* create a URB, and a buffer for it, and copy the data to the URB */
	urb = usb_alloc_urb(0, GFP_ATOMIC);
	if (!urb)
		goto nomem;

	buf = usb_alloc_coherent(priv->udev, size, GFP_ATOMIC,
				 &urb->transfer_dma);
	if (!buf) {
		netdev_err(netdev, "No memory left for USB buffer\n");
		goto nomembuf;
	}

	memset(buf, 0, size);

	msg = (struct usb_8dev_tx_msg *)buf;
	msg->begin = USB_8DEV_DATA_START;
	msg->flags = 0x00;

	if (cf->can_id & CAN_RTR_FLAG)
		msg->flags |= USB_8DEV_RTR;

	if (cf->can_id & CAN_EFF_FLAG)
		msg->flags |= USB_8DEV_EXTID;

	msg->id = cpu_to_be32(cf->can_id & CAN_ERR_MASK);
	msg->dlc = cf->can_dlc;
	memcpy(msg->data, cf->data, cf->can_dlc);
	msg->end = USB_8DEV_DATA_END;

	for (i = 0; i < MAX_TX_URBS; i++) {
		if (priv->tx_contexts[i].echo_index == MAX_TX_URBS) {
			context = &priv->tx_contexts[i];
			break;
		}
	}

	/* May never happen! When this happens we'd more URBs in flight as
	 * allowed (MAX_TX_URBS).
	 */
	if (!context)
		goto nofreecontext;

	context->priv = priv;
	context->echo_index = i;
	context->dlc = cf->can_dlc;

	usb_fill_bulk_urb(urb, priv->udev,
			  usb_sndbulkpipe(priv->udev, USB_8DEV_ENDP_DATA_TX),
			  buf, size, usb_8dev_write_bulk_callback, context);
	urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;
	usb_anchor_urb(urb, &priv->tx_submitted);

	can_put_echo_skb(skb, netdev, context->echo_index);

	atomic_inc(&priv->active_tx_urbs);

	err = usb_submit_urb(urb, GFP_ATOMIC);
	if (unlikely(err))
		goto failed;
	else if (atomic_read(&priv->active_tx_urbs) >= MAX_TX_URBS)
		/* Slow down tx path */
		netif_stop_queue(netdev);

	/* Release our reference to this URB, the USB core will eventually free
	 * it entirely.
	 */
	usb_free_urb(urb);

	return NETDEV_TX_OK;

nofreecontext:
	usb_free_coherent(priv->udev, size, buf, urb->transfer_dma);
	usb_free_urb(urb);

	netdev_warn(netdev, "couldn't find free context");

	return NETDEV_TX_BUSY;

failed:
	can_free_echo_skb(netdev, context->echo_index);

	usb_unanchor_urb(urb);
	usb_free_coherent(priv->udev, size, buf, urb->transfer_dma);

	atomic_dec(&priv->active_tx_urbs);

	if (err == -ENODEV)
		netif_device_detach(netdev);
	else
		netdev_warn(netdev, "failed tx_urb %d\n", err);

nomembuf:
	usb_free_urb(urb);

nomem:
	dev_kfree_skb(skb);
	stats->tx_dropped++;

	return NETDEV_TX_OK;
}
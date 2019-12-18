#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct urb {int /*<<< orphan*/  transfer_dma; int /*<<< orphan*/  transfer_flags; } ;
struct sk_buff {scalar_t__ data; } ;
struct net_device_stats {int /*<<< orphan*/  tx_dropped; } ;
struct net_device {struct net_device_stats stats; } ;
struct esd_usb2_net_priv {int /*<<< orphan*/  active_tx_jobs; int /*<<< orphan*/  tx_submitted; struct esd_tx_urb_context* tx_contexts; int /*<<< orphan*/  index; struct esd_usb2* usb2; } ;
struct TYPE_5__ {int len; int /*<<< orphan*/  cmd; } ;
struct TYPE_4__ {int dlc; int hnd; int /*<<< orphan*/ * data; int /*<<< orphan*/  id; int /*<<< orphan*/  net; } ;
struct TYPE_6__ {TYPE_2__ hdr; TYPE_1__ tx; } ;
struct esd_usb2_msg {TYPE_3__ msg; } ;
struct esd_usb2 {int /*<<< orphan*/  udev; } ;
struct esd_tx_urb_context {int echo_index; int dlc; struct esd_usb2_net_priv* priv; } ;
struct can_frame {int can_dlc; int can_id; int /*<<< orphan*/ * data; } ;
typedef  int netdev_tx_t ;

/* Variables and functions */
 int CAN_EFF_FLAG ; 
 int CAN_ERR_MASK ; 
 int CAN_RTR_FLAG ; 
 int /*<<< orphan*/  CMD_CAN_TX ; 
 int ENODEV ; 
 int ESD_EXTID ; 
 int ESD_RTR ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int MAX_TX_URBS ; 
 int NETDEV_TX_BUSY ; 
 int NETDEV_TX_OK ; 
 int /*<<< orphan*/  URB_NO_TRANSFER_DMA_MAP ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ can_dropped_invalid_skb (struct net_device*,struct sk_buff*) ; 
 int /*<<< orphan*/  can_free_echo_skb (struct net_device*,int) ; 
 int /*<<< orphan*/  can_put_echo_skb (struct sk_buff*,struct net_device*,int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  esd_usb2_write_bulk_callback ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct esd_usb2_net_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*,...) ; 
 int /*<<< orphan*/  netif_device_detach (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_trans_update (struct net_device*) ; 
 int /*<<< orphan*/ * usb_alloc_coherent (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct urb* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_anchor_urb (struct urb*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (struct urb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct esd_tx_urb_context*) ; 
 int /*<<< orphan*/  usb_free_coherent (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (int /*<<< orphan*/ ,int) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_unanchor_urb (struct urb*) ; 

__attribute__((used)) static netdev_tx_t esd_usb2_start_xmit(struct sk_buff *skb,
				      struct net_device *netdev)
{
	struct esd_usb2_net_priv *priv = netdev_priv(netdev);
	struct esd_usb2 *dev = priv->usb2;
	struct esd_tx_urb_context *context = NULL;
	struct net_device_stats *stats = &netdev->stats;
	struct can_frame *cf = (struct can_frame *)skb->data;
	struct esd_usb2_msg *msg;
	struct urb *urb;
	u8 *buf;
	int i, err;
	int ret = NETDEV_TX_OK;
	size_t size = sizeof(struct esd_usb2_msg);

	if (can_dropped_invalid_skb(netdev, skb))
		return NETDEV_TX_OK;

	/* create a URB, and a buffer for it, and copy the data to the URB */
	urb = usb_alloc_urb(0, GFP_ATOMIC);
	if (!urb) {
		stats->tx_dropped++;
		dev_kfree_skb(skb);
		goto nourbmem;
	}

	buf = usb_alloc_coherent(dev->udev, size, GFP_ATOMIC,
				 &urb->transfer_dma);
	if (!buf) {
		netdev_err(netdev, "No memory left for USB buffer\n");
		stats->tx_dropped++;
		dev_kfree_skb(skb);
		goto nobufmem;
	}

	msg = (struct esd_usb2_msg *)buf;

	msg->msg.hdr.len = 3; /* minimal length */
	msg->msg.hdr.cmd = CMD_CAN_TX;
	msg->msg.tx.net = priv->index;
	msg->msg.tx.dlc = cf->can_dlc;
	msg->msg.tx.id = cpu_to_le32(cf->can_id & CAN_ERR_MASK);

	if (cf->can_id & CAN_RTR_FLAG)
		msg->msg.tx.dlc |= ESD_RTR;

	if (cf->can_id & CAN_EFF_FLAG)
		msg->msg.tx.id |= cpu_to_le32(ESD_EXTID);

	for (i = 0; i < cf->can_dlc; i++)
		msg->msg.tx.data[i] = cf->data[i];

	msg->msg.hdr.len += (cf->can_dlc + 3) >> 2;

	for (i = 0; i < MAX_TX_URBS; i++) {
		if (priv->tx_contexts[i].echo_index == MAX_TX_URBS) {
			context = &priv->tx_contexts[i];
			break;
		}
	}

	/*
	 * This may never happen.
	 */
	if (!context) {
		netdev_warn(netdev, "couldn't find free context\n");
		ret = NETDEV_TX_BUSY;
		goto releasebuf;
	}

	context->priv = priv;
	context->echo_index = i;
	context->dlc = cf->can_dlc;

	/* hnd must not be 0 - MSB is stripped in txdone handling */
	msg->msg.tx.hnd = 0x80000000 | i; /* returned in TX done message */

	usb_fill_bulk_urb(urb, dev->udev, usb_sndbulkpipe(dev->udev, 2), buf,
			  msg->msg.hdr.len << 2,
			  esd_usb2_write_bulk_callback, context);

	urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;

	usb_anchor_urb(urb, &priv->tx_submitted);

	can_put_echo_skb(skb, netdev, context->echo_index);

	atomic_inc(&priv->active_tx_jobs);

	/* Slow down tx path */
	if (atomic_read(&priv->active_tx_jobs) >= MAX_TX_URBS)
		netif_stop_queue(netdev);

	err = usb_submit_urb(urb, GFP_ATOMIC);
	if (err) {
		can_free_echo_skb(netdev, context->echo_index);

		atomic_dec(&priv->active_tx_jobs);
		usb_unanchor_urb(urb);

		stats->tx_dropped++;

		if (err == -ENODEV)
			netif_device_detach(netdev);
		else
			netdev_warn(netdev, "failed tx_urb %d\n", err);

		goto releasebuf;
	}

	netif_trans_update(netdev);

	/*
	 * Release our reference to this URB, the USB core will eventually free
	 * it entirely.
	 */
	usb_free_urb(urb);

	return NETDEV_TX_OK;

releasebuf:
	usb_free_coherent(dev->udev, size, buf, urb->transfer_dma);

nobufmem:
	usb_free_urb(urb);

nourbmem:
	return ret;
}
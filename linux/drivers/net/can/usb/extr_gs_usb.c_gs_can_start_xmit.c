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
struct urb {int /*<<< orphan*/  transfer_dma; int /*<<< orphan*/  transfer_flags; } ;
struct sk_buff {scalar_t__ data; } ;
struct net_device_stats {int /*<<< orphan*/  tx_dropped; } ;
struct net_device {int dummy; } ;
struct gs_tx_context {unsigned int echo_id; } ;
struct gs_host_frame {unsigned int echo_id; int /*<<< orphan*/  data; int /*<<< orphan*/  can_dlc; int /*<<< orphan*/  can_id; int /*<<< orphan*/  channel; } ;
struct gs_can {int /*<<< orphan*/  udev; int /*<<< orphan*/  active_tx_urbs; int /*<<< orphan*/  tx_submitted; int /*<<< orphan*/  channel; TYPE_1__* netdev; } ;
struct can_frame {int /*<<< orphan*/  can_dlc; int /*<<< orphan*/  data; int /*<<< orphan*/  can_id; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
struct TYPE_2__ {struct net_device_stats stats; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GSUSB_ENDPOINT_OUT ; 
 unsigned int GS_MAX_TX_URBS ; 
 int /*<<< orphan*/  NETDEV_TX_BUSY ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  URB_NO_TRANSFER_DMA_MAP ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 unsigned int atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ can_dropped_invalid_skb (struct net_device*,struct sk_buff*) ; 
 int /*<<< orphan*/  can_free_echo_skb (struct net_device*,unsigned int) ; 
 int /*<<< orphan*/  can_put_echo_skb (struct sk_buff*,struct net_device*,unsigned int) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 struct gs_tx_context* gs_alloc_tx_context (struct gs_can*) ; 
 int /*<<< orphan*/  gs_free_tx_context (struct gs_tx_context*) ; 
 int /*<<< orphan*/  gs_usb_xmit_callback ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,...) ; 
 struct gs_can* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_detach (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 scalar_t__ unlikely (int) ; 
 struct gs_host_frame* usb_alloc_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct urb* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_anchor_urb (struct urb*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (struct urb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gs_host_frame*,int,int /*<<< orphan*/ ,struct gs_tx_context*) ; 
 int /*<<< orphan*/  usb_free_coherent (int /*<<< orphan*/ ,int,struct gs_host_frame*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_unanchor_urb (struct urb*) ; 

__attribute__((used)) static netdev_tx_t gs_can_start_xmit(struct sk_buff *skb,
				     struct net_device *netdev)
{
	struct gs_can *dev = netdev_priv(netdev);
	struct net_device_stats *stats = &dev->netdev->stats;
	struct urb *urb;
	struct gs_host_frame *hf;
	struct can_frame *cf;
	int rc;
	unsigned int idx;
	struct gs_tx_context *txc;

	if (can_dropped_invalid_skb(netdev, skb))
		return NETDEV_TX_OK;

	/* find an empty context to keep track of transmission */
	txc = gs_alloc_tx_context(dev);
	if (!txc)
		return NETDEV_TX_BUSY;

	/* create a URB, and a buffer for it */
	urb = usb_alloc_urb(0, GFP_ATOMIC);
	if (!urb)
		goto nomem_urb;

	hf = usb_alloc_coherent(dev->udev, sizeof(*hf), GFP_ATOMIC,
				&urb->transfer_dma);
	if (!hf) {
		netdev_err(netdev, "No memory left for USB buffer\n");
		goto nomem_hf;
	}

	idx = txc->echo_id;

	if (idx >= GS_MAX_TX_URBS) {
		netdev_err(netdev, "Invalid tx context %d\n", idx);
		goto badidx;
	}

	hf->echo_id = idx;
	hf->channel = dev->channel;

	cf = (struct can_frame *)skb->data;

	hf->can_id = cf->can_id;
	hf->can_dlc = cf->can_dlc;
	memcpy(hf->data, cf->data, cf->can_dlc);

	usb_fill_bulk_urb(urb, dev->udev,
			  usb_sndbulkpipe(dev->udev, GSUSB_ENDPOINT_OUT),
			  hf,
			  sizeof(*hf),
			  gs_usb_xmit_callback,
			  txc);

	urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;
	usb_anchor_urb(urb, &dev->tx_submitted);

	can_put_echo_skb(skb, netdev, idx);

	atomic_inc(&dev->active_tx_urbs);

	rc = usb_submit_urb(urb, GFP_ATOMIC);
	if (unlikely(rc)) {			/* usb send failed */
		atomic_dec(&dev->active_tx_urbs);

		can_free_echo_skb(netdev, idx);
		gs_free_tx_context(txc);

		usb_unanchor_urb(urb);
		usb_free_coherent(dev->udev,
				  sizeof(*hf),
				  hf,
				  urb->transfer_dma);

		if (rc == -ENODEV) {
			netif_device_detach(netdev);
		} else {
			netdev_err(netdev, "usb_submit failed (err=%d)\n", rc);
			stats->tx_dropped++;
		}
	} else {
		/* Slow down tx path */
		if (atomic_read(&dev->active_tx_urbs) >= GS_MAX_TX_URBS)
			netif_stop_queue(netdev);
	}

	/* let usb core take care of this urb */
	usb_free_urb(urb);

	return NETDEV_TX_OK;

 badidx:
	usb_free_coherent(dev->udev,
			  sizeof(*hf),
			  hf,
			  urb->transfer_dma);
 nomem_hf:
	usb_free_urb(urb);

 nomem_urb:
	gs_free_tx_context(txc);
	dev_kfree_skb(skb);
	stats->tx_dropped++;
	return NETDEV_TX_OK;
}
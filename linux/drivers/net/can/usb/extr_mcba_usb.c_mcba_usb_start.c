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
struct urb {int /*<<< orphan*/  transfer_dma; int /*<<< orphan*/  transfer_flags; } ;
struct net_device {int dummy; } ;
struct mcba_priv {int /*<<< orphan*/  udev; int /*<<< orphan*/  rx_submitted; struct net_device* netdev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MCBA_MAX_RX_URBS ; 
 int /*<<< orphan*/  MCBA_USB_EP_IN ; 
 int /*<<< orphan*/  MCBA_USB_RX_BUFF_SIZE ; 
 int /*<<< orphan*/  MCBA_VER_REQ_CAN ; 
 int /*<<< orphan*/  MCBA_VER_REQ_USB ; 
 int /*<<< orphan*/  URB_NO_TRANSFER_DMA_MAP ; 
 int /*<<< orphan*/  mcba_init_ctx (struct mcba_priv*) ; 
 int /*<<< orphan*/  mcba_usb_read_bulk_callback ; 
 int /*<<< orphan*/  mcba_usb_xmit_read_fw_ver (struct mcba_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*) ; 
 int /*<<< orphan*/ * usb_alloc_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct urb* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_anchor_urb (struct urb*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (struct urb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mcba_priv*) ; 
 int /*<<< orphan*/  usb_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_unanchor_urb (struct urb*) ; 

__attribute__((used)) static int mcba_usb_start(struct mcba_priv *priv)
{
	struct net_device *netdev = priv->netdev;
	int err, i;

	mcba_init_ctx(priv);

	for (i = 0; i < MCBA_MAX_RX_URBS; i++) {
		struct urb *urb = NULL;
		u8 *buf;

		/* create a URB, and a buffer for it */
		urb = usb_alloc_urb(0, GFP_KERNEL);
		if (!urb) {
			err = -ENOMEM;
			break;
		}

		buf = usb_alloc_coherent(priv->udev, MCBA_USB_RX_BUFF_SIZE,
					 GFP_KERNEL, &urb->transfer_dma);
		if (!buf) {
			netdev_err(netdev, "No memory left for USB buffer\n");
			usb_free_urb(urb);
			err = -ENOMEM;
			break;
		}

		usb_fill_bulk_urb(urb, priv->udev,
				  usb_rcvbulkpipe(priv->udev, MCBA_USB_EP_IN),
				  buf, MCBA_USB_RX_BUFF_SIZE,
				  mcba_usb_read_bulk_callback, priv);
		urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;
		usb_anchor_urb(urb, &priv->rx_submitted);

		err = usb_submit_urb(urb, GFP_KERNEL);
		if (err) {
			usb_unanchor_urb(urb);
			usb_free_coherent(priv->udev, MCBA_USB_RX_BUFF_SIZE,
					  buf, urb->transfer_dma);
			usb_free_urb(urb);
			break;
		}

		/* Drop reference, USB core will take care of freeing it */
		usb_free_urb(urb);
	}

	/* Did we submit any URBs */
	if (i == 0) {
		netdev_warn(netdev, "couldn't setup read URBs\n");
		return err;
	}

	/* Warn if we've couldn't transmit all the URBs */
	if (i < MCBA_MAX_RX_URBS)
		netdev_warn(netdev, "rx performance may be slow\n");

	mcba_usb_xmit_read_fw_ver(priv, MCBA_VER_REQ_USB);
	mcba_usb_xmit_read_fw_ver(priv, MCBA_VER_REQ_CAN);

	return err;
}
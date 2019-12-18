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
struct urb {int dummy; } ;
struct net_device {int dummy; } ;
struct kvaser_usb_net_priv {int /*<<< orphan*/  tx_submitted; struct net_device* netdev; struct kvaser_usb* dev; } ;
struct kvaser_usb {TYPE_1__* bulk_out; int /*<<< orphan*/  udev; } ;
struct TYPE_2__ {int /*<<< orphan*/  bEndpointAddress; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  kvaser_usb_send_cmd_callback ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct urb* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_anchor_urb (struct urb*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (struct urb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_unanchor_urb (struct urb*) ; 

int kvaser_usb_send_cmd_async(struct kvaser_usb_net_priv *priv, void *cmd,
			      int len)
{
	struct kvaser_usb *dev = priv->dev;
	struct net_device *netdev = priv->netdev;
	struct urb *urb;
	int err;

	urb = usb_alloc_urb(0, GFP_ATOMIC);
	if (!urb)
		return -ENOMEM;

	usb_fill_bulk_urb(urb, dev->udev,
			  usb_sndbulkpipe(dev->udev,
					  dev->bulk_out->bEndpointAddress),
			  cmd, len, kvaser_usb_send_cmd_callback, netdev);
	usb_anchor_urb(urb, &priv->tx_submitted);

	err = usb_submit_urb(urb, GFP_ATOMIC);
	if (err) {
		netdev_err(netdev, "Error transmitting URB\n");
		usb_unanchor_urb(urb);
	}
	usb_free_urb(urb);

	return 0;
}
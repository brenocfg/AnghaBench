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
struct urb {int /*<<< orphan*/  status; int /*<<< orphan*/  transfer_buffer; struct kvaser_usb_tx_urb_context* context; } ;
struct net_device {int dummy; } ;
struct kvaser_usb_tx_urb_context {struct kvaser_usb_net_priv* priv; } ;
struct kvaser_usb_net_priv {struct net_device* netdev; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_device_present (struct net_device*) ; 

__attribute__((used)) static void kvaser_usb_write_bulk_callback(struct urb *urb)
{
	struct kvaser_usb_tx_urb_context *context = urb->context;
	struct kvaser_usb_net_priv *priv;
	struct net_device *netdev;

	if (WARN_ON(!context))
		return;

	priv = context->priv;
	netdev = priv->netdev;

	kfree(urb->transfer_buffer);

	if (!netif_device_present(netdev))
		return;

	if (urb->status)
		netdev_info(netdev, "Tx URB aborted (%d)\n", urb->status);
}
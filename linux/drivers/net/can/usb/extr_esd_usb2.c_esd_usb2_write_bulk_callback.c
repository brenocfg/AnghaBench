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
struct urb {int /*<<< orphan*/  status; int /*<<< orphan*/  transfer_dma; int /*<<< orphan*/  transfer_buffer; int /*<<< orphan*/  dev; struct esd_tx_urb_context* context; } ;
struct net_device {int dummy; } ;
struct esd_usb2_net_priv {struct net_device* netdev; } ;
struct esd_usb2_msg {int dummy; } ;
struct esd_tx_urb_context {struct esd_usb2_net_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_device_present (struct net_device*) ; 
 int /*<<< orphan*/  netif_trans_update (struct net_device*) ; 
 int /*<<< orphan*/  usb_free_coherent (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void esd_usb2_write_bulk_callback(struct urb *urb)
{
	struct esd_tx_urb_context *context = urb->context;
	struct esd_usb2_net_priv *priv;
	struct net_device *netdev;
	size_t size = sizeof(struct esd_usb2_msg);

	WARN_ON(!context);

	priv = context->priv;
	netdev = priv->netdev;

	/* free up our allocated buffer */
	usb_free_coherent(urb->dev, size,
			  urb->transfer_buffer, urb->transfer_dma);

	if (!netif_device_present(netdev))
		return;

	if (urb->status)
		netdev_info(netdev, "Tx URB aborted (%d)\n", urb->status);

	netif_trans_update(netdev);
}
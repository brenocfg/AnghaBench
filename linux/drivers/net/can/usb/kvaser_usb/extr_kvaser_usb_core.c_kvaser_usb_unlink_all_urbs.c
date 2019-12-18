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
struct kvaser_usb_net_priv {int dummy; } ;
struct kvaser_usb {int nchannels; struct kvaser_usb_net_priv** nets; int /*<<< orphan*/ * rxbuf_dma; int /*<<< orphan*/ * rxbuf; int /*<<< orphan*/  udev; int /*<<< orphan*/  rx_submitted; } ;

/* Variables and functions */
 int KVASER_USB_MAX_RX_URBS ; 
 int /*<<< orphan*/  KVASER_USB_RX_BUFFER_SIZE ; 
 int /*<<< orphan*/  kvaser_usb_unlink_tx_urbs (struct kvaser_usb_net_priv*) ; 
 int /*<<< orphan*/  usb_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_kill_anchored_urbs (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void kvaser_usb_unlink_all_urbs(struct kvaser_usb *dev)
{
	int i;

	usb_kill_anchored_urbs(&dev->rx_submitted);

	for (i = 0; i < KVASER_USB_MAX_RX_URBS; i++)
		usb_free_coherent(dev->udev, KVASER_USB_RX_BUFFER_SIZE,
				  dev->rxbuf[i], dev->rxbuf_dma[i]);

	for (i = 0; i < dev->nchannels; i++) {
		struct kvaser_usb_net_priv *priv = dev->nets[i];

		if (priv)
			kvaser_usb_unlink_tx_urbs(priv);
	}
}
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
struct usb_interface {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  bt_datalen; int /*<<< orphan*/  tp_datalen; } ;
struct bcm5974 {TYPE_2__* bt_urb; TYPE_2__* tp_urb; int /*<<< orphan*/  bt_data; TYPE_1__ cfg; int /*<<< orphan*/  udev; int /*<<< orphan*/  tp_data; int /*<<< orphan*/  input; } ;
struct TYPE_4__ {int /*<<< orphan*/  transfer_dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct bcm5974*) ; 
 int /*<<< orphan*/  usb_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (TYPE_2__*) ; 
 struct bcm5974* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bcm5974_disconnect(struct usb_interface *iface)
{
	struct bcm5974 *dev = usb_get_intfdata(iface);

	usb_set_intfdata(iface, NULL);

	input_unregister_device(dev->input);
	usb_free_coherent(dev->udev, dev->cfg.tp_datalen,
			  dev->tp_data, dev->tp_urb->transfer_dma);
	if (dev->bt_urb)
		usb_free_coherent(dev->udev, dev->cfg.bt_datalen,
				  dev->bt_data, dev->bt_urb->transfer_dma);
	usb_free_urb(dev->tp_urb);
	usb_free_urb(dev->bt_urb);
	kfree(dev);
}
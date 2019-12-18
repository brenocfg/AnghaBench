#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct atp {TYPE_2__* urb; int /*<<< orphan*/  data; TYPE_1__* info; int /*<<< orphan*/  udev; int /*<<< orphan*/  input; } ;
struct TYPE_5__ {int /*<<< orphan*/  transfer_dma; } ;
struct TYPE_4__ {int /*<<< orphan*/  datalen; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct atp*) ; 
 int /*<<< orphan*/  usb_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (TYPE_2__*) ; 
 struct atp* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_kill_urb (TYPE_2__*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void atp_disconnect(struct usb_interface *iface)
{
	struct atp *dev = usb_get_intfdata(iface);

	usb_set_intfdata(iface, NULL);
	if (dev) {
		usb_kill_urb(dev->urb);
		input_unregister_device(dev->input);
		usb_free_coherent(dev->udev, dev->info->datalen,
				  dev->data, dev->urb->transfer_dma);
		usb_free_urb(dev->urb);
		kfree(dev);
	}
	dev_info(&iface->dev, "input: appletouch disconnected\n");
}
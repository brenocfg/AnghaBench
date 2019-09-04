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
struct usb_interface {int dummy; } ;
struct usb_device {int dummy; } ;
struct mceusb_dev {int /*<<< orphan*/  dma_in; int /*<<< orphan*/  buf_in; int /*<<< orphan*/  len_in; int /*<<< orphan*/  urb_in; int /*<<< orphan*/  rc; int /*<<< orphan*/  kevent; int /*<<< orphan*/ * usbdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kfree (struct mceusb_dev*) ; 
 int /*<<< orphan*/  rc_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_coherent (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 
 struct mceusb_dev* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_put_dev (struct usb_device*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mceusb_dev_disconnect(struct usb_interface *intf)
{
	struct usb_device *dev = interface_to_usbdev(intf);
	struct mceusb_dev *ir = usb_get_intfdata(intf);

	usb_set_intfdata(intf, NULL);

	if (!ir)
		return;

	ir->usbdev = NULL;
	cancel_work_sync(&ir->kevent);
	rc_unregister_device(ir->rc);
	usb_kill_urb(ir->urb_in);
	usb_free_urb(ir->urb_in);
	usb_free_coherent(dev, ir->len_in, ir->buf_in, ir->dma_in);
	usb_put_dev(dev);

	kfree(ir);
}
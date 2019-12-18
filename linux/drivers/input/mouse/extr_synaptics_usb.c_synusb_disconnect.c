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
struct usb_interface {int dummy; } ;
struct usb_device {int dummy; } ;
struct synusb {int flags; TYPE_1__* urb; int /*<<< orphan*/  data; int /*<<< orphan*/  input; } ;
struct TYPE_2__ {int /*<<< orphan*/  transfer_dma; } ;

/* Variables and functions */
 int SYNUSB_IO_ALWAYS ; 
 int /*<<< orphan*/  SYNUSB_RECV_SIZE ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kfree (struct synusb*) ; 
 int /*<<< orphan*/  synusb_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_coherent (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (TYPE_1__*) ; 
 struct synusb* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void synusb_disconnect(struct usb_interface *intf)
{
	struct synusb *synusb = usb_get_intfdata(intf);
	struct usb_device *udev = interface_to_usbdev(intf);

	if (synusb->flags & SYNUSB_IO_ALWAYS)
		synusb_close(synusb->input);

	input_unregister_device(synusb->input);

	usb_free_coherent(udev, SYNUSB_RECV_SIZE, synusb->data,
			  synusb->urb->transfer_dma);
	usb_free_urb(synusb->urb);
	kfree(synusb);

	usb_set_intfdata(intf, NULL);
}
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
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct usb_device {int dummy; } ;
struct gtco {int /*<<< orphan*/  buf_dma; int /*<<< orphan*/  buffer; int /*<<< orphan*/  urbinfo; int /*<<< orphan*/  inputdevice; } ;

/* Variables and functions */
 int /*<<< orphan*/  REPORT_MAX_SIZE ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kfree (struct gtco*) ; 
 int /*<<< orphan*/  usb_free_coherent (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 
 struct gtco* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gtco_disconnect(struct usb_interface *interface)
{
	/* Grab private device ptr */
	struct gtco *gtco = usb_get_intfdata(interface);
	struct usb_device *udev = interface_to_usbdev(interface);

	/* Now reverse all the registration stuff */
	if (gtco) {
		input_unregister_device(gtco->inputdevice);
		usb_kill_urb(gtco->urbinfo);
		usb_free_urb(gtco->urbinfo);
		usb_free_coherent(udev, REPORT_MAX_SIZE,
				  gtco->buffer, gtco->buf_dma);
		kfree(gtco);
	}

	dev_info(&interface->dev, "gtco driver disconnected\n");
}
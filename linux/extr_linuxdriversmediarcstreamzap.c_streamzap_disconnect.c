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
struct streamzap_ir {int /*<<< orphan*/  dma_in; int /*<<< orphan*/  buf_in; int /*<<< orphan*/  buf_in_len; int /*<<< orphan*/  urb_in; int /*<<< orphan*/  rdev; int /*<<< orphan*/ * usbdev; } ;

/* Variables and functions */
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kfree (struct streamzap_ir*) ; 
 int /*<<< orphan*/  rc_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_coherent (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 
 struct streamzap_ir* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void streamzap_disconnect(struct usb_interface *interface)
{
	struct streamzap_ir *sz = usb_get_intfdata(interface);
	struct usb_device *usbdev = interface_to_usbdev(interface);

	usb_set_intfdata(interface, NULL);

	if (!sz)
		return;

	sz->usbdev = NULL;
	rc_unregister_device(sz->rdev);
	usb_kill_urb(sz->urb_in);
	usb_free_urb(sz->urb_in);
	usb_free_coherent(usbdev, sz->buf_in_len, sz->buf_in, sz->dma_in);

	kfree(sz);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {int dummy; } ;
struct usb_device {int dummy; } ;
struct ttusbir {TYPE_1__* bulk_urb; TYPE_1__** urb; int /*<<< orphan*/  led; int /*<<< orphan*/  rc; struct usb_device* udev; } ;
struct TYPE_3__ {int /*<<< orphan*/  transfer_dma; int /*<<< orphan*/  transfer_buffer; } ;

/* Variables and functions */
 int NUM_URBS ; 
 int /*<<< orphan*/  kfree (struct ttusbir*) ; 
 int /*<<< orphan*/  led_classdev_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rc_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_coherent (struct usb_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (TYPE_1__*) ; 
 struct ttusbir* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_kill_urb (TYPE_1__*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ttusbir_disconnect(struct usb_interface *intf)
{
	struct ttusbir *tt = usb_get_intfdata(intf);
	struct usb_device *udev = tt->udev;
	int i;

	tt->udev = NULL;

	rc_unregister_device(tt->rc);
	led_classdev_unregister(&tt->led);
	for (i = 0; i < NUM_URBS; i++) {
		usb_kill_urb(tt->urb[i]);
		usb_free_coherent(udev, 128, tt->urb[i]->transfer_buffer,
						tt->urb[i]->transfer_dma);
		usb_free_urb(tt->urb[i]);
	}
	usb_kill_urb(tt->bulk_urb);
	usb_free_urb(tt->bulk_urb);
	usb_set_intfdata(intf, NULL);
	kfree(tt);
}
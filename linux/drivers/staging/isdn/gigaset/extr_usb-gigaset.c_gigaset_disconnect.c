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
struct usb_cardstate {int /*<<< orphan*/ * udev; int /*<<< orphan*/ * interface; int /*<<< orphan*/ * bulk_out_buffer; int /*<<< orphan*/ * rcvbuf; int /*<<< orphan*/ * bulk_out_urb; int /*<<< orphan*/ * read_urb; } ;
struct TYPE_2__ {struct usb_cardstate* usb; } ;
struct cardstate {int /*<<< orphan*/ * dev; int /*<<< orphan*/  write_tasklet; TYPE_1__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  gigaset_freecs (struct cardstate*) ; 
 int /*<<< orphan*/  gigaset_stop (struct cardstate*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ *) ; 
 struct cardstate* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_put_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gigaset_disconnect(struct usb_interface *interface)
{
	struct cardstate *cs;
	struct usb_cardstate *ucs;

	cs = usb_get_intfdata(interface);
	ucs = cs->hw.usb;

	dev_info(cs->dev, "disconnecting Gigaset USB adapter\n");

	usb_kill_urb(ucs->read_urb);

	gigaset_stop(cs);

	usb_set_intfdata(interface, NULL);
	tasklet_kill(&cs->write_tasklet);

	usb_kill_urb(ucs->bulk_out_urb);

	kfree(ucs->bulk_out_buffer);
	usb_free_urb(ucs->bulk_out_urb);
	kfree(ucs->rcvbuf);
	usb_free_urb(ucs->read_urb);
	ucs->read_urb = ucs->bulk_out_urb = NULL;
	ucs->rcvbuf = ucs->bulk_out_buffer = NULL;

	usb_put_dev(ucs->udev);
	ucs->interface = NULL;
	ucs->udev = NULL;
	cs->dev = NULL;
	gigaset_freecs(cs);
}
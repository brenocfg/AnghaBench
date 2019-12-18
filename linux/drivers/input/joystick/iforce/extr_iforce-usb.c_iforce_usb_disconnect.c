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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct iforce_usb {int /*<<< orphan*/  out; int /*<<< orphan*/  irq; TYPE_1__ iforce; } ;

/* Variables and functions */
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct iforce_usb*) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 
 struct iforce_usb* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iforce_usb_disconnect(struct usb_interface *intf)
{
	struct iforce_usb *iforce_usb = usb_get_intfdata(intf);

	usb_set_intfdata(intf, NULL);

	input_unregister_device(iforce_usb->iforce.dev);

	usb_free_urb(iforce_usb->irq);
	usb_free_urb(iforce_usb->out);

	kfree(iforce_usb);
}
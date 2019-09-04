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
struct iforce {int /*<<< orphan*/  ctrl; int /*<<< orphan*/  out; int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct iforce*) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 
 struct iforce* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iforce_usb_disconnect(struct usb_interface *intf)
{
	struct iforce *iforce = usb_get_intfdata(intf);

	usb_set_intfdata(intf, NULL);

	input_unregister_device(iforce->dev);

	usb_free_urb(iforce->irq);
	usb_free_urb(iforce->out);
	usb_free_urb(iforce->ctrl);

	kfree(iforce);
}
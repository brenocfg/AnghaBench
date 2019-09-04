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
struct vprbrd {int /*<<< orphan*/  usb_dev; } ;
struct usb_interface {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kfree (struct vprbrd*) ; 
 int /*<<< orphan*/  mfd_remove_devices (int /*<<< orphan*/ *) ; 
 struct vprbrd* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_put_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vprbrd_disconnect(struct usb_interface *interface)
{
	struct vprbrd *vb = usb_get_intfdata(interface);

	mfd_remove_devices(&interface->dev);
	usb_set_intfdata(interface, NULL);
	usb_put_dev(vb->usb_dev);
	kfree(vb);

	dev_dbg(&interface->dev, "disconnected\n");
}
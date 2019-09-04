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
struct kvaser_usb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvaser_usb_remove_interfaces (struct kvaser_usb*) ; 
 struct kvaser_usb* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void kvaser_usb_disconnect(struct usb_interface *intf)
{
	struct kvaser_usb *dev = usb_get_intfdata(intf);

	usb_set_intfdata(intf, NULL);

	if (!dev)
		return;

	kvaser_usb_remove_interfaces(dev);
}
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
struct dvb_usb_device {TYPE_1__* desc; } ;
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  dvb_usb_exit (struct dvb_usb_device*) ; 
 int /*<<< orphan*/  info (char*,char const*) ; 
 struct dvb_usb_device* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

void dvb_usb_device_exit(struct usb_interface *intf)
{
	struct dvb_usb_device *d = usb_get_intfdata(intf);
	const char *name = "generic DVB-USB module";

	usb_set_intfdata(intf, NULL);
	if (d != NULL && d->desc != NULL) {
		name = d->desc->name;
		dvb_usb_exit(d);
	}
	info("%s successfully deinitialized and disconnected.", name);

}
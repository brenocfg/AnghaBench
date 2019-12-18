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
typedef  int /*<<< orphan*/  name ;
struct TYPE_2__ {char const* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  dvb_usb_exit (struct dvb_usb_device*) ; 
 int /*<<< orphan*/  info (char*,char*) ; 
 int /*<<< orphan*/  strscpy (char*,char const*,int) ; 
 struct dvb_usb_device* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

void dvb_usb_device_exit(struct usb_interface *intf)
{
	struct dvb_usb_device *d = usb_get_intfdata(intf);
	const char *default_name = "generic DVB-USB module";
	char name[40];

	usb_set_intfdata(intf, NULL);
	if (d != NULL && d->desc != NULL) {
		strscpy(name, d->desc->name, sizeof(name));
		dvb_usb_exit(d);
	} else {
		strscpy(name, default_name, sizeof(name));
	}
	info("%s successfully deinitialized and disconnected.", name);

}
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
struct module {int dummy; } ;
struct dvb_usb_device_properties {int /*<<< orphan*/  no_reconnect; } ;
struct dvb_usb_device_description {int /*<<< orphan*/  name; } ;
struct dvb_usb_device {struct module* owner; struct dvb_usb_device_description* desc; int /*<<< orphan*/  props; struct usb_device* udev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  deb_err (char*) ; 
 int dvb_usb_download_firmware (struct usb_device*,struct dvb_usb_device_properties*) ; 
 struct dvb_usb_device_description* dvb_usb_find_device (struct usb_device*,struct dvb_usb_device_properties*,int*) ; 
 int dvb_usb_init (struct dvb_usb_device*,short*) ; 
 int /*<<< orphan*/  err (char*) ; 
 int /*<<< orphan*/  info (char*,int /*<<< orphan*/ ,...) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 struct dvb_usb_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct dvb_usb_device_properties*,int) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct dvb_usb_device*) ; 

int dvb_usb_device_init(struct usb_interface *intf,
			struct dvb_usb_device_properties *props,
			struct module *owner, struct dvb_usb_device **du,
			short *adapter_nums)
{
	struct usb_device *udev = interface_to_usbdev(intf);
	struct dvb_usb_device *d = NULL;
	struct dvb_usb_device_description *desc = NULL;

	int ret = -ENOMEM, cold = 0;

	if (du != NULL)
		*du = NULL;

	if ((desc = dvb_usb_find_device(udev, props, &cold)) == NULL) {
		deb_err("something went very wrong, device was not found in current device list - let's see what comes next.\n");
		return -ENODEV;
	}

	if (cold) {
		info("found a '%s' in cold state, will try to load a firmware", desc->name);
		ret = dvb_usb_download_firmware(udev, props);
		if (!props->no_reconnect || ret != 0)
			return ret;
	}

	info("found a '%s' in warm state.", desc->name);
	d = kzalloc(sizeof(struct dvb_usb_device), GFP_KERNEL);
	if (d == NULL) {
		err("no memory for 'struct dvb_usb_device'");
		return -ENOMEM;
	}

	d->udev = udev;
	memcpy(&d->props, props, sizeof(struct dvb_usb_device_properties));
	d->desc = desc;
	d->owner = owner;

	usb_set_intfdata(intf, d);

	if (du != NULL)
		*du = d;

	ret = dvb_usb_init(d, adapter_nums);

	if (ret == 0)
		info("%s successfully initialized and connected.", desc->name);
	else
		info("%s error while loading driver (%d)", desc->name, ret);
	return ret;
}
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
struct usb_device_id {int dummy; } ;
struct usb_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  index; int /*<<< orphan*/  value; scalar_t__ request; } ;

/* Variables and functions */
 int /*<<< orphan*/  DTV5100_USB_TIMEOUT ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int USB_DIR_OUT ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  adapter_nr ; 
 TYPE_1__* dtv5100_init ; 
 int /*<<< orphan*/  dtv5100_properties ; 
 int dvb_usb_device_init (struct usb_interface*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dtv5100_probe(struct usb_interface *intf,
			 const struct usb_device_id *id)
{
	int i, ret;
	struct usb_device *udev = interface_to_usbdev(intf);

	/* initialize non qt1010/zl10353 part? */
	for (i = 0; dtv5100_init[i].request; i++) {
		ret = usb_control_msg(udev, usb_rcvctrlpipe(udev, 0),
				      dtv5100_init[i].request,
				      USB_TYPE_VENDOR | USB_DIR_OUT,
				      dtv5100_init[i].value,
				      dtv5100_init[i].index, NULL, 0,
				      DTV5100_USB_TIMEOUT);
		if (ret)
			return ret;
	}

	ret = dvb_usb_device_init(intf, &dtv5100_properties,
				  THIS_MODULE, NULL, adapter_nr);
	if (ret)
		return ret;

	return 0;
}
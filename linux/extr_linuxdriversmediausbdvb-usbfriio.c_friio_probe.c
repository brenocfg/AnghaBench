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
struct usb_interface {scalar_t__ num_altsetting; } ;
struct TYPE_2__ {int /*<<< orphan*/  bAlternateSetting; int /*<<< orphan*/  bInterfaceNumber; } ;
struct usb_host_interface {TYPE_1__ desc; } ;
struct usb_device_id {int dummy; } ;
struct dvb_usb_device {int /*<<< orphan*/ * adapter; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  FRIIO_BULK_ALTSETTING ; 
 scalar_t__ GL861_ALTSETTING_COUNT ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  adapter_nr ; 
 int /*<<< orphan*/  deb_rc (char*) ; 
 int dvb_usb_device_init (struct usb_interface*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct dvb_usb_device**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  friio_properties ; 
 int /*<<< orphan*/  friio_streaming_ctrl (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  interface_to_usbdev (struct usb_interface*) ; 
 struct usb_host_interface* usb_altnum_to_altsetting (struct usb_interface*,int /*<<< orphan*/ ) ; 
 int usb_set_interface (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int friio_probe(struct usb_interface *intf,
		       const struct usb_device_id *id)
{
	struct dvb_usb_device *d;
	struct usb_host_interface *alt;
	int ret;

	if (intf->num_altsetting < GL861_ALTSETTING_COUNT)
		return -ENODEV;

	alt = usb_altnum_to_altsetting(intf, FRIIO_BULK_ALTSETTING);
	if (alt == NULL) {
		deb_rc("not alt found!\n");
		return -ENODEV;
	}
	ret = usb_set_interface(interface_to_usbdev(intf),
				alt->desc.bInterfaceNumber,
				alt->desc.bAlternateSetting);
	if (ret != 0) {
		deb_rc("failed to set alt-setting!\n");
		return ret;
	}

	ret = dvb_usb_device_init(intf, &friio_properties,
				  THIS_MODULE, &d, adapter_nr);
	if (ret == 0)
		friio_streaming_ctrl(&d->adapter[0], 1);

	return ret;
}
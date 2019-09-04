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
struct TYPE_2__ {int /*<<< orphan*/  idVendor; int /*<<< orphan*/  idProduct; } ;
struct usb_device {TYPE_1__ descriptor; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 scalar_t__ USB_PID_OPERA1_WARM ; 
 scalar_t__ USB_VID_OPERA1 ; 
 int /*<<< orphan*/  adapter_nr ; 
 scalar_t__ dvb_usb_device_init (struct usb_interface*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opera1_properties ; 
 scalar_t__ opera1_xilinx_load_firmware (struct usb_device*,char*) ; 

__attribute__((used)) static int opera1_probe(struct usb_interface *intf,
			const struct usb_device_id *id)
{
	struct usb_device *udev = interface_to_usbdev(intf);

	if (le16_to_cpu(udev->descriptor.idProduct) == USB_PID_OPERA1_WARM &&
	    le16_to_cpu(udev->descriptor.idVendor) == USB_VID_OPERA1 &&
		opera1_xilinx_load_firmware(udev, "dvb-usb-opera1-fpga-01.fw") != 0
	    ) {
		return -EINVAL;
	}

	if (0 != dvb_usb_device_init(intf, &opera1_properties,
				     THIS_MODULE, NULL, adapter_nr))
		return -EINVAL;
	return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {TYPE_2__* altsetting; } ;
struct usb_device {int dummy; } ;
struct uas_dev_info {int shutdown; } ;
struct device {int dummy; } ;
struct Scsi_Host {scalar_t__ hostdata; } ;
struct TYPE_3__ {int /*<<< orphan*/  bInterfaceNumber; } ;
struct TYPE_4__ {TYPE_1__ desc; } ;

/* Variables and functions */
 scalar_t__ SYSTEM_RESTART ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 scalar_t__ system_state ; 
 struct usb_interface* to_usb_interface (struct device*) ; 
 int /*<<< orphan*/  uas_free_streams (struct uas_dev_info*) ; 
 struct Scsi_Host* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_reset_device (struct usb_device*) ; 
 int /*<<< orphan*/  usb_set_interface (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void uas_shutdown(struct device *dev)
{
	struct usb_interface *intf = to_usb_interface(dev);
	struct usb_device *udev = interface_to_usbdev(intf);
	struct Scsi_Host *shost = usb_get_intfdata(intf);
	struct uas_dev_info *devinfo = (struct uas_dev_info *)shost->hostdata;

	if (system_state != SYSTEM_RESTART)
		return;

	devinfo->shutdown = 1;
	uas_free_streams(devinfo);
	usb_set_interface(udev, intf->altsetting[0].desc.bInterfaceNumber, 0);
	usb_reset_device(udev);
}
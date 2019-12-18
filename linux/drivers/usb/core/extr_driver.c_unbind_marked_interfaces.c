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
struct TYPE_4__ {scalar_t__ driver; } ;
struct usb_interface {scalar_t__ needs_binding; TYPE_2__ dev; } ;
struct TYPE_3__ {int bNumInterfaces; } ;
struct usb_host_config {struct usb_interface** interface; TYPE_1__ desc; } ;
struct usb_device {struct usb_host_config* actconfig; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb_forced_unbind_intf (struct usb_interface*) ; 

__attribute__((used)) static void unbind_marked_interfaces(struct usb_device *udev)
{
	struct usb_host_config	*config;
	int			i;
	struct usb_interface	*intf;

	config = udev->actconfig;
	if (config) {
		for (i = 0; i < config->desc.bNumInterfaces; ++i) {
			intf = config->interface[i];
			if (intf->dev.driver && intf->needs_binding)
				usb_forced_unbind_intf(intf);
		}
	}
}
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
struct usb_interface_cache {scalar_t__ num_altsetting; struct usb_host_interface* altsetting; } ;
struct usb_host_interface {int dummy; } ;
struct TYPE_3__ {unsigned int bNumInterfaces; } ;
struct usb_host_config {struct usb_interface_cache** intf_cache; TYPE_1__ desc; } ;
struct usb_device_id {int dummy; } ;
struct TYPE_4__ {unsigned int bNumConfigurations; } ;
struct usb_device {struct usb_host_config* config; TYPE_2__ descriptor; } ;

/* Variables and functions */
 scalar_t__ usb_match_one_id_intf (struct usb_device*,struct usb_host_interface*,struct usb_device_id const*) ; 

__attribute__((used)) static bool usb_match_any_interface(struct usb_device *udev,
				    const struct usb_device_id *id)
{
	unsigned int i;

	for (i = 0; i < udev->descriptor.bNumConfigurations; ++i) {
		struct usb_host_config *cfg = &udev->config[i];
		unsigned int j;

		for (j = 0; j < cfg->desc.bNumInterfaces; ++j) {
			struct usb_interface_cache *cache;
			struct usb_host_interface *intf;

			cache = cfg->intf_cache[j];
			if (cache->num_altsetting == 0)
				continue;

			intf = &cache->altsetting[0];
			if (usb_match_one_id_intf(udev, intf, id))
				return true;
		}
	}

	return false;
}
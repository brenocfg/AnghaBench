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
struct TYPE_4__ {int usage_page; } ;
struct TYPE_3__ {int usage_index; scalar_t__* usage; } ;
struct hid_parser {int /*<<< orphan*/  scan_flags; TYPE_2__ global; TYPE_1__ local; struct hid_device* device; } ;
struct hid_device {scalar_t__ group; scalar_t__ vendor; scalar_t__ product; } ;

/* Variables and functions */
 unsigned int HID_COLLECTION_PHYSICAL ; 
 scalar_t__ HID_GD_POINTER ; 
 scalar_t__ HID_GROUP_GENERIC ; 
 scalar_t__ HID_GROUP_MULTITOUCH ; 
 scalar_t__ HID_GROUP_SENSOR_HUB ; 
 int /*<<< orphan*/  HID_SCAN_FLAG_GD_POINTER ; 
 int /*<<< orphan*/  HID_SCAN_FLAG_VENDOR_SPECIFIC ; 
 int HID_UP_GENDESK ; 
 int HID_UP_MSVENDOR ; 
 int HID_UP_SENSOR ; 
 scalar_t__ USB_DEVICE_ID_MS_POWER_COVER ; 
 scalar_t__ USB_VENDOR_ID_MICROSOFT ; 

__attribute__((used)) static void hid_scan_collection(struct hid_parser *parser, unsigned type)
{
	struct hid_device *hid = parser->device;
	int i;

	if (((parser->global.usage_page << 16) == HID_UP_SENSOR) &&
	    type == HID_COLLECTION_PHYSICAL)
		hid->group = HID_GROUP_SENSOR_HUB;

	if (hid->vendor == USB_VENDOR_ID_MICROSOFT &&
	    hid->product == USB_DEVICE_ID_MS_POWER_COVER &&
	    hid->group == HID_GROUP_MULTITOUCH)
		hid->group = HID_GROUP_GENERIC;

	if ((parser->global.usage_page << 16) == HID_UP_GENDESK)
		for (i = 0; i < parser->local.usage_index; i++)
			if (parser->local.usage[i] == HID_GD_POINTER)
				parser->scan_flags |= HID_SCAN_FLAG_GD_POINTER;

	if ((parser->global.usage_page << 16) >= HID_UP_MSVENDOR)
		parser->scan_flags |= HID_SCAN_FLAG_VENDOR_SPECIFIC;
}
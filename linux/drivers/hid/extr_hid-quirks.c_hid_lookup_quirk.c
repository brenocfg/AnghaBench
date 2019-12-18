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
struct hid_device_id {unsigned long driver_data; } ;
struct hid_device {scalar_t__ bus; scalar_t__ vendor; int product; int version; } ;

/* Variables and functions */
 scalar_t__ BUS_USB ; 
 unsigned long HID_QUIRK_IGNORE ; 
 unsigned long HID_QUIRK_NO_INIT_REPORTS ; 
#define  USB_DEVICE_ID_JABRA_SPEAK_410 129 
#define  USB_DEVICE_ID_JABRA_SPEAK_510 128 
 int USB_DEVICE_ID_NCR_FIRST ; 
 int USB_DEVICE_ID_NCR_LAST ; 
 scalar_t__ USB_VENDOR_ID_JABRA ; 
 scalar_t__ USB_VENDOR_ID_NCR ; 
 int /*<<< orphan*/  dquirks_lock ; 
 struct hid_device_id* hid_exists_dquirk (struct hid_device const*) ; 
 unsigned long hid_gets_squirk (struct hid_device const*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

unsigned long hid_lookup_quirk(const struct hid_device *hdev)
{
	unsigned long quirks = 0;
	const struct hid_device_id *quirk_entry = NULL;

	/* NCR devices must not be queried for reports */
	if (hdev->bus == BUS_USB &&
	    hdev->vendor == USB_VENDOR_ID_NCR &&
	    hdev->product >= USB_DEVICE_ID_NCR_FIRST &&
	    hdev->product <= USB_DEVICE_ID_NCR_LAST)
		return HID_QUIRK_NO_INIT_REPORTS;

	/* These devices must be ignored if version (bcdDevice) is too old */
	if (hdev->bus == BUS_USB && hdev->vendor == USB_VENDOR_ID_JABRA) {
		switch (hdev->product) {
		case USB_DEVICE_ID_JABRA_SPEAK_410:
			if (hdev->version < 0x0111)
				return HID_QUIRK_IGNORE;
			break;
		case USB_DEVICE_ID_JABRA_SPEAK_510:
			if (hdev->version < 0x0214)
				return HID_QUIRK_IGNORE;
			break;
		}
	}

	mutex_lock(&dquirks_lock);
	quirk_entry = hid_exists_dquirk(hdev);
	if (quirk_entry)
		quirks = quirk_entry->driver_data;
	else
		quirks = hid_gets_squirk(hdev);
	mutex_unlock(&dquirks_lock);

	return quirks;
}
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
struct hid_device {int quirks; int vendor; int product; scalar_t__ type; int /*<<< orphan*/  name; int /*<<< orphan*/  bus; } ;
struct TYPE_2__ {char* id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_USB ; 
 int HID_QUIRK_IGNORE ; 
 int HID_QUIRK_NO_IGNORE ; 
 scalar_t__ HID_TYPE_USBMOUSE ; 
 scalar_t__ HID_TYPE_USBNONE ; 
 int USB_DEVICE_ID_ATMEL_V_USB ; 
 int USB_DEVICE_ID_CODEMERCS_IOW_FIRST ; 
 int USB_DEVICE_ID_CODEMERCS_IOW_LAST ; 
 int USB_DEVICE_ID_HANWANG_TABLET_FIRST ; 
 int USB_DEVICE_ID_HANWANG_TABLET_LAST ; 
 int USB_DEVICE_ID_JESS_YUREX ; 
 int USB_DEVICE_ID_LOGITECH_AUDIOHUB ; 
 int USB_DEVICE_ID_LOGITECH_HARMONY_FIRST ; 
 int USB_DEVICE_ID_LOGITECH_HARMONY_LAST ; 
 int USB_DEVICE_ID_SOUNDGRAPH_IMON_FIRST ; 
 int USB_DEVICE_ID_SOUNDGRAPH_IMON_LAST ; 
 int USB_DEVICE_ID_VELLEMAN_K8055_FIRST ; 
 int USB_DEVICE_ID_VELLEMAN_K8055_LAST ; 
 int USB_DEVICE_ID_VELLEMAN_K8061_FIRST ; 
 int USB_DEVICE_ID_VELLEMAN_K8061_LAST ; 
#define  USB_VENDOR_ID_ATMEL_V_USB 135 
#define  USB_VENDOR_ID_CODEMERCS 134 
#define  USB_VENDOR_ID_ELAN 133 
#define  USB_VENDOR_ID_HANWANG 132 
#define  USB_VENDOR_ID_JESS 131 
#define  USB_VENDOR_ID_LOGITECH 130 
#define  USB_VENDOR_ID_SOUNDGRAPH 129 
#define  USB_VENDOR_ID_VELLEMAN 128 
 TYPE_1__* elan_acpi_id ; 
 int /*<<< orphan*/  hid_ignore_list ; 
 scalar_t__ hid_match_id (struct hid_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hid_mouse_ignore_list ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char*,int) ; 

bool hid_ignore(struct hid_device *hdev)
{
	int i;

	if (hdev->quirks & HID_QUIRK_NO_IGNORE)
		return false;
	if (hdev->quirks & HID_QUIRK_IGNORE)
		return true;

	switch (hdev->vendor) {
	case USB_VENDOR_ID_CODEMERCS:
		/* ignore all Code Mercenaries IOWarrior devices */
		if (hdev->product >= USB_DEVICE_ID_CODEMERCS_IOW_FIRST &&
		    hdev->product <= USB_DEVICE_ID_CODEMERCS_IOW_LAST)
			return true;
		break;
	case USB_VENDOR_ID_LOGITECH:
		if (hdev->product >= USB_DEVICE_ID_LOGITECH_HARMONY_FIRST &&
		    hdev->product <= USB_DEVICE_ID_LOGITECH_HARMONY_LAST)
			return true;
		/*
		 * The Keene FM transmitter USB device has the same USB ID as
		 * the Logitech AudioHub Speaker, but it should ignore the hid.
		 * Check if the name is that of the Keene device.
		 * For reference: the name of the AudioHub is
		 * "HOLTEK  AudioHub Speaker".
		 */
		if (hdev->product == USB_DEVICE_ID_LOGITECH_AUDIOHUB &&
		    !strcmp(hdev->name, "HOLTEK  B-LINK USB Audio  "))
			return true;
		break;
	case USB_VENDOR_ID_SOUNDGRAPH:
		if (hdev->product >= USB_DEVICE_ID_SOUNDGRAPH_IMON_FIRST &&
		    hdev->product <= USB_DEVICE_ID_SOUNDGRAPH_IMON_LAST)
			return true;
		break;
	case USB_VENDOR_ID_HANWANG:
		if (hdev->product >= USB_DEVICE_ID_HANWANG_TABLET_FIRST &&
		    hdev->product <= USB_DEVICE_ID_HANWANG_TABLET_LAST)
			return true;
		break;
	case USB_VENDOR_ID_JESS:
		if (hdev->product == USB_DEVICE_ID_JESS_YUREX &&
		    hdev->type == HID_TYPE_USBNONE)
			return true;
		break;
	case USB_VENDOR_ID_VELLEMAN:
		/* These are not HID devices.  They are handled by comedi. */
		if ((hdev->product >= USB_DEVICE_ID_VELLEMAN_K8055_FIRST &&
		     hdev->product <= USB_DEVICE_ID_VELLEMAN_K8055_LAST) ||
		    (hdev->product >= USB_DEVICE_ID_VELLEMAN_K8061_FIRST &&
		     hdev->product <= USB_DEVICE_ID_VELLEMAN_K8061_LAST))
			return true;
		break;
	case USB_VENDOR_ID_ATMEL_V_USB:
		/* Masterkit MA901 usb radio based on Atmel tiny85 chip and
		 * it has the same USB ID as many Atmel V-USB devices. This
		 * usb radio is handled by radio-ma901.c driver so we want
		 * ignore the hid. Check the name, bus, product and ignore
		 * if we have MA901 usb radio.
		 */
		if (hdev->product == USB_DEVICE_ID_ATMEL_V_USB &&
		    hdev->bus == BUS_USB &&
		    strncmp(hdev->name, "www.masterkit.ru MA901", 22) == 0)
			return true;
		break;
	case USB_VENDOR_ID_ELAN:
		/*
		 * Blacklist of everything that gets handled by the elan_i2c
		 * input driver.  This avoids disabling valid touchpads and
		 * other ELAN devices.
		 */
		if ((hdev->product == 0x0401 || hdev->product == 0x0400))
			for (i = 0; strlen(elan_acpi_id[i].id); ++i)
				if (!strncmp(hdev->name, elan_acpi_id[i].id,
					     strlen(elan_acpi_id[i].id)))
					return true;
		break;
	}

	if (hdev->type == HID_TYPE_USBMOUSE &&
	    hid_match_id(hdev, hid_mouse_ignore_list))
		return true;

	return !!hid_match_id(hdev, hid_ignore_list);
}
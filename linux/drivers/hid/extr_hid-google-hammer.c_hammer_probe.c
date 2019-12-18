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
struct hid_device_id {int dummy; } ;
struct hid_device {scalar_t__ product; int /*<<< orphan*/  quirks; } ;

/* Variables and functions */
 int /*<<< orphan*/  HID_CONNECT_DEFAULT ; 
 int /*<<< orphan*/  HID_QUIRK_ALWAYS_POLL ; 
 scalar_t__ USB_DEVICE_ID_GOOGLE_WHISKERS ; 
 scalar_t__ hammer_has_backlight_control (struct hid_device*) ; 
 scalar_t__ hammer_is_keyboard_interface (struct hid_device*) ; 
 int hammer_register_leds (struct hid_device*) ; 
 int hid_hw_start (struct hid_device*,int /*<<< orphan*/ ) ; 
 int hid_parse (struct hid_device*) ; 
 int /*<<< orphan*/  hid_warn (struct hid_device*,char*,int) ; 

__attribute__((used)) static int hammer_probe(struct hid_device *hdev,
			const struct hid_device_id *id)
{
	int error;

	/*
	 * We always want to poll for, and handle tablet mode events from
	 * Whiskers, even when nobody has opened the input device. This also
	 * prevents the hid core from dropping early tablet mode events from
	 * the device.
	 */
	if (hdev->product == USB_DEVICE_ID_GOOGLE_WHISKERS &&
			hammer_is_keyboard_interface(hdev))
		hdev->quirks |= HID_QUIRK_ALWAYS_POLL;

	error = hid_parse(hdev);
	if (error)
		return error;

	error = hid_hw_start(hdev, HID_CONNECT_DEFAULT);
	if (error)
		return error;

	if (hammer_has_backlight_control(hdev)) {
		error = hammer_register_leds(hdev);
		if (error)
			hid_warn(hdev,
				"Failed to register keyboard backlight: %d\n",
				error);
	}

	return 0;
}
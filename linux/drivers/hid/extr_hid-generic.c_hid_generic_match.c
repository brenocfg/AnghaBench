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
struct hid_device {int quirks; } ;

/* Variables and functions */
 int HID_QUIRK_HAVE_SPECIAL_DRIVER ; 
 int /*<<< orphan*/  __check_hid_generic ; 
 scalar_t__ bus_for_each_drv (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct hid_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hid_bus_type ; 

__attribute__((used)) static bool hid_generic_match(struct hid_device *hdev,
			      bool ignore_special_driver)
{
	if (ignore_special_driver)
		return true;

	if (hdev->quirks & HID_QUIRK_HAVE_SPECIAL_DRIVER)
		return false;

	/*
	 * If any other driver wants the device, leave the device to this other
	 * driver.
	 */
	if (bus_for_each_drv(&hid_bus_type, NULL, hdev, __check_hid_generic))
		return false;

	return true;
}
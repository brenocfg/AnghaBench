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
struct hid_device {int /*<<< orphan*/  product; int /*<<< orphan*/  vendor; } ;

/* Variables and functions */
 unsigned long HID_QUIRK_HAVE_SPECIAL_DRIVER ; 
 unsigned long HID_QUIRK_IGNORE ; 
 int /*<<< orphan*/  dbg_hid (char*,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hid_have_special_driver ; 
 int /*<<< orphan*/  hid_ignore_list ; 
 struct hid_device_id* hid_match_id (struct hid_device const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hid_quirks ; 

__attribute__((used)) static unsigned long hid_gets_squirk(const struct hid_device *hdev)
{
	const struct hid_device_id *bl_entry;
	unsigned long quirks = 0;

	if (hid_match_id(hdev, hid_ignore_list))
		quirks |= HID_QUIRK_IGNORE;

	if (hid_match_id(hdev, hid_have_special_driver))
		quirks |= HID_QUIRK_HAVE_SPECIAL_DRIVER;

	bl_entry = hid_match_id(hdev, hid_quirks);
	if (bl_entry != NULL)
		quirks |= bl_entry->driver_data;

	if (quirks)
		dbg_hid("Found squirk 0x%lx for HID device 0x%04x:0x%04x\n",
			quirks, hdev->vendor, hdev->product);
	return quirks;
}
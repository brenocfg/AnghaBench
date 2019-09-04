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
struct hid_device {int /*<<< orphan*/  quirks; } ;

/* Variables and functions */
 int /*<<< orphan*/  HID_CONNECT_DEFAULT ; 
 int /*<<< orphan*/  HID_QUIRK_INPUT_PER_APP ; 
 int hid_hw_start (struct hid_device*,int /*<<< orphan*/ ) ; 
 int hid_parse (struct hid_device*) ; 

__attribute__((used)) static int hid_generic_probe(struct hid_device *hdev,
			     const struct hid_device_id *id)
{
	int ret;

	hdev->quirks |= HID_QUIRK_INPUT_PER_APP;

	ret = hid_parse(hdev);
	if (ret)
		return ret;

	return hid_hw_start(hdev, HID_CONNECT_DEFAULT);
}
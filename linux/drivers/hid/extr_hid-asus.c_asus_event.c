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
struct hid_usage {int hid; int /*<<< orphan*/  type; } ;
struct hid_field {int dummy; } ;
struct hid_device {int dummy; } ;
typedef  int /*<<< orphan*/  __s32 ;

/* Variables and functions */
 int HID_USAGE ; 
 int HID_USAGE_PAGE ; 
 int /*<<< orphan*/  hid_warn (struct hid_device*,char*,int) ; 

__attribute__((used)) static int asus_event(struct hid_device *hdev, struct hid_field *field,
		      struct hid_usage *usage, __s32 value)
{
	if ((usage->hid & HID_USAGE_PAGE) == 0xff310000 &&
	    (usage->hid & HID_USAGE) != 0x00 && !usage->type) {
		hid_warn(hdev, "Unmapped Asus vendor usagepage code 0x%02x\n",
			 usage->hid & HID_USAGE);
	}

	return 0;
}
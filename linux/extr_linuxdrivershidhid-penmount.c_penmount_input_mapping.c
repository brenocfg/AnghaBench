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
struct hid_usage {int hid; } ;
struct hid_input {int dummy; } ;
struct hid_field {int dummy; } ;
struct hid_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTN_TOUCH ; 
 int /*<<< orphan*/  EV_KEY ; 
 int HID_UP_BUTTON ; 
 int HID_USAGE ; 
 int HID_USAGE_PAGE ; 
 int /*<<< orphan*/  hid_map_usage (struct hid_input*,struct hid_usage*,unsigned long**,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int penmount_input_mapping(struct hid_device *hdev,
		struct hid_input *hi, struct hid_field *field,
		struct hid_usage *usage, unsigned long **bit, int *max)
{
	if ((usage->hid & HID_USAGE_PAGE) == HID_UP_BUTTON) {
		if (((usage->hid - 1) & HID_USAGE) == 0) {
			hid_map_usage(hi, usage, bit, max, EV_KEY, BTN_TOUCH);
			return 1;
		} else {
			return -1;
		}
	}

	return 0;
}
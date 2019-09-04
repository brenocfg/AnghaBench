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
struct input_keymap_entry {unsigned int index; int len; int /*<<< orphan*/  scancode; int /*<<< orphan*/  keycode; } ;
struct input_dev {int dummy; } ;
struct hid_usage {scalar_t__ type; unsigned int hid; int /*<<< orphan*/  code; } ;
struct hid_device {int dummy; } ;
typedef  int /*<<< orphan*/  scancode ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ EV_KEY ; 
 unsigned int HID_USAGE ; 
 unsigned int HID_USAGE_PAGE ; 
 int /*<<< orphan*/  KEY_RESERVED ; 
 struct hid_usage* hidinput_locate_usage (struct hid_device*,struct input_keymap_entry*,unsigned int*) ; 
 struct hid_device* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned int*,int) ; 

__attribute__((used)) static int hidinput_getkeycode(struct input_dev *dev,
			       struct input_keymap_entry *ke)
{
	struct hid_device *hid = input_get_drvdata(dev);
	struct hid_usage *usage;
	unsigned int scancode, index;

	usage = hidinput_locate_usage(hid, ke, &index);
	if (usage) {
		ke->keycode = usage->type == EV_KEY ?
				usage->code : KEY_RESERVED;
		ke->index = index;
		scancode = usage->hid & (HID_USAGE_PAGE | HID_USAGE);
		ke->len = sizeof(scancode);
		memcpy(ke->scancode, &scancode, sizeof(scancode));
		return 0;
	}

	return -EINVAL;
}
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
struct input_keymap_entry {unsigned int keycode; } ;
struct input_dev {int /*<<< orphan*/  keybit; } ;
struct hid_usage {scalar_t__ type; unsigned int code; int /*<<< orphan*/  hid; } ;
struct hid_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ EV_KEY ; 
 unsigned int KEY_RESERVED ; 
 int /*<<< orphan*/  clear_bit (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbg_hid (char*,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ hidinput_find_key (struct hid_device*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *) ; 
 struct hid_usage* hidinput_locate_usage (struct hid_device*,struct input_keymap_entry const*,int /*<<< orphan*/ *) ; 
 struct hid_device* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  match_keycode ; 
 int /*<<< orphan*/  set_bit (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hidinput_setkeycode(struct input_dev *dev,
			       const struct input_keymap_entry *ke,
			       unsigned int *old_keycode)
{
	struct hid_device *hid = input_get_drvdata(dev);
	struct hid_usage *usage;

	usage = hidinput_locate_usage(hid, ke, NULL);
	if (usage) {
		*old_keycode = usage->type == EV_KEY ?
				usage->code : KEY_RESERVED;
		usage->code = ke->keycode;

		clear_bit(*old_keycode, dev->keybit);
		set_bit(usage->code, dev->keybit);
		dbg_hid("Assigned keycode %d to HID usage code %x\n",
			usage->code, usage->hid);

		/*
		 * Set the keybit for the old keycode if the old keycode is used
		 * by another key
		 */
		if (hidinput_find_key(hid, match_keycode, *old_keycode, NULL))
			set_bit(*old_keycode, dev->keybit);

		return 0;
	}

	return -EINVAL;
}
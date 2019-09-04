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
typedef  struct key_entry {unsigned int code; int /*<<< orphan*/  keycode; int /*<<< orphan*/  type; } const key_entry ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KEY_UNKNOWN ; 
 int /*<<< orphan*/  KE_KEY ; 
 struct key_entry const* sparse_keymap_entry_from_scancode (struct input_dev*,unsigned int) ; 
 int /*<<< orphan*/  sparse_keymap_report_entry (struct input_dev*,struct key_entry const*,unsigned int,int) ; 

bool sparse_keymap_report_event(struct input_dev *dev, unsigned int code,
				unsigned int value, bool autorelease)
{
	const struct key_entry *ke =
		sparse_keymap_entry_from_scancode(dev, code);
	struct key_entry unknown_ke;

	if (ke) {
		sparse_keymap_report_entry(dev, ke, value, autorelease);
		return true;
	}

	/* Report an unknown key event as a debugging aid */
	unknown_ke.type = KE_KEY;
	unknown_ke.code = code;
	unknown_ke.keycode = KEY_UNKNOWN;
	sparse_keymap_report_entry(dev, &unknown_ke, value, true);

	return false;
}
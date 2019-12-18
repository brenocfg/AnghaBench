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
struct rc_map_table {unsigned int scancode; scalar_t__ keycode; } ;
struct input_keymap_entry {int flags; unsigned int index; } ;

/* Variables and functions */
 int INPUT_KEYMAP_BY_INDEX ; 
 scalar_t__ KEY_RESERVED ; 
 scalar_t__ KEY_UNKNOWN ; 
 scalar_t__ input_scancode_to_scalar (struct input_keymap_entry const*,unsigned int*) ; 

__attribute__((used)) static unsigned int
legacy_dvb_usb_get_keymap_index(const struct input_keymap_entry *ke,
				struct rc_map_table *keymap,
				unsigned int keymap_size)
{
	unsigned int index;
	unsigned int scancode;

	if (ke->flags & INPUT_KEYMAP_BY_INDEX) {
		index = ke->index;
	} else {
		if (input_scancode_to_scalar(ke, &scancode))
			return keymap_size;

		/* See if we can match the raw key code. */
		for (index = 0; index < keymap_size; index++)
			if (keymap[index].scancode == scancode)
				break;

		/* See if there is an unused hole in the map */
		if (index >= keymap_size) {
			for (index = 0; index < keymap_size; index++) {
				if (keymap[index].keycode == KEY_RESERVED ||
				    keymap[index].keycode == KEY_UNKNOWN) {
					break;
				}
			}
		}
	}

	return index;
}
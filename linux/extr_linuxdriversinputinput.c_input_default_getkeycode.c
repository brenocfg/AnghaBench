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
struct input_keymap_entry {int flags; unsigned int index; int len; int /*<<< orphan*/  scancode; int /*<<< orphan*/  keycode; } ;
struct input_dev {unsigned int keycodemax; int /*<<< orphan*/  keycodesize; } ;
typedef  int /*<<< orphan*/  index ;

/* Variables and functions */
 int EINVAL ; 
 int INPUT_KEYMAP_BY_INDEX ; 
 int /*<<< orphan*/  input_fetch_keycode (struct input_dev*,unsigned int) ; 
 int input_scancode_to_scalar (struct input_keymap_entry*,unsigned int*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned int*,int) ; 

__attribute__((used)) static int input_default_getkeycode(struct input_dev *dev,
				    struct input_keymap_entry *ke)
{
	unsigned int index;
	int error;

	if (!dev->keycodesize)
		return -EINVAL;

	if (ke->flags & INPUT_KEYMAP_BY_INDEX)
		index = ke->index;
	else {
		error = input_scancode_to_scalar(ke, &index);
		if (error)
			return error;
	}

	if (index >= dev->keycodemax)
		return -EINVAL;

	ke->keycode = input_fetch_keycode(dev, index);
	ke->index = index;
	ke->len = sizeof(index);
	memcpy(ke->scancode, &index, sizeof(index));

	return 0;
}
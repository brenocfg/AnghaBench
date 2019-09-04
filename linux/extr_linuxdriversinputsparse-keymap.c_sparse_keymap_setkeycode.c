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
struct key_entry {scalar_t__ type; unsigned int keycode; } ;
struct input_keymap_entry {unsigned int keycode; } ;
struct input_dev {int /*<<< orphan*/  keybit; scalar_t__ keycode; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ KE_KEY ; 
 int /*<<< orphan*/  clear_bit (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sparse_keymap_entry_from_keycode (struct input_dev*,unsigned int) ; 
 struct key_entry* sparse_keymap_locate (struct input_dev*,struct input_keymap_entry const*) ; 

__attribute__((used)) static int sparse_keymap_setkeycode(struct input_dev *dev,
				    const struct input_keymap_entry *ke,
				    unsigned int *old_keycode)
{
	struct key_entry *key;

	if (dev->keycode) {
		key = sparse_keymap_locate(dev, ke);
		if (key && key->type == KE_KEY) {
			*old_keycode = key->keycode;
			key->keycode = ke->keycode;
			set_bit(ke->keycode, dev->keybit);
			if (!sparse_keymap_entry_from_keycode(dev, *old_keycode))
				clear_bit(*old_keycode, dev->keybit);
			return 0;
		}
	}

	return -EINVAL;
}
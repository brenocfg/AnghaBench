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
struct key_entry {int dummy; } ;
struct input_keymap_entry {int flags; int /*<<< orphan*/  index; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int INPUT_KEYMAP_BY_INDEX ; 
 scalar_t__ input_scancode_to_scalar (struct input_keymap_entry const*,unsigned int*) ; 
 struct key_entry* sparse_keymap_entry_by_index (struct input_dev*,int /*<<< orphan*/ ) ; 
 struct key_entry* sparse_keymap_entry_from_scancode (struct input_dev*,unsigned int) ; 

__attribute__((used)) static struct key_entry *sparse_keymap_locate(struct input_dev *dev,
					const struct input_keymap_entry *ke)
{
	struct key_entry *key;
	unsigned int scancode;

	if (ke->flags & INPUT_KEYMAP_BY_INDEX)
		key = sparse_keymap_entry_by_index(dev, ke->index);
	else if (input_scancode_to_scalar(ke, &scancode) == 0)
		key = sparse_keymap_entry_from_scancode(dev, scancode);
	else
		key = NULL;

	return key;
}
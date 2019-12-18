#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  code; } ;
struct key_entry {scalar_t__ type; TYPE_1__ sw; int /*<<< orphan*/  keycode; } ;
struct input_dev {size_t keycodemax; int /*<<< orphan*/  setkeycode; int /*<<< orphan*/  getkeycode; struct key_entry* keycode; int /*<<< orphan*/  mscbit; int /*<<< orphan*/  evbit; int /*<<< orphan*/  keybit; int /*<<< orphan*/  swbit; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  EV_MSC ; 
 int /*<<< orphan*/  EV_SW ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KEY_UNKNOWN ; 
 scalar_t__ KE_END ; 
#define  KE_KEY 130 
#define  KE_SW 129 
#define  KE_VSW 128 
 int /*<<< orphan*/  MSC_SCAN ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct key_entry* devm_kmemdup (int /*<<< orphan*/ *,struct key_entry const*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sparse_keymap_getkeycode ; 
 int /*<<< orphan*/  sparse_keymap_setkeycode ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int sparse_keymap_setup(struct input_dev *dev,
			const struct key_entry *keymap,
			int (*setup)(struct input_dev *, struct key_entry *))
{
	size_t map_size = 1; /* to account for the last KE_END entry */
	const struct key_entry *e;
	struct key_entry *map, *entry;
	int i;
	int error;

	for (e = keymap; e->type != KE_END; e++)
		map_size++;

	map = devm_kmemdup(&dev->dev, keymap, map_size * sizeof(*map),
			   GFP_KERNEL);
	if (!map)
		return -ENOMEM;

	for (i = 0; i < map_size; i++) {
		entry = &map[i];

		if (setup) {
			error = setup(dev, entry);
			if (error)
				return error;
		}

		switch (entry->type) {
		case KE_KEY:
			__set_bit(EV_KEY, dev->evbit);
			__set_bit(entry->keycode, dev->keybit);
			break;

		case KE_SW:
		case KE_VSW:
			__set_bit(EV_SW, dev->evbit);
			__set_bit(entry->sw.code, dev->swbit);
			break;
		}
	}

	if (test_bit(EV_KEY, dev->evbit)) {
		__set_bit(KEY_UNKNOWN, dev->keybit);
		__set_bit(EV_MSC, dev->evbit);
		__set_bit(MSC_SCAN, dev->mscbit);
	}

	dev->keycode = map;
	dev->keycodemax = map_size;
	dev->getkeycode = sparse_keymap_getkeycode;
	dev->setkeycode = sparse_keymap_setkeycode;

	return 0;
}
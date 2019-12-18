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
struct matrix_keymap_data {int keymap_size; unsigned int* keymap; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct input_dev {unsigned short* keycode; int keycodesize; size_t keycodemax; int /*<<< orphan*/  keybit; int /*<<< orphan*/  evbit; TYPE_1__ dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KEY_RESERVED ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 unsigned short* devm_kcalloc (int /*<<< orphan*/ ,size_t,int,int /*<<< orphan*/ ) ; 
 unsigned int get_count_order (unsigned int) ; 
 int /*<<< orphan*/  matrix_keypad_map_key (struct input_dev*,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 int matrix_keypad_parse_keymap (char const*,unsigned int,unsigned int,struct input_dev*) ; 

int matrix_keypad_build_keymap(const struct matrix_keymap_data *keymap_data,
			       const char *keymap_name,
			       unsigned int rows, unsigned int cols,
			       unsigned short *keymap,
			       struct input_dev *input_dev)
{
	unsigned int row_shift = get_count_order(cols);
	size_t max_keys = rows << row_shift;
	int i;
	int error;

	if (WARN_ON(!input_dev->dev.parent))
		return -EINVAL;

	if (!keymap) {
		keymap = devm_kcalloc(input_dev->dev.parent,
				      max_keys, sizeof(*keymap),
				      GFP_KERNEL);
		if (!keymap) {
			dev_err(input_dev->dev.parent,
				"Unable to allocate memory for keymap");
			return -ENOMEM;
		}
	}

	input_dev->keycode = keymap;
	input_dev->keycodesize = sizeof(*keymap);
	input_dev->keycodemax = max_keys;

	__set_bit(EV_KEY, input_dev->evbit);

	if (keymap_data) {
		for (i = 0; i < keymap_data->keymap_size; i++) {
			unsigned int key = keymap_data->keymap[i];

			if (!matrix_keypad_map_key(input_dev, rows, cols,
						   row_shift, key))
				return -EINVAL;
		}
	} else {
		error = matrix_keypad_parse_keymap(keymap_name, rows, cols,
						   input_dev);
		if (error)
			return error;
	}

	__clear_bit(KEY_RESERVED, input_dev->keybit);

	return 0;
}
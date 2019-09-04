#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct input_keymap_entry {int flags; unsigned int index; int len; int /*<<< orphan*/  scancode; int /*<<< orphan*/  keycode; } ;
struct input_dev {int dummy; } ;
struct ati_remote2 {int /*<<< orphan*/ ** keycode; } ;
typedef  int /*<<< orphan*/  scancode ;
struct TYPE_3__ {unsigned int hw_code; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 unsigned int ATI_REMOTE2_MODES ; 
 unsigned int ATI_REMOTE2_PC ; 
 int EINVAL ; 
 int INPUT_KEYMAP_BY_INDEX ; 
 TYPE_1__* ati_remote2_key_table ; 
 int ati_remote2_lookup (unsigned int) ; 
 struct ati_remote2* input_get_drvdata (struct input_dev*) ; 
 scalar_t__ input_scancode_to_scalar (struct input_keymap_entry*,unsigned int*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,unsigned int*,int) ; 

__attribute__((used)) static int ati_remote2_getkeycode(struct input_dev *idev,
				  struct input_keymap_entry *ke)
{
	struct ati_remote2 *ar2 = input_get_drvdata(idev);
	unsigned int mode;
	int offset;
	unsigned int index;
	unsigned int scancode;

	if (ke->flags & INPUT_KEYMAP_BY_INDEX) {
		index = ke->index;
		if (index >= ATI_REMOTE2_MODES *
				ARRAY_SIZE(ati_remote2_key_table))
			return -EINVAL;

		mode = ke->index / ARRAY_SIZE(ati_remote2_key_table);
		offset = ke->index % ARRAY_SIZE(ati_remote2_key_table);
		scancode = (mode << 8) + ati_remote2_key_table[offset].hw_code;
	} else {
		if (input_scancode_to_scalar(ke, &scancode))
			return -EINVAL;

		mode = scancode >> 8;
		if (mode > ATI_REMOTE2_PC)
			return -EINVAL;

		offset = ati_remote2_lookup(scancode & 0xff);
		if (offset < 0)
			return -EINVAL;

		index = mode * ARRAY_SIZE(ati_remote2_key_table) + offset;
	}

	ke->keycode = ar2->keycode[mode][offset];
	ke->len = sizeof(scancode);
	memcpy(&ke->scancode, &scancode, sizeof(scancode));
	ke->index = index;

	return 0;
}
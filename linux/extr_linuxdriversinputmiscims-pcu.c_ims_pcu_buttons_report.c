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
typedef  unsigned long u32 ;
struct input_dev {int dummy; } ;
struct ims_pcu_buttons {unsigned short* keymap; struct input_dev* input; } ;
struct ims_pcu {struct ims_pcu_buttons buttons; } ;

/* Variables and functions */
 unsigned short KEY_RESERVED ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,unsigned short,unsigned long) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 

__attribute__((used)) static void ims_pcu_buttons_report(struct ims_pcu *pcu, u32 data)
{
	struct ims_pcu_buttons *buttons = &pcu->buttons;
	struct input_dev *input = buttons->input;
	int i;

	for (i = 0; i < 32; i++) {
		unsigned short keycode = buttons->keymap[i];

		if (keycode != KEY_RESERVED)
			input_report_key(input, keycode, data & (1UL << i));
	}

	input_sync(input);
}
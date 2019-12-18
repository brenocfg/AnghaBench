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
struct input_dev {int keycodesize; int keycodemax; int* evbit; int /*<<< orphan*/  keybit; int /*<<< orphan*/ * keycode; } ;
struct hid_input {struct input_dev* input; } ;
struct hid_device {int dummy; } ;
struct creative_sb0540 {int /*<<< orphan*/ * keymap; struct input_dev* input_dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  EV_REP ; 
 int /*<<< orphan*/  KEY_RESERVED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * creative_sb0540_key_table ; 
 struct creative_sb0540* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int creative_sb0540_input_configured(struct hid_device *hid,
		struct hid_input *hidinput)
{
	struct input_dev *input_dev = hidinput->input;
	struct creative_sb0540 *creative_sb0540 = hid_get_drvdata(hid);
	int i;

	creative_sb0540->input_dev = input_dev;

	input_dev->keycode = creative_sb0540->keymap;
	input_dev->keycodesize = sizeof(unsigned short);
	input_dev->keycodemax = ARRAY_SIZE(creative_sb0540->keymap);

	input_dev->evbit[0] = BIT(EV_KEY) | BIT(EV_REP);

	memcpy(creative_sb0540->keymap, creative_sb0540_key_table,
		sizeof(creative_sb0540->keymap));
	for (i = 0; i < ARRAY_SIZE(creative_sb0540_key_table); i++)
		set_bit(creative_sb0540->keymap[i], input_dev->keybit);
	clear_bit(KEY_RESERVED, input_dev->keybit);

	return 0;
}
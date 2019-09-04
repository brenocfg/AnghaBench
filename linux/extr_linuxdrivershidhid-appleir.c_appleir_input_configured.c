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
struct appleir {int /*<<< orphan*/ * keymap; struct input_dev* input_dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  EV_REP ; 
 int /*<<< orphan*/  KEY_RESERVED ; 
 int /*<<< orphan*/ * appleir_key_table ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct appleir* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int appleir_input_configured(struct hid_device *hid,
		struct hid_input *hidinput)
{
	struct input_dev *input_dev = hidinput->input;
	struct appleir *appleir = hid_get_drvdata(hid);
	int i;

	appleir->input_dev = input_dev;

	input_dev->keycode = appleir->keymap;
	input_dev->keycodesize = sizeof(unsigned short);
	input_dev->keycodemax = ARRAY_SIZE(appleir->keymap);

	input_dev->evbit[0] = BIT(EV_KEY) | BIT(EV_REP);

	memcpy(appleir->keymap, appleir_key_table, sizeof(appleir->keymap));
	for (i = 0; i < ARRAY_SIZE(appleir_key_table); i++)
		set_bit(appleir->keymap[i], input_dev->keybit);
	clear_bit(KEY_RESERVED, input_dev->keybit);

	return 0;
}
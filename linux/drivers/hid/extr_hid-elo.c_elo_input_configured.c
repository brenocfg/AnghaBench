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
struct input_dev {int /*<<< orphan*/  absbit; int /*<<< orphan*/  keybit; } ;
struct hid_input {struct input_dev* input; } ;
struct hid_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_PRESSURE ; 
 int /*<<< orphan*/  BTN_LEFT ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_abs_params (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int elo_input_configured(struct hid_device *hdev,
		struct hid_input *hidinput)
{
	struct input_dev *input = hidinput->input;

	/*
	 * ELO devices have one Button usage in GenDesk field, which makes
	 * hid-input map it to BTN_LEFT; that confuses userspace, which then
	 * considers the device to be a mouse/touchpad instead of touchscreen.
	 */
	clear_bit(BTN_LEFT, input->keybit);
	set_bit(BTN_TOUCH, input->keybit);
	set_bit(ABS_PRESSURE, input->absbit);
	input_set_abs_params(input, ABS_PRESSURE, 0, 256, 0, 0);

	return 0;
}
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
struct tc_keypad {int dummy; } ;
struct input_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct tc_keypad* input_get_drvdata (struct input_dev*) ; 
 int tc3589x_keypad_enable (struct tc_keypad*) ; 
 int tc3589x_keypad_init_key_hardware (struct tc_keypad*) ; 

__attribute__((used)) static int tc3589x_keypad_open(struct input_dev *input)
{
	int error;
	struct tc_keypad *keypad = input_get_drvdata(input);

	/* enable the keypad module */
	error = tc3589x_keypad_enable(keypad);
	if (error < 0) {
		dev_err(&input->dev, "failed to enable keypad module\n");
		return error;
	}

	error = tc3589x_keypad_init_key_hardware(keypad);
	if (error < 0) {
		dev_err(&input->dev, "failed to configure keypad module\n");
		return error;
	}

	return 0;
}
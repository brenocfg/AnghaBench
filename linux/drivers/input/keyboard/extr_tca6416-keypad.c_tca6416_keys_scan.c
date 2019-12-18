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
typedef  int u16 ;
struct tca6416_keypad_chip {int pinmask; int reg_input; struct tca6416_button* buttons; struct input_dev* input; } ;
struct tca6416_button {int type; int active_low; int /*<<< orphan*/  code; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 unsigned int EV_KEY ; 
 int /*<<< orphan*/  TCA6416_INPUT ; 
 int /*<<< orphan*/  input_event (struct input_dev*,unsigned int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 int tca6416_read_reg (struct tca6416_keypad_chip*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void tca6416_keys_scan(struct tca6416_keypad_chip *chip)
{
	struct input_dev *input = chip->input;
	u16 reg_val, val;
	int error, i, pin_index;

	error = tca6416_read_reg(chip, TCA6416_INPUT, &reg_val);
	if (error)
		return;

	reg_val &= chip->pinmask;

	/* Figure out which lines have changed */
	val = reg_val ^ chip->reg_input;
	chip->reg_input = reg_val;

	for (i = 0, pin_index = 0; i < 16; i++) {
		if (val & (1 << i)) {
			struct tca6416_button *button = &chip->buttons[pin_index];
			unsigned int type = button->type ?: EV_KEY;
			int state = ((reg_val & (1 << i)) ? 1 : 0)
						^ button->active_low;

			input_event(input, type, button->code, !!state);
			input_sync(input);
		}

		if (chip->pinmask & (1 << i))
			pin_index++;
	}
}
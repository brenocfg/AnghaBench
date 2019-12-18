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
struct tca6416_keypad_chip {int reg_output; int reg_direction; int pinmask; int reg_input; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCA6416_DIRECTION ; 
 int /*<<< orphan*/  TCA6416_INPUT ; 
 int /*<<< orphan*/  TCA6416_OUTPUT ; 
 int tca6416_read_reg (struct tca6416_keypad_chip*,int /*<<< orphan*/ ,int*) ; 
 int tca6416_write_reg (struct tca6416_keypad_chip*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tca6416_setup_registers(struct tca6416_keypad_chip *chip)
{
	int error;

	error = tca6416_read_reg(chip, TCA6416_OUTPUT, &chip->reg_output);
	if (error)
		return error;

	error = tca6416_read_reg(chip, TCA6416_DIRECTION, &chip->reg_direction);
	if (error)
		return error;

	/* ensure that keypad pins are set to input */
	error = tca6416_write_reg(chip, TCA6416_DIRECTION,
				  chip->reg_direction | chip->pinmask);
	if (error)
		return error;

	error = tca6416_read_reg(chip, TCA6416_DIRECTION, &chip->reg_direction);
	if (error)
		return error;

	error = tca6416_read_reg(chip, TCA6416_INPUT, &chip->reg_input);
	if (error)
		return error;

	chip->reg_input &= chip->pinmask;

	return 0;
}
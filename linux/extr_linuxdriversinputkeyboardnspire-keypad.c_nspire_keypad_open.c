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
struct nspire_keypad {int /*<<< orphan*/  clk; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 struct nspire_keypad* input_get_drvdata (struct input_dev*) ; 
 int nspire_keypad_chip_init (struct nspire_keypad*) ; 

__attribute__((used)) static int nspire_keypad_open(struct input_dev *input)
{
	struct nspire_keypad *keypad = input_get_drvdata(input);
	int error;

	error = clk_prepare_enable(keypad->clk);
	if (error)
		return error;

	error = nspire_keypad_chip_init(keypad);
	if (error) {
		clk_disable_unprepare(keypad->clk);
		return error;
	}

	return 0;
}
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
struct input_dev {int dummy; } ;

/* Variables and functions */
 struct tc_keypad* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  tc3589x_keypad_disable (struct tc_keypad*) ; 

__attribute__((used)) static void tc3589x_keypad_close(struct input_dev *input)
{
	struct tc_keypad *keypad = input_get_drvdata(input);

	/* disable the keypad module */
	tc3589x_keypad_disable(keypad);
}
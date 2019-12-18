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
struct pxa27x_keypad {int /*<<< orphan*/  clk; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 struct pxa27x_keypad* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  pxa27x_keypad_config (struct pxa27x_keypad*) ; 

__attribute__((used)) static int pxa27x_keypad_open(struct input_dev *dev)
{
	struct pxa27x_keypad *keypad = input_get_drvdata(dev);
	int ret;
	/* Enable unit clock */
	ret = clk_prepare_enable(keypad->clk);
	if (ret)
		return ret;

	pxa27x_keypad_config(keypad);

	return 0;
}
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
struct tc_keypad {int keypad_stopped; struct tc3589x* tc3589x; } ;
struct tc3589x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TC3589x_CLKEN ; 
 int TC3589x_EVT_INT ; 
 int TC3589x_EVT_INT_CLR ; 
 int TC3589x_EVT_LOSS_INT ; 
 int /*<<< orphan*/  TC3589x_KBDIC ; 
 int /*<<< orphan*/  TC3589x_KBDMSK ; 
 int TC3589x_KBDRST ; 
 int TC3589x_KBD_INT_CLR ; 
 int /*<<< orphan*/  TC3589x_RSTCTRL ; 
 int tc3589x_set_bits (struct tc3589x*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int tc3589x_keypad_disable(struct tc_keypad *keypad)
{
	struct tc3589x *tc3589x = keypad->tc3589x;
	int ret;

	/* clear IRQ */
	ret = tc3589x_set_bits(tc3589x, TC3589x_KBDIC,
			0x0, TC3589x_EVT_INT_CLR | TC3589x_KBD_INT_CLR);
	if (ret < 0)
		return ret;

	/* disable all interrupts */
	ret = tc3589x_set_bits(tc3589x, TC3589x_KBDMSK,
			~(TC3589x_EVT_LOSS_INT | TC3589x_EVT_INT), 0x0);
	if (ret < 0)
		return ret;

	/* disable the keypad module */
	ret = tc3589x_set_bits(tc3589x, TC3589x_CLKEN, 0x1, 0x0);
	if (ret < 0)
		return ret;

	/* put the keypad module into reset */
	ret = tc3589x_set_bits(tc3589x, TC3589x_RSTCTRL, TC3589x_KBDRST, 0x1);

	keypad->keypad_stopped = true;

	return ret;
}
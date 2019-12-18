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
struct pxa27x_keypad {int* rotary_rel_code; unsigned char* keycodes; struct input_dev* input_dev; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_MSC ; 
 int MAX_MATRIX_KEY_NUM ; 
 int /*<<< orphan*/  MSC_SCAN ; 
 int /*<<< orphan*/  input_event (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,unsigned char,int) ; 
 int /*<<< orphan*/  input_report_rel (struct input_dev*,int,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 

__attribute__((used)) static void report_rotary_event(struct pxa27x_keypad *keypad, int r, int delta)
{
	struct input_dev *dev = keypad->input_dev;

	if (delta == 0)
		return;

	if (keypad->rotary_rel_code[r] == -1) {
		int code = MAX_MATRIX_KEY_NUM + 2 * r + (delta > 0 ? 0 : 1);
		unsigned char keycode = keypad->keycodes[code];

		/* simulate a press-n-release */
		input_event(dev, EV_MSC, MSC_SCAN, code);
		input_report_key(dev, keycode, 1);
		input_sync(dev);
		input_event(dev, EV_MSC, MSC_SCAN, code);
		input_report_key(dev, keycode, 0);
		input_sync(dev);
	} else {
		input_report_rel(dev, keypad->rotary_rel_code[r], delta);
		input_sync(dev);
	}
}
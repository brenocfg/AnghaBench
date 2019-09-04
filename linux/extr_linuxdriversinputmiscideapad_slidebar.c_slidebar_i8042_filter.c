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
struct serio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 unsigned char I8042_STR_AUXDATA ; 
 int /*<<< orphan*/  input_report_abs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  serio_interrupt (struct serio*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slidebar_input_dev ; 
 int /*<<< orphan*/  slidebar_pos_get () ; 

__attribute__((used)) static bool slidebar_i8042_filter(unsigned char data, unsigned char str,
				  struct serio *port)
{
	static bool extended = false;

	/* We are only interested in data coming form KBC port */
	if (str & I8042_STR_AUXDATA)
		return false;

	/* Scancodes: e03b on move, e0bb on release. */
	if (data == 0xe0) {
		extended = true;
		return true;
	}

	if (!extended)
		return false;

	extended = false;

	if (likely((data & 0x7f) != 0x3b)) {
		serio_interrupt(port, 0xe0, 0);
		return false;
	}

	if (data & 0x80) {
		input_report_key(slidebar_input_dev, BTN_TOUCH, 0);
	} else {
		input_report_key(slidebar_input_dev, BTN_TOUCH, 1);
		input_report_abs(slidebar_input_dev, ABS_X, slidebar_pos_get());
	}
	input_sync(slidebar_input_dev);

	return true;
}
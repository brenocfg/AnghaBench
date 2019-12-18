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
struct input_dev {int dummy; } ;
struct hidpp_scroll_counter {int wheel_multiplier; int remainder; unsigned long long last_time; int direction; } ;

/* Variables and functions */
 int /*<<< orphan*/  REL_WHEEL ; 
 int /*<<< orphan*/  REL_WHEEL_HI_RES ; 
 int abs (int) ; 
 int /*<<< orphan*/  input_report_rel (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 unsigned long long sched_clock () ; 

__attribute__((used)) static void hidpp_scroll_counter_handle_scroll(struct input_dev *input_dev,
					       struct hidpp_scroll_counter *counter,
					       int hi_res_value)
{
	int low_res_value, remainder, direction;
	unsigned long long now, previous;

	hi_res_value = hi_res_value * 120/counter->wheel_multiplier;
	input_report_rel(input_dev, REL_WHEEL_HI_RES, hi_res_value);

	remainder = counter->remainder;
	direction = hi_res_value > 0 ? 1 : -1;

	now = sched_clock();
	previous = counter->last_time;
	counter->last_time = now;
	/*
	 * Reset the remainder after a period of inactivity or when the
	 * direction changes. This prevents the REL_WHEEL emulation point
	 * from sliding for devices that don't always provide the same
	 * number of movements per detent.
	 */
	if (now - previous > 1000000000 || direction != counter->direction)
		remainder = 0;

	counter->direction = direction;
	remainder += hi_res_value;

	/* Some wheels will rest 7/8ths of a detent from the previous detent
	 * after slow movement, so we want the threshold for low-res events to
	 * be in the middle between two detents (e.g. after 4/8ths) as
	 * opposed to on the detents themselves (8/8ths).
	 */
	if (abs(remainder) >= 60) {
		/* Add (or subtract) 1 because we want to trigger when the wheel
		 * is half-way to the next detent (i.e. scroll 1 detent after a
		 * 1/2 detent movement, 2 detents after a 1 1/2 detent movement,
		 * etc.).
		 */
		low_res_value = remainder / 120;
		if (low_res_value == 0)
			low_res_value = (hi_res_value > 0 ? 1 : -1);
		input_report_rel(input_dev, REL_WHEEL, low_res_value);
		remainder -= low_res_value * 120;
	}
	counter->remainder = remainder;
}
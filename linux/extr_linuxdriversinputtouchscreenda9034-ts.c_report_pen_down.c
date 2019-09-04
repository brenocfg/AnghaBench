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
struct da9034_touch {int last_x; int last_y; int /*<<< orphan*/  input_dev; scalar_t__ y_inverted; scalar_t__ x_inverted; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int /*<<< orphan*/  input_report_abs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void report_pen_down(struct da9034_touch *touch)
{
	int x = touch->last_x;
	int y = touch->last_y;

	x &= 0xfff;
	if (touch->x_inverted)
		x = 1024 - x;
	y &= 0xfff;
	if (touch->y_inverted)
		y = 1024 - y;

	input_report_abs(touch->input_dev, ABS_X, x);
	input_report_abs(touch->input_dev, ABS_Y, y);
	input_report_key(touch->input_dev, BTN_TOUCH, 1);

	input_sync(touch->input_dev);
}
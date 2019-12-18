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
struct wm831x_ts {struct wm831x* wm831x; } ;
struct wm831x {int dummy; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int WM831X_TCH_CVT_ENA ; 
 int WM831X_TCH_ENA ; 
 int WM831X_TCH_X_ENA ; 
 int WM831X_TCH_Y_ENA ; 
 int WM831X_TCH_Z_ENA ; 
 int /*<<< orphan*/  WM831X_TOUCH_CONTROL_1 ; 
 struct wm831x_ts* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  wm831x_set_bits (struct wm831x*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int wm831x_ts_input_open(struct input_dev *idev)
{
	struct wm831x_ts *wm831x_ts = input_get_drvdata(idev);
	struct wm831x *wm831x = wm831x_ts->wm831x;

	wm831x_set_bits(wm831x, WM831X_TOUCH_CONTROL_1,
			WM831X_TCH_ENA | WM831X_TCH_CVT_ENA |
			WM831X_TCH_X_ENA | WM831X_TCH_Y_ENA |
			WM831X_TCH_Z_ENA, WM831X_TCH_ENA);

	wm831x_set_bits(wm831x, WM831X_TOUCH_CONTROL_1,
			WM831X_TCH_CVT_ENA, WM831X_TCH_CVT_ENA);

	return 0;
}
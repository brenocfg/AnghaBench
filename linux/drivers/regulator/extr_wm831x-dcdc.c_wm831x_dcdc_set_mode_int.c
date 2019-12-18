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
struct wm831x {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  REGULATOR_MODE_FAST 131 
#define  REGULATOR_MODE_IDLE 130 
#define  REGULATOR_MODE_NORMAL 129 
#define  REGULATOR_MODE_STANDBY 128 
 int /*<<< orphan*/  WM831X_DC1_ON_MODE_MASK ; 
 int WM831X_DC1_ON_MODE_SHIFT ; 
 int WM831X_DCDC_MODE_FAST ; 
 int WM831X_DCDC_MODE_IDLE ; 
 int WM831X_DCDC_MODE_NORMAL ; 
 int WM831X_DCDC_MODE_STANDBY ; 
 int wm831x_set_bits (struct wm831x*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm831x_dcdc_set_mode_int(struct wm831x *wm831x, int reg,
				    unsigned int mode)
{
	int val;

	switch (mode) {
	case REGULATOR_MODE_FAST:
		val = WM831X_DCDC_MODE_FAST;
		break;
	case REGULATOR_MODE_NORMAL:
		val = WM831X_DCDC_MODE_NORMAL;
		break;
	case REGULATOR_MODE_STANDBY:
		val = WM831X_DCDC_MODE_STANDBY;
		break;
	case REGULATOR_MODE_IDLE:
		val = WM831X_DCDC_MODE_IDLE;
		break;
	default:
		return -EINVAL;
	}

	return wm831x_set_bits(wm831x, reg, WM831X_DC1_ON_MODE_MASK,
			       val << WM831X_DC1_ON_MODE_SHIFT);
}
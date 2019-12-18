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
typedef  scalar_t__ u16 ;
struct wm831x_dcdc {scalar_t__ base; struct wm831x* wm831x; } ;
struct wm831x {int dummy; } ;
struct regulator_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 unsigned int EINVAL ; 
 unsigned int REGULATOR_MODE_FAST ; 
 unsigned int REGULATOR_MODE_IDLE ; 
 unsigned int REGULATOR_MODE_NORMAL ; 
 unsigned int REGULATOR_MODE_STANDBY ; 
 int WM831X_DC1_ON_MODE_MASK ; 
 int WM831X_DC1_ON_MODE_SHIFT ; 
#define  WM831X_DCDC_MODE_FAST 131 
#define  WM831X_DCDC_MODE_IDLE 130 
#define  WM831X_DCDC_MODE_NORMAL 129 
#define  WM831X_DCDC_MODE_STANDBY 128 
 scalar_t__ WM831X_DCDC_ON_CONFIG ; 
 struct wm831x_dcdc* rdev_get_drvdata (struct regulator_dev*) ; 
 int wm831x_reg_read (struct wm831x*,scalar_t__) ; 

__attribute__((used)) static unsigned int wm831x_dcdc_get_mode(struct regulator_dev *rdev)

{
	struct wm831x_dcdc *dcdc = rdev_get_drvdata(rdev);
	struct wm831x *wm831x = dcdc->wm831x;
	u16 reg = dcdc->base + WM831X_DCDC_ON_CONFIG;
	int val;

	val = wm831x_reg_read(wm831x, reg);
	if (val < 0)
		return val;

	val = (val & WM831X_DC1_ON_MODE_MASK) >> WM831X_DC1_ON_MODE_SHIFT;

	switch (val) {
	case WM831X_DCDC_MODE_FAST:
		return REGULATOR_MODE_FAST;
	case WM831X_DCDC_MODE_NORMAL:
		return REGULATOR_MODE_NORMAL;
	case WM831X_DCDC_MODE_STANDBY:
		return REGULATOR_MODE_STANDBY;
	case WM831X_DCDC_MODE_IDLE:
		return REGULATOR_MODE_IDLE;
	default:
		BUG();
		return -EINVAL;
	}
}
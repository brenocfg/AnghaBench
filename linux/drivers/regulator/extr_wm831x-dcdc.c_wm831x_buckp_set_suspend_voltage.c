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
 int /*<<< orphan*/  WM831X_DC3_ON_VSEL_MASK ; 
 scalar_t__ WM831X_DCDC_SLEEP_CONTROL ; 
 struct wm831x_dcdc* rdev_get_drvdata (struct regulator_dev*) ; 
 int regulator_map_voltage_linear (struct regulator_dev*,int,int) ; 
 int wm831x_set_bits (struct wm831x*,scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm831x_buckp_set_suspend_voltage(struct regulator_dev *rdev, int uV)
{
	struct wm831x_dcdc *dcdc = rdev_get_drvdata(rdev);
	struct wm831x *wm831x = dcdc->wm831x;
	u16 reg = dcdc->base + WM831X_DCDC_SLEEP_CONTROL;
	int sel;

	sel = regulator_map_voltage_linear(rdev, uV, uV);
	if (sel < 0)
		return sel;

	return wm831x_set_bits(wm831x, reg, WM831X_DC3_ON_VSEL_MASK, sel);
}
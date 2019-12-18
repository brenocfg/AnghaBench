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
struct wm831x_ldo {int base; struct wm831x* wm831x; } ;
struct wm831x {int dummy; } ;
struct regulator_dev {int dummy; } ;

/* Variables and functions */
 unsigned int REGULATOR_MODE_IDLE ; 
 unsigned int REGULATOR_MODE_NORMAL ; 
 unsigned int REGULATOR_MODE_STANDBY ; 
 int WM831X_LDO1_LP_MODE ; 
 int WM831X_LDO1_ON_MODE ; 
 int WM831X_LDO_CONTROL ; 
 int WM831X_LDO_ON_CONTROL ; 
 struct wm831x_ldo* rdev_get_drvdata (struct regulator_dev*) ; 
 int wm831x_reg_read (struct wm831x*,int) ; 

__attribute__((used)) static unsigned int wm831x_gp_ldo_get_mode(struct regulator_dev *rdev)
{
	struct wm831x_ldo *ldo = rdev_get_drvdata(rdev);
	struct wm831x *wm831x = ldo->wm831x;
	int ctrl_reg = ldo->base + WM831X_LDO_CONTROL;
	int on_reg = ldo->base + WM831X_LDO_ON_CONTROL;
	int ret;

	ret = wm831x_reg_read(wm831x, on_reg);
	if (ret < 0)
		return ret;

	if (!(ret & WM831X_LDO1_ON_MODE))
		return REGULATOR_MODE_NORMAL;

	ret = wm831x_reg_read(wm831x, ctrl_reg);
	if (ret < 0)
		return ret;

	if (ret & WM831X_LDO1_LP_MODE)
		return REGULATOR_MODE_STANDBY;
	else
		return REGULATOR_MODE_IDLE;
}
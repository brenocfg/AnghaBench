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
struct wm831x_dcdc {struct wm831x* wm831x; } ;
struct wm831x {int /*<<< orphan*/  dev; } ;
struct regulator_dev {int dummy; } ;

/* Variables and functions */
 int REGULATOR_STATUS_ERROR ; 
 int REGULATOR_STATUS_OFF ; 
 int REGULATOR_STATUS_ON ; 
 int WM831X_DC1_HC_STS ; 
 int WM831X_DC1_OV_STS ; 
 int /*<<< orphan*/  WM831X_DCDC_STATUS ; 
 int /*<<< orphan*/  WM831X_DCDC_UV_STATUS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 struct wm831x_dcdc* rdev_get_drvdata (struct regulator_dev*) ; 
 int rdev_get_id (struct regulator_dev*) ; 
 int wm831x_reg_read (struct wm831x*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm831x_dcdc_get_status(struct regulator_dev *rdev)
{
	struct wm831x_dcdc *dcdc = rdev_get_drvdata(rdev);
	struct wm831x *wm831x = dcdc->wm831x;
	int ret;

	/* First, check for errors */
	ret = wm831x_reg_read(wm831x, WM831X_DCDC_UV_STATUS);
	if (ret < 0)
		return ret;

	if (ret & (1 << rdev_get_id(rdev))) {
		dev_dbg(wm831x->dev, "DCDC%d under voltage\n",
			rdev_get_id(rdev) + 1);
		return REGULATOR_STATUS_ERROR;
	}

	/* DCDC1 and DCDC2 can additionally detect high voltage/current */
	if (rdev_get_id(rdev) < 2) {
		if (ret & (WM831X_DC1_OV_STS << rdev_get_id(rdev))) {
			dev_dbg(wm831x->dev, "DCDC%d over voltage\n",
				rdev_get_id(rdev) + 1);
			return REGULATOR_STATUS_ERROR;
		}

		if (ret & (WM831X_DC1_HC_STS << rdev_get_id(rdev))) {
			dev_dbg(wm831x->dev, "DCDC%d over current\n",
				rdev_get_id(rdev) + 1);
			return REGULATOR_STATUS_ERROR;
		}
	}

	/* Is the regulator on? */
	ret = wm831x_reg_read(wm831x, WM831X_DCDC_STATUS);
	if (ret < 0)
		return ret;
	if (!(ret & (1 << rdev_get_id(rdev))))
		return REGULATOR_STATUS_OFF;

	/* TODO: When we handle hardware control modes so we can report the
	 * current mode. */
	return REGULATOR_STATUS_ON;
}
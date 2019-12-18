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
struct wm831x_dcdc {int base; unsigned int on_vsel; unsigned int dvs_vsel; scalar_t__ dvs_gpiod; struct wm831x* wm831x; } ;
struct wm831x {int /*<<< orphan*/  dev; } ;
struct regulator_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WM831X_DC1_DVS_VSEL_MASK ; 
 int /*<<< orphan*/  WM831X_DC1_ON_VSEL_MASK ; 
 int WM831X_DCDC_DVS_CONTROL ; 
 int WM831X_DCDC_ON_CONFIG ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 struct wm831x_dcdc* rdev_get_drvdata (struct regulator_dev*) ; 
 int wm831x_buckv_set_dvs (struct regulator_dev*,int) ; 
 int wm831x_set_bits (struct wm831x*,int,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int wm831x_buckv_set_voltage_sel(struct regulator_dev *rdev,
					unsigned vsel)
{
	struct wm831x_dcdc *dcdc = rdev_get_drvdata(rdev);
	struct wm831x *wm831x = dcdc->wm831x;
	int on_reg = dcdc->base + WM831X_DCDC_ON_CONFIG;
	int dvs_reg = dcdc->base + WM831X_DCDC_DVS_CONTROL;
	int ret;

	/* If this value is already set then do a GPIO update if we can */
	if (dcdc->dvs_gpiod && dcdc->on_vsel == vsel)
		return wm831x_buckv_set_dvs(rdev, 0);

	if (dcdc->dvs_gpiod && dcdc->dvs_vsel == vsel)
		return wm831x_buckv_set_dvs(rdev, 1);

	/* Always set the ON status to the minimum voltage */
	ret = wm831x_set_bits(wm831x, on_reg, WM831X_DC1_ON_VSEL_MASK, vsel);
	if (ret < 0)
		return ret;
	dcdc->on_vsel = vsel;

	if (!dcdc->dvs_gpiod)
		return ret;

	/* Kick the voltage transition now */
	ret = wm831x_buckv_set_dvs(rdev, 0);
	if (ret < 0)
		return ret;

	/*
	 * If this VSEL is higher than the last one we've seen then
	 * remember it as the DVS VSEL.  This is optimised for CPUfreq
	 * usage where we want to get to the highest voltage very
	 * quickly.
	 */
	if (vsel > dcdc->dvs_vsel) {
		ret = wm831x_set_bits(wm831x, dvs_reg,
				      WM831X_DC1_DVS_VSEL_MASK,
				      vsel);
		if (ret == 0)
			dcdc->dvs_vsel = vsel;
		else
			dev_warn(wm831x->dev,
				 "Failed to set DCDC DVS VSEL: %d\n", ret);
	}

	return 0;
}
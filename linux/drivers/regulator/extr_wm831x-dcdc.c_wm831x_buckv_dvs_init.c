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
typedef  int u16 ;
struct wm831x_dcdc {int name; int dvs_vsel; int on_vsel; scalar_t__ base; int /*<<< orphan*/  dvs_gpiod; scalar_t__ dvs_gpio_state; struct wm831x* wm831x; } ;
struct wm831x_buckv_pdata {int dvs_control_src; scalar_t__ dvs_init_state; } ;
struct wm831x {int /*<<< orphan*/  dev; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM831X_DC1_DVS_SRC_MASK ; 
 int WM831X_DC1_DVS_SRC_SHIFT ; 
 int /*<<< orphan*/  WM831X_DC1_DVS_VSEL_MASK ; 
 scalar_t__ WM831X_DCDC_DVS_CONTROL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  devm_gpiod_get (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int wm831x_set_bits (struct wm831x*,scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void wm831x_buckv_dvs_init(struct platform_device *pdev,
				  struct wm831x_dcdc *dcdc,
				  struct wm831x_buckv_pdata *pdata)
{
	struct wm831x *wm831x = dcdc->wm831x;
	int ret;
	u16 ctrl;

	if (!pdata)
		return;

	/* gpiolib won't let us read the GPIO status so pick the higher
	 * of the two existing voltages so we take it as platform data.
	 */
	dcdc->dvs_gpio_state = pdata->dvs_init_state;

	dcdc->dvs_gpiod = devm_gpiod_get(&pdev->dev, "dvs",
			dcdc->dvs_gpio_state ? GPIOD_OUT_HIGH : GPIOD_OUT_LOW);
	if (IS_ERR(dcdc->dvs_gpiod)) {
		dev_err(wm831x->dev, "Failed to get %s DVS GPIO: %ld\n",
			dcdc->name, PTR_ERR(dcdc->dvs_gpiod));
		return;
	}

	switch (pdata->dvs_control_src) {
	case 1:
		ctrl = 2 << WM831X_DC1_DVS_SRC_SHIFT;
		break;
	case 2:
		ctrl = 3 << WM831X_DC1_DVS_SRC_SHIFT;
		break;
	default:
		dev_err(wm831x->dev, "Invalid DVS control source %d for %s\n",
			pdata->dvs_control_src, dcdc->name);
		return;
	}

	/* If DVS_VSEL is set to the minimum value then raise it to ON_VSEL
	 * to make bootstrapping a bit smoother.
	 */
	if (!dcdc->dvs_vsel) {
		ret = wm831x_set_bits(wm831x,
				      dcdc->base + WM831X_DCDC_DVS_CONTROL,
				      WM831X_DC1_DVS_VSEL_MASK, dcdc->on_vsel);
		if (ret == 0)
			dcdc->dvs_vsel = dcdc->on_vsel;
		else
			dev_warn(wm831x->dev, "Failed to set DVS_VSEL: %d\n",
				 ret);
	}

	ret = wm831x_set_bits(wm831x, dcdc->base + WM831X_DCDC_DVS_CONTROL,
			      WM831X_DC1_DVS_SRC_MASK, ctrl);
	if (ret < 0) {
		dev_err(wm831x->dev, "Failed to set %s DVS source: %d\n",
			dcdc->name, ret);
	}
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * init; } ;
struct wm831x_clk {int xtal_ena; TYPE_3__ clkout_hw; TYPE_3__ fll_hw; TYPE_3__ xtal_hw; struct wm831x* wm831x; } ;
struct wm831x {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WM831X_CLOCK_CONTROL_2 ; 
 int WM831X_XTAL_ENA ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct wm831x* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int devm_clk_hw_register (TYPE_1__*,TYPE_3__*) ; 
 struct wm831x_clk* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct wm831x_clk*) ; 
 int /*<<< orphan*/  wm831x_clkout_init ; 
 int /*<<< orphan*/  wm831x_fll_init ; 
 int wm831x_reg_read (struct wm831x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm831x_xtal_init ; 

__attribute__((used)) static int wm831x_clk_probe(struct platform_device *pdev)
{
	struct wm831x *wm831x = dev_get_drvdata(pdev->dev.parent);
	struct wm831x_clk *clkdata;
	int ret;

	clkdata = devm_kzalloc(&pdev->dev, sizeof(*clkdata), GFP_KERNEL);
	if (!clkdata)
		return -ENOMEM;

	clkdata->wm831x = wm831x;

	/* XTAL_ENA can only be set via OTP/InstantConfig so just read once */
	ret = wm831x_reg_read(wm831x, WM831X_CLOCK_CONTROL_2);
	if (ret < 0) {
		dev_err(wm831x->dev, "Unable to read CLOCK_CONTROL_2: %d\n",
			ret);
		return ret;
	}
	clkdata->xtal_ena = ret & WM831X_XTAL_ENA;

	clkdata->xtal_hw.init = &wm831x_xtal_init;
	ret = devm_clk_hw_register(&pdev->dev, &clkdata->xtal_hw);
	if (ret)
		return ret;

	clkdata->fll_hw.init = &wm831x_fll_init;
	ret = devm_clk_hw_register(&pdev->dev, &clkdata->fll_hw);
	if (ret)
		return ret;

	clkdata->clkout_hw.init = &wm831x_clkout_init;
	ret = devm_clk_hw_register(&pdev->dev, &clkdata->clkout_hw);
	if (ret)
		return ret;

	platform_set_drvdata(pdev, clkdata);

	return 0;
}
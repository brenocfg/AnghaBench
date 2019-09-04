#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {struct device_node* of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct TYPE_7__ {int pixelclock; int hactive; int vactive; } ;
struct panel_drv_data {int use_dsi_backlight; int /*<<< orphan*/  extbldev; int /*<<< orphan*/ * vddi; int /*<<< orphan*/ * vpnl; scalar_t__ height_mm; scalar_t__ width_mm; TYPE_1__ vm; int /*<<< orphan*/ * ext_te_gpio; int /*<<< orphan*/ * reset_gpio; } ;
struct display_timing {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GPIOD_IN ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  dev_warn (TYPE_2__*,char*) ; 
 int /*<<< orphan*/ * devm_gpiod_get (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * devm_gpiod_get_optional (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 void* devm_regulator_get_optional (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  of_find_backlight_by_node (struct device_node*) ; 
 int of_get_display_timing (struct device_node*,char*,struct display_timing*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,scalar_t__*) ; 
 struct panel_drv_data* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  videomode_from_timing (struct display_timing*,TYPE_1__*) ; 

__attribute__((used)) static int dsicm_probe_of(struct platform_device *pdev)
{
	struct device_node *node = pdev->dev.of_node;
	struct device_node *backlight;
	struct panel_drv_data *ddata = platform_get_drvdata(pdev);
	struct display_timing timing;
	int err;

	ddata->reset_gpio = devm_gpiod_get(&pdev->dev, "reset", GPIOD_OUT_LOW);
	if (IS_ERR(ddata->reset_gpio)) {
		err = PTR_ERR(ddata->reset_gpio);
		dev_err(&pdev->dev, "reset gpio request failed: %d", err);
		return err;
	}

	ddata->ext_te_gpio = devm_gpiod_get_optional(&pdev->dev, "te",
						     GPIOD_IN);
	if (IS_ERR(ddata->ext_te_gpio)) {
		err = PTR_ERR(ddata->ext_te_gpio);
		dev_err(&pdev->dev, "TE gpio request failed: %d", err);
		return err;
	}

	err = of_get_display_timing(node, "panel-timing", &timing);
	if (!err) {
		videomode_from_timing(&timing, &ddata->vm);
		if (!ddata->vm.pixelclock)
			ddata->vm.pixelclock =
				ddata->vm.hactive * ddata->vm.vactive * 60;
	} else {
		dev_warn(&pdev->dev,
			 "failed to get video timing, using defaults\n");
	}

	ddata->width_mm = 0;
	of_property_read_u32(node, "width-mm", &ddata->width_mm);

	ddata->height_mm = 0;
	of_property_read_u32(node, "height-mm", &ddata->height_mm);

	ddata->vpnl = devm_regulator_get_optional(&pdev->dev, "vpnl");
	if (IS_ERR(ddata->vpnl)) {
		err = PTR_ERR(ddata->vpnl);
		if (err == -EPROBE_DEFER)
			return err;
		ddata->vpnl = NULL;
	}

	ddata->vddi = devm_regulator_get_optional(&pdev->dev, "vddi");
	if (IS_ERR(ddata->vddi)) {
		err = PTR_ERR(ddata->vddi);
		if (err == -EPROBE_DEFER)
			return err;
		ddata->vddi = NULL;
	}

	backlight = of_parse_phandle(node, "backlight", 0);
	if (backlight) {
		ddata->extbldev = of_find_backlight_by_node(backlight);
		of_node_put(backlight);

		if (!ddata->extbldev)
			return -EPROBE_DEFER;
	} else {
		/* assume native backlight support */
		ddata->use_dsi_backlight = true;
	}

	/* TODO: ulps */

	return 0;
}
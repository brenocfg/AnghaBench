#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  vm; } ;
struct omap_dss_device {TYPE_1__ panel; int /*<<< orphan*/  owner; int /*<<< orphan*/  type; int /*<<< orphan*/ * driver; int /*<<< orphan*/ * dev; } ;
struct panel_drv_data {int /*<<< orphan*/  vm; struct omap_dss_device dssdev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  OMAP_DISPLAY_TYPE_DPI ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct panel_drv_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int omapdss_register_display (struct omap_dss_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct panel_drv_data*) ; 
 int /*<<< orphan*/  sharp_ls_ops ; 
 int sharp_ls_probe_of (struct platform_device*) ; 
 int /*<<< orphan*/  sharp_ls_vm ; 

__attribute__((used)) static int sharp_ls_probe(struct platform_device *pdev)
{
	struct panel_drv_data *ddata;
	struct omap_dss_device *dssdev;
	int r;

	ddata = devm_kzalloc(&pdev->dev, sizeof(*ddata), GFP_KERNEL);
	if (ddata == NULL)
		return -ENOMEM;

	platform_set_drvdata(pdev, ddata);

	r = sharp_ls_probe_of(pdev);
	if (r)
		return r;

	ddata->vm = sharp_ls_vm;

	dssdev = &ddata->dssdev;
	dssdev->dev = &pdev->dev;
	dssdev->driver = &sharp_ls_ops;
	dssdev->type = OMAP_DISPLAY_TYPE_DPI;
	dssdev->owner = THIS_MODULE;
	dssdev->panel.vm = ddata->vm;

	r = omapdss_register_display(dssdev);
	if (r) {
		dev_err(&pdev->dev, "Failed to register panel\n");
		return r;
	}

	return 0;
}
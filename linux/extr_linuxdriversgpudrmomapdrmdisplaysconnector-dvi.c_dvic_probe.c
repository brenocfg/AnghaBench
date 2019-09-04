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
struct TYPE_2__ {void* vm; } ;
struct omap_dss_device {TYPE_1__ panel; int /*<<< orphan*/  owner; int /*<<< orphan*/  type; int /*<<< orphan*/ * dev; int /*<<< orphan*/ * driver; } ;
struct panel_drv_data {int /*<<< orphan*/  hpd_lock; int /*<<< orphan*/  i2c_adapter; struct omap_dss_device dssdev; void* vm; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  OMAP_DISPLAY_TYPE_DVI ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct panel_drv_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 void* dvic_default_vm ; 
 int /*<<< orphan*/  dvic_driver ; 
 int dvic_probe_of (struct platform_device*) ; 
 int /*<<< orphan*/  i2c_put_adapter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int omapdss_register_display (struct omap_dss_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct panel_drv_data*) ; 

__attribute__((used)) static int dvic_probe(struct platform_device *pdev)
{
	struct panel_drv_data *ddata;
	struct omap_dss_device *dssdev;
	int r;

	ddata = devm_kzalloc(&pdev->dev, sizeof(*ddata), GFP_KERNEL);
	if (!ddata)
		return -ENOMEM;

	platform_set_drvdata(pdev, ddata);

	r = dvic_probe_of(pdev);
	if (r)
		return r;

	ddata->vm = dvic_default_vm;

	dssdev = &ddata->dssdev;
	dssdev->driver = &dvic_driver;
	dssdev->dev = &pdev->dev;
	dssdev->type = OMAP_DISPLAY_TYPE_DVI;
	dssdev->owner = THIS_MODULE;
	dssdev->panel.vm = dvic_default_vm;

	r = omapdss_register_display(dssdev);
	if (r) {
		dev_err(&pdev->dev, "Failed to register panel\n");
		goto err_reg;
	}

	return 0;

err_reg:
	i2c_put_adapter(ddata->i2c_adapter);
	mutex_destroy(&ddata->hpd_lock);

	return r;
}
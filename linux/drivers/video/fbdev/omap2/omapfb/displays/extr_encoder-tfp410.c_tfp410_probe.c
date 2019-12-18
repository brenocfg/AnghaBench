#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_4__ dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  data_lines; } ;
struct TYPE_9__ {TYPE_2__ dpi; } ;
struct TYPE_7__ {int /*<<< orphan*/ * dvi; } ;
struct omap_dss_device {int port_num; TYPE_3__ phy; int /*<<< orphan*/  owner; int /*<<< orphan*/  output_type; int /*<<< orphan*/  type; TYPE_4__* dev; TYPE_1__ ops; } ;
struct panel_drv_data {int /*<<< orphan*/  in; int /*<<< orphan*/  data_lines; struct omap_dss_device dssdev; int /*<<< orphan*/  pd_gpio; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOF_OUT_INIT_LOW ; 
 int /*<<< orphan*/  OMAP_DISPLAY_TYPE_DPI ; 
 int /*<<< orphan*/  OMAP_DISPLAY_TYPE_DVI ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*,...) ; 
 int devm_gpio_request_one (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 struct panel_drv_data* devm_kzalloc (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_dss_put_device (int /*<<< orphan*/ ) ; 
 int omapdss_register_output (struct omap_dss_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct panel_drv_data*) ; 
 int /*<<< orphan*/  tfp410_dvi_ops ; 
 int tfp410_probe_of (struct platform_device*) ; 

__attribute__((used)) static int tfp410_probe(struct platform_device *pdev)
{
	struct panel_drv_data *ddata;
	struct omap_dss_device *dssdev;
	int r;

	if (!pdev->dev.of_node)
		return -ENODEV;

	ddata = devm_kzalloc(&pdev->dev, sizeof(*ddata), GFP_KERNEL);
	if (!ddata)
		return -ENOMEM;

	platform_set_drvdata(pdev, ddata);

	r = tfp410_probe_of(pdev);
	if (r)
		return r;

	if (gpio_is_valid(ddata->pd_gpio)) {
		r = devm_gpio_request_one(&pdev->dev, ddata->pd_gpio,
				GPIOF_OUT_INIT_LOW, "tfp410 PD");
		if (r) {
			dev_err(&pdev->dev, "Failed to request PD GPIO %d\n",
					ddata->pd_gpio);
			goto err_gpio;
		}
	}

	dssdev = &ddata->dssdev;
	dssdev->ops.dvi = &tfp410_dvi_ops;
	dssdev->dev = &pdev->dev;
	dssdev->type = OMAP_DISPLAY_TYPE_DPI;
	dssdev->output_type = OMAP_DISPLAY_TYPE_DVI;
	dssdev->owner = THIS_MODULE;
	dssdev->phy.dpi.data_lines = ddata->data_lines;
	dssdev->port_num = 1;

	r = omapdss_register_output(dssdev);
	if (r) {
		dev_err(&pdev->dev, "Failed to register output\n");
		goto err_reg;
	}

	return 0;
err_reg:
err_gpio:
	omap_dss_put_device(ddata->in);
	return r;
}
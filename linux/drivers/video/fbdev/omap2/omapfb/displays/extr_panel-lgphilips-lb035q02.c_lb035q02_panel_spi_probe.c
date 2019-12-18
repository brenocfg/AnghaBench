#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  of_node; } ;
struct spi_device {TYPE_4__ dev; } ;
struct TYPE_9__ {int /*<<< orphan*/  data_lines; } ;
struct TYPE_10__ {TYPE_2__ dpi; } ;
struct TYPE_8__ {int /*<<< orphan*/  timings; } ;
struct omap_dss_device {TYPE_3__ phy; TYPE_1__ panel; int /*<<< orphan*/  owner; int /*<<< orphan*/  type; int /*<<< orphan*/ * driver; TYPE_4__* dev; } ;
struct panel_drv_data {int /*<<< orphan*/  in; int /*<<< orphan*/  data_lines; int /*<<< orphan*/  videomode; struct omap_dss_device dssdev; int /*<<< orphan*/  backlight_gpio; struct spi_device* spi; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOF_OUT_INIT_LOW ; 
 int /*<<< orphan*/  OMAP_DISPLAY_TYPE_DPI ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_4__*,struct panel_drv_data*) ; 
 int devm_gpio_request_one (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 struct panel_drv_data* devm_kzalloc (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lb035q02_ops ; 
 int lb035q02_probe_of (struct spi_device*) ; 
 int /*<<< orphan*/  lb035q02_timings ; 
 int /*<<< orphan*/  omap_dss_put_device (int /*<<< orphan*/ ) ; 
 int omapdss_register_display (struct omap_dss_device*) ; 

__attribute__((used)) static int lb035q02_panel_spi_probe(struct spi_device *spi)
{
	struct panel_drv_data *ddata;
	struct omap_dss_device *dssdev;
	int r;

	if (!spi->dev.of_node)
		return -ENODEV;

	ddata = devm_kzalloc(&spi->dev, sizeof(*ddata), GFP_KERNEL);
	if (ddata == NULL)
		return -ENOMEM;

	dev_set_drvdata(&spi->dev, ddata);

	ddata->spi = spi;

	r = lb035q02_probe_of(spi);
	if (r)
		return r;

	if (gpio_is_valid(ddata->backlight_gpio)) {
		r = devm_gpio_request_one(&spi->dev, ddata->backlight_gpio,
				GPIOF_OUT_INIT_LOW, "panel backlight");
		if (r)
			goto err_gpio;
	}

	ddata->videomode = lb035q02_timings;

	dssdev = &ddata->dssdev;
	dssdev->dev = &spi->dev;
	dssdev->driver = &lb035q02_ops;
	dssdev->type = OMAP_DISPLAY_TYPE_DPI;
	dssdev->owner = THIS_MODULE;
	dssdev->panel.timings = ddata->videomode;
	dssdev->phy.dpi.data_lines = ddata->data_lines;

	r = omapdss_register_display(dssdev);
	if (r) {
		dev_err(&spi->dev, "Failed to register panel\n");
		goto err_reg;
	}

	return 0;

err_reg:
err_gpio:
	omap_dss_put_device(ddata->in);
	return r;
}
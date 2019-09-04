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
struct spi_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  vm; } ;
struct omap_dss_device {TYPE_1__ panel; int /*<<< orphan*/  owner; int /*<<< orphan*/  type; int /*<<< orphan*/ * driver; int /*<<< orphan*/ * dev; } ;
struct panel_drv_data {int /*<<< orphan*/  vm; struct omap_dss_device dssdev; struct spi_device* spi; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  OMAP_DISPLAY_TYPE_DPI ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct panel_drv_data*) ; 
 struct panel_drv_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lb035q02_ops ; 
 int lb035q02_probe_of (struct spi_device*) ; 
 int /*<<< orphan*/  lb035q02_vm ; 
 int omapdss_register_display (struct omap_dss_device*) ; 

__attribute__((used)) static int lb035q02_panel_spi_probe(struct spi_device *spi)
{
	struct panel_drv_data *ddata;
	struct omap_dss_device *dssdev;
	int r;

	ddata = devm_kzalloc(&spi->dev, sizeof(*ddata), GFP_KERNEL);
	if (ddata == NULL)
		return -ENOMEM;

	dev_set_drvdata(&spi->dev, ddata);

	ddata->spi = spi;

	r = lb035q02_probe_of(spi);
	if (r)
		return r;

	ddata->vm = lb035q02_vm;

	dssdev = &ddata->dssdev;
	dssdev->dev = &spi->dev;
	dssdev->driver = &lb035q02_ops;
	dssdev->type = OMAP_DISPLAY_TYPE_DPI;
	dssdev->owner = THIS_MODULE;
	dssdev->panel.vm = ddata->vm;

	r = omapdss_register_display(dssdev);
	if (r) {
		dev_err(&spi->dev, "Failed to register panel\n");
		return r;
	}

	return 0;
}
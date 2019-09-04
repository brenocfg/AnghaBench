#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct panel_drv_data {int /*<<< orphan*/  spi_suspended; int /*<<< orphan*/  vm; struct omap_dss_device* in; } ;
struct TYPE_3__ {TYPE_2__* dpi; } ;
struct omap_dss_device {int /*<<< orphan*/  state; TYPE_1__ ops; } ;
struct TYPE_4__ {int (* enable ) (struct omap_dss_device*) ;int /*<<< orphan*/  (* disable ) (struct omap_dss_device*) ;int /*<<< orphan*/  (* set_timings ) (struct omap_dss_device*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  OMAP_DSS_DISPLAY_ACTIVE ; 
 int /*<<< orphan*/  omapdss_device_is_connected (struct omap_dss_device*) ; 
 scalar_t__ omapdss_device_is_enabled (struct omap_dss_device*) ; 
 int /*<<< orphan*/  stub1 (struct omap_dss_device*,int /*<<< orphan*/ *) ; 
 int stub2 (struct omap_dss_device*) ; 
 int /*<<< orphan*/  stub3 (struct omap_dss_device*) ; 
 struct panel_drv_data* to_panel_data (struct omap_dss_device*) ; 
 int tpo_td043_power_on (struct panel_drv_data*) ; 

__attribute__((used)) static int tpo_td043_enable(struct omap_dss_device *dssdev)
{
	struct panel_drv_data *ddata = to_panel_data(dssdev);
	struct omap_dss_device *in = ddata->in;
	int r;

	if (!omapdss_device_is_connected(dssdev))
		return -ENODEV;

	if (omapdss_device_is_enabled(dssdev))
		return 0;

	in->ops.dpi->set_timings(in, &ddata->vm);

	r = in->ops.dpi->enable(in);
	if (r)
		return r;

	/*
	 * If we are resuming from system suspend, SPI clocks might not be
	 * enabled yet, so we'll program the LCD from SPI PM resume callback.
	 */
	if (!ddata->spi_suspended) {
		r = tpo_td043_power_on(ddata);
		if (r) {
			in->ops.dpi->disable(in);
			return r;
		}
	}

	dssdev->state = OMAP_DSS_DISPLAY_ACTIVE;

	return 0;
}
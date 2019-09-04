#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct panel_drv_data {struct omap_dss_device* in; } ;
struct TYPE_5__ {TYPE_1__* dpi; } ;
struct omap_dss_device {TYPE_2__ ops; TYPE_3__* dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  of_node; } ;
struct TYPE_4__ {int (* connect ) (struct omap_dss_device*,struct omap_dss_device*) ;} ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct omap_dss_device*) ; 
 int PTR_ERR (struct omap_dss_device*) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  omap_dss_put_device (struct omap_dss_device*) ; 
 scalar_t__ omapdss_device_is_connected (struct omap_dss_device*) ; 
 struct omap_dss_device* omapdss_of_find_source_for_first_ep (int /*<<< orphan*/ ) ; 
 int stub1 (struct omap_dss_device*,struct omap_dss_device*) ; 
 struct panel_drv_data* to_panel_data (struct omap_dss_device*) ; 

__attribute__((used)) static int td028ttec1_panel_connect(struct omap_dss_device *dssdev)
{
	struct panel_drv_data *ddata = to_panel_data(dssdev);
	struct omap_dss_device *in;
	int r;

	if (omapdss_device_is_connected(dssdev))
		return 0;

	in = omapdss_of_find_source_for_first_ep(dssdev->dev->of_node);
	if (IS_ERR(in)) {
		dev_err(dssdev->dev, "failed to find video source\n");
		return PTR_ERR(in);
	}

	r = in->ops.dpi->connect(in, dssdev);
	if (r) {
		omap_dss_put_device(in);
		return r;
	}

	ddata->in = in;
	return 0;
}
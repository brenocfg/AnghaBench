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
struct panel_drv_data {int /*<<< orphan*/  channel; struct omap_dss_device* in; TYPE_1__* pdev; } ;
struct TYPE_6__ {TYPE_2__* dsi; } ;
struct omap_dss_device {TYPE_3__ ops; struct device* dev; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct TYPE_5__ {int (* connect ) (struct omap_dss_device*,struct omap_dss_device*) ;int (* request_vc ) (struct omap_dss_device*,int /*<<< orphan*/ *) ;int (* set_vc_id ) (struct omap_dss_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* disconnect ) (struct omap_dss_device*,struct omap_dss_device*) ;int /*<<< orphan*/  (* release_vc ) (struct omap_dss_device*,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {struct device dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct omap_dss_device*) ; 
 int PTR_ERR (struct omap_dss_device*) ; 
 int /*<<< orphan*/  TCH ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  omap_dss_put_device (struct omap_dss_device*) ; 
 scalar_t__ omapdss_device_is_connected (struct omap_dss_device*) ; 
 struct omap_dss_device* omapdss_of_find_source_for_first_ep (int /*<<< orphan*/ ) ; 
 int stub1 (struct omap_dss_device*,struct omap_dss_device*) ; 
 int stub2 (struct omap_dss_device*,int /*<<< orphan*/ *) ; 
 int stub3 (struct omap_dss_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct omap_dss_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (struct omap_dss_device*,struct omap_dss_device*) ; 
 struct panel_drv_data* to_panel_data (struct omap_dss_device*) ; 

__attribute__((used)) static int dsicm_connect(struct omap_dss_device *dssdev)
{
	struct panel_drv_data *ddata = to_panel_data(dssdev);
	struct device *dev = &ddata->pdev->dev;
	struct omap_dss_device *in;
	int r;

	if (omapdss_device_is_connected(dssdev))
		return 0;

	in = omapdss_of_find_source_for_first_ep(dssdev->dev->of_node);
	if (IS_ERR(in)) {
		dev_err(dssdev->dev, "failed to find video source\n");
		return PTR_ERR(in);
	}

	r = in->ops.dsi->connect(in, dssdev);
	if (r) {
		dev_err(dev, "Failed to connect to video source\n");
		goto err_connect;
	}

	r = in->ops.dsi->request_vc(in, &ddata->channel);
	if (r) {
		dev_err(dev, "failed to get virtual channel\n");
		goto err_req_vc;
	}

	r = in->ops.dsi->set_vc_id(in, ddata->channel, TCH);
	if (r) {
		dev_err(dev, "failed to set VC_ID\n");
		goto err_vc_id;
	}

	ddata->in = in;
	return 0;

err_vc_id:
	in->ops.dsi->release_vc(in, ddata->channel);
err_req_vc:
	in->ops.dsi->disconnect(in, dssdev);
err_connect:
	omap_dss_put_device(in);
	return r;
}
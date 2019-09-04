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
struct panel_drv_data {struct omap_dss_device* in; int /*<<< orphan*/  ls_oe_gpio; int /*<<< orphan*/  ct_cp_hpd_gpio; } ;
struct TYPE_5__ {TYPE_1__* hdmi; } ;
struct omap_dss_device {struct omap_dss_device* dst; struct omap_dss_device* src; TYPE_2__ ops; TYPE_3__* dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  of_node; } ;
struct TYPE_4__ {int (* connect ) (struct omap_dss_device*,struct omap_dss_device*) ;} ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct omap_dss_device*) ; 
 int PTR_ERR (struct omap_dss_device*) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  omap_dss_put_device (struct omap_dss_device*) ; 
 struct omap_dss_device* omapdss_of_find_source_for_first_ep (int /*<<< orphan*/ ) ; 
 int stub1 (struct omap_dss_device*,struct omap_dss_device*) ; 
 struct panel_drv_data* to_panel_data (struct omap_dss_device*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int tpd_connect(struct omap_dss_device *dssdev,
		struct omap_dss_device *dst)
{
	struct panel_drv_data *ddata = to_panel_data(dssdev);
	struct omap_dss_device *in;
	int r;

	in = omapdss_of_find_source_for_first_ep(dssdev->dev->of_node);
	if (IS_ERR(in)) {
		dev_err(dssdev->dev, "failed to find video source\n");
		return PTR_ERR(in);
	}

	r = in->ops.hdmi->connect(in, dssdev);
	if (r) {
		omap_dss_put_device(in);
		return r;
	}

	dst->src = dssdev;
	dssdev->dst = dst;

	gpiod_set_value_cansleep(ddata->ct_cp_hpd_gpio, 1);
	gpiod_set_value_cansleep(ddata->ls_oe_gpio, 1);

	/* DC-DC converter needs at max 300us to get to 90% of 5V */
	udelay(300);

	ddata->in = in;
	return 0;
}
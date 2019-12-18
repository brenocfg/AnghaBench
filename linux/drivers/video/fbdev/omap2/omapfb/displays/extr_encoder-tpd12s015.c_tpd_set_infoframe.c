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
struct panel_drv_data {struct omap_dss_device* in; } ;
struct TYPE_4__ {TYPE_1__* hdmi; } ;
struct omap_dss_device {TYPE_2__ ops; } ;
struct hdmi_avi_infoframe {int dummy; } ;
struct TYPE_3__ {int (* set_infoframe ) (struct omap_dss_device*,struct hdmi_avi_infoframe const*) ;} ;

/* Variables and functions */
 int stub1 (struct omap_dss_device*,struct hdmi_avi_infoframe const*) ; 
 struct panel_drv_data* to_panel_data (struct omap_dss_device*) ; 

__attribute__((used)) static int tpd_set_infoframe(struct omap_dss_device *dssdev,
		const struct hdmi_avi_infoframe *avi)
{
	struct panel_drv_data *ddata = to_panel_data(dssdev);
	struct omap_dss_device *in = ddata->in;

	return in->ops.hdmi->set_infoframe(in, avi);
}
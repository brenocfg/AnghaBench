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
typedef  int /*<<< orphan*/  u8 ;
struct panel_drv_data {int /*<<< orphan*/  ls_oe_gpio; int /*<<< orphan*/  hpd_gpio; struct omap_dss_device* in; } ;
struct TYPE_4__ {TYPE_1__* hdmi; } ;
struct omap_dss_device {TYPE_2__ ops; } ;
struct TYPE_3__ {int (* read_edid ) (struct omap_dss_device*,int /*<<< orphan*/ *,int) ;} ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  gpiod_get_value_cansleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 int stub1 (struct omap_dss_device*,int /*<<< orphan*/ *,int) ; 
 struct panel_drv_data* to_panel_data (struct omap_dss_device*) ; 

__attribute__((used)) static int tpd_read_edid(struct omap_dss_device *dssdev,
		u8 *edid, int len)
{
	struct panel_drv_data *ddata = to_panel_data(dssdev);
	struct omap_dss_device *in = ddata->in;
	int r;

	if (!gpiod_get_value_cansleep(ddata->hpd_gpio))
		return -ENODEV;

	gpiod_set_value_cansleep(ddata->ls_oe_gpio, 1);

	r = in->ops.hdmi->read_edid(in, edid, len);

	gpiod_set_value_cansleep(ddata->ls_oe_gpio, 0);

	return r;
}
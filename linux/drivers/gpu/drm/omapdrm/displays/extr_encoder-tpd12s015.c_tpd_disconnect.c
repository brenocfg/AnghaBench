#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct panel_drv_data {int /*<<< orphan*/  ls_oe_gpio; int /*<<< orphan*/  ct_cp_hpd_gpio; } ;
struct omap_dss_device {int /*<<< orphan*/  next; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omapdss_device_disconnect (struct omap_dss_device*,int /*<<< orphan*/ ) ; 
 struct panel_drv_data* to_panel_data (struct omap_dss_device*) ; 

__attribute__((used)) static void tpd_disconnect(struct omap_dss_device *src,
			   struct omap_dss_device *dst)
{
	struct panel_drv_data *ddata = to_panel_data(dst);

	gpiod_set_value_cansleep(ddata->ct_cp_hpd_gpio, 0);
	gpiod_set_value_cansleep(ddata->ls_oe_gpio, 0);

	omapdss_device_disconnect(dst, dst->next);
}
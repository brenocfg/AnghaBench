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
struct panel_drv_data {int /*<<< orphan*/  hpd_lock; int /*<<< orphan*/ * hpd_cb_data; int /*<<< orphan*/ * hpd_cb; int /*<<< orphan*/  hpd_gpio; struct omap_dss_device* in; } ;
struct TYPE_4__ {TYPE_1__* hdmi; } ;
struct omap_dss_device {TYPE_2__ ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* unregister_hpd_cb ) (struct omap_dss_device*) ;} ;

/* Variables and functions */
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct omap_dss_device*) ; 
 struct panel_drv_data* to_panel_data (struct omap_dss_device*) ; 

__attribute__((used)) static void hdmic_unregister_hpd_cb(struct omap_dss_device *dssdev)
{
	struct panel_drv_data *ddata = to_panel_data(dssdev);
	struct omap_dss_device *in = ddata->in;

	if (gpio_is_valid(ddata->hpd_gpio)) {
		mutex_lock(&ddata->hpd_lock);
		ddata->hpd_cb = NULL;
		ddata->hpd_cb_data = NULL;
		mutex_unlock(&ddata->hpd_lock);
	} else if (in->ops.hdmi->unregister_hpd_cb) {
		in->ops.hdmi->unregister_hpd_cb(in);
	}
}
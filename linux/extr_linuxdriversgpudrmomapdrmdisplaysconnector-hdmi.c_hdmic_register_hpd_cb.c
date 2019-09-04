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
struct panel_drv_data {void (* hpd_cb ) (void*,int) ;int /*<<< orphan*/  hpd_lock; void* hpd_cb_data; int /*<<< orphan*/  hpd_gpio; struct omap_dss_device* in; } ;
struct TYPE_4__ {TYPE_1__* hdmi; } ;
struct omap_dss_device {TYPE_2__ ops; } ;
struct TYPE_3__ {int (* register_hpd_cb ) (struct omap_dss_device*,void (*) (void*,int),void*) ;} ;

/* Variables and functions */
 int ENOTSUPP ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct omap_dss_device*,void (*) (void*,int),void*) ; 
 struct panel_drv_data* to_panel_data (struct omap_dss_device*) ; 

__attribute__((used)) static int hdmic_register_hpd_cb(struct omap_dss_device *dssdev,
				 void (*cb)(void *cb_data,
					    enum drm_connector_status status),
				 void *cb_data)
{
	struct panel_drv_data *ddata = to_panel_data(dssdev);
	struct omap_dss_device *in = ddata->in;

	if (gpio_is_valid(ddata->hpd_gpio)) {
		mutex_lock(&ddata->hpd_lock);
		ddata->hpd_cb = cb;
		ddata->hpd_cb_data = cb_data;
		mutex_unlock(&ddata->hpd_lock);
		return 0;
	} else if (in->ops.hdmi->register_hpd_cb) {
		return in->ops.hdmi->register_hpd_cb(in, cb, cb_data);
	}

	return -ENOTSUPP;
}
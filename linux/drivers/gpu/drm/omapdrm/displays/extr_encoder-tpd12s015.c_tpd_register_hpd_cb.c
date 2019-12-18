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
struct panel_drv_data {void (* hpd_cb ) (void*,int) ;int /*<<< orphan*/  hpd_lock; void* hpd_cb_data; } ;
struct omap_dss_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct panel_drv_data* to_panel_data (struct omap_dss_device*) ; 

__attribute__((used)) static void tpd_register_hpd_cb(struct omap_dss_device *dssdev,
				void (*cb)(void *cb_data,
					  enum drm_connector_status status),
				void *cb_data)
{
	struct panel_drv_data *ddata = to_panel_data(dssdev);

	mutex_lock(&ddata->hpd_lock);
	ddata->hpd_cb = cb;
	ddata->hpd_cb_data = cb_data;
	mutex_unlock(&ddata->hpd_lock);
}
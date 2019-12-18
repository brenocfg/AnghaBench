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
struct omap_dss_device {int dummy; } ;
struct dsi_data {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSDBG (char*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dsi_bus_is_locked (struct dsi_data*) ; 
 int /*<<< orphan*/  dsi_display_uninit_dsi (struct dsi_data*,int,int) ; 
 int /*<<< orphan*/  dsi_runtime_put (struct dsi_data*) ; 
 int /*<<< orphan*/  dsi_sync_vc (struct dsi_data*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct dsi_data* to_dsi_data (struct omap_dss_device*) ; 

__attribute__((used)) static void dsi_display_disable(struct omap_dss_device *dssdev,
		bool disconnect_lanes, bool enter_ulps)
{
	struct dsi_data *dsi = to_dsi_data(dssdev);

	DSSDBG("dsi_display_disable\n");

	WARN_ON(!dsi_bus_is_locked(dsi));

	mutex_lock(&dsi->lock);

	dsi_sync_vc(dsi, 0);
	dsi_sync_vc(dsi, 1);
	dsi_sync_vc(dsi, 2);
	dsi_sync_vc(dsi, 3);

	dsi_display_uninit_dsi(dsi, disconnect_lanes, enter_ulps);

	dsi_runtime_put(dsi);

	mutex_unlock(&dsi->lock);
}
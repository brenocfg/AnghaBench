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
 int /*<<< orphan*/  _dsi_initialize_irq (struct dsi_data*) ; 
 int /*<<< orphan*/  dsi_bus_is_locked (struct dsi_data*) ; 
 int dsi_display_init_dsi (struct dsi_data*) ; 
 int dsi_runtime_get (struct dsi_data*) ; 
 int /*<<< orphan*/  dsi_runtime_put (struct dsi_data*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct dsi_data* to_dsi_data (struct omap_dss_device*) ; 

__attribute__((used)) static void dsi_display_enable(struct omap_dss_device *dssdev)
{
	struct dsi_data *dsi = to_dsi_data(dssdev);
	int r;

	DSSDBG("dsi_display_enable\n");

	WARN_ON(!dsi_bus_is_locked(dsi));

	mutex_lock(&dsi->lock);

	r = dsi_runtime_get(dsi);
	if (r)
		goto err_get_dsi;

	_dsi_initialize_irq(dsi);

	r = dsi_display_init_dsi(dsi);
	if (r)
		goto err_init_dsi;

	mutex_unlock(&dsi->lock);

	return;

err_init_dsi:
	dsi_runtime_put(dsi);
err_get_dsi:
	mutex_unlock(&dsi->lock);
	DSSDBG("dsi_display_enable FAILED\n");
}
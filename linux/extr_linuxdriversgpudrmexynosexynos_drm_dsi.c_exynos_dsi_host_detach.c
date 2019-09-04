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
struct mipi_dsi_host {int dummy; } ;
struct mipi_dsi_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  status; struct drm_device* dev; } ;
struct exynos_dsi {TYPE_1__ connector; int /*<<< orphan*/ * panel; int /*<<< orphan*/  encoder; } ;
struct TYPE_4__ {scalar_t__ poll_enabled; int /*<<< orphan*/  mutex; } ;
struct drm_device {TYPE_2__ mode_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  connector_status_disconnected ; 
 int /*<<< orphan*/  drm_kms_helper_hotplug_event (struct drm_device*) ; 
 int /*<<< orphan*/  drm_panel_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exynos_dsi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exynos_dsi_unregister_te_irq (struct exynos_dsi*) ; 
 struct exynos_dsi* host_to_dsi (struct mipi_dsi_host*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int exynos_dsi_host_detach(struct mipi_dsi_host *host,
				  struct mipi_dsi_device *device)
{
	struct exynos_dsi *dsi = host_to_dsi(host);
	struct drm_device *drm = dsi->connector.dev;

	mutex_lock(&drm->mode_config.mutex);

	if (dsi->panel) {
		exynos_dsi_disable(&dsi->encoder);
		drm_panel_detach(dsi->panel);
		dsi->panel = NULL;
		dsi->connector.status = connector_status_disconnected;
	}

	mutex_unlock(&drm->mode_config.mutex);

	if (drm->mode_config.poll_enabled)
		drm_kms_helper_hotplug_event(drm);

	exynos_dsi_unregister_te_irq(dsi);

	return 0;
}
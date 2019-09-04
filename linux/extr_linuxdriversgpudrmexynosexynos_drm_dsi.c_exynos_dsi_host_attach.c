#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mipi_dsi_host {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  of_node; } ;
struct mipi_dsi_device {int mode_flags; TYPE_2__ dev; int /*<<< orphan*/  format; int /*<<< orphan*/  lanes; } ;
struct TYPE_8__ {int /*<<< orphan*/  status; struct drm_device* dev; } ;
struct exynos_dsi {int mode_flags; TYPE_4__ connector; int /*<<< orphan*/ * panel; int /*<<< orphan*/  format; int /*<<< orphan*/  lanes; } ;
struct TYPE_5__ {scalar_t__ poll_enabled; int /*<<< orphan*/  mutex; } ;
struct drm_device {TYPE_1__ mode_config; } ;
struct TYPE_7__ {int i80_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXYNOS_DISPLAY_TYPE_LCD ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int MIPI_DSI_MODE_VIDEO ; 
 int /*<<< orphan*/  connector_status_connected ; 
 int /*<<< orphan*/  drm_kms_helper_hotplug_event (struct drm_device*) ; 
 int /*<<< orphan*/  drm_panel_attach (int /*<<< orphan*/ *,TYPE_4__*) ; 
 TYPE_3__* exynos_drm_crtc_get_by_type (struct drm_device*,int /*<<< orphan*/ ) ; 
 int exynos_dsi_register_te_irq (struct exynos_dsi*,TYPE_2__*) ; 
 struct exynos_dsi* host_to_dsi (struct mipi_dsi_host*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * of_drm_find_panel (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int exynos_dsi_host_attach(struct mipi_dsi_host *host,
				  struct mipi_dsi_device *device)
{
	struct exynos_dsi *dsi = host_to_dsi(host);
	struct drm_device *drm = dsi->connector.dev;

	/*
	 * This is a temporary solution and should be made by more generic way.
	 *
	 * If attached panel device is for command mode one, dsi should register
	 * TE interrupt handler.
	 */
	if (!(device->mode_flags & MIPI_DSI_MODE_VIDEO)) {
		int ret = exynos_dsi_register_te_irq(dsi, &device->dev);
		if (ret)
			return ret;
	}

	mutex_lock(&drm->mode_config.mutex);

	dsi->lanes = device->lanes;
	dsi->format = device->format;
	dsi->mode_flags = device->mode_flags;
	dsi->panel = of_drm_find_panel(device->dev.of_node);
	if (IS_ERR(dsi->panel))
		dsi->panel = NULL;

	if (dsi->panel) {
		drm_panel_attach(dsi->panel, &dsi->connector);
		dsi->connector.status = connector_status_connected;
	}
	exynos_drm_crtc_get_by_type(drm, EXYNOS_DISPLAY_TYPE_LCD)->i80_mode =
			!(dsi->mode_flags & MIPI_DSI_MODE_VIDEO);

	mutex_unlock(&drm->mode_config.mutex);

	if (drm->mode_config.poll_enabled)
		drm_kms_helper_hotplug_event(drm);

	return 0;
}
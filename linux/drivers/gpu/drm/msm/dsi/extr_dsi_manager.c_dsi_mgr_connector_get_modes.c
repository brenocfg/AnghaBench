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
struct msm_dsi {struct drm_panel* panel; } ;
struct drm_panel {int dummy; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_panel_attach (struct drm_panel*,struct drm_connector*) ; 
 int drm_panel_get_modes (struct drm_panel*) ; 
 int dsi_mgr_connector_get_id (struct drm_connector*) ; 
 struct msm_dsi* dsi_mgr_get_dsi (int) ; 

__attribute__((used)) static int dsi_mgr_connector_get_modes(struct drm_connector *connector)
{
	int id = dsi_mgr_connector_get_id(connector);
	struct msm_dsi *msm_dsi = dsi_mgr_get_dsi(id);
	struct drm_panel *panel = msm_dsi->panel;
	int num;

	if (!panel)
		return 0;

	/*
	 * In dual DSI mode, we have one connector that can be
	 * attached to the drm_panel.
	 */
	drm_panel_attach(panel, connector);
	num = drm_panel_get_modes(panel);
	if (!num)
		return 0;

	return num;
}
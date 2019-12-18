#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct msm_kms {TYPE_3__* funcs; } ;
struct msm_dsi {struct drm_panel* panel; int /*<<< orphan*/  encoder; int /*<<< orphan*/  id; int /*<<< orphan*/  host; } ;
struct msm_drm_private {struct msm_kms* kms; } ;
struct drm_panel {int dummy; } ;
struct drm_connector {TYPE_2__* dev; int /*<<< orphan*/  base; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* set_split_display ) (struct msm_kms*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  tile_property; } ;
struct TYPE_5__ {TYPE_1__ mode_config; struct msm_drm_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ IS_DUAL_DSI () ; 
 scalar_t__ IS_ERR (struct drm_panel*) ; 
 int /*<<< orphan*/  IS_MASTER_DSI_LINK (int /*<<< orphan*/ ) ; 
 int PTR_ERR (struct drm_panel*) ; 
 int /*<<< orphan*/  drm_object_attach_property (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct msm_dsi* dsi_mgr_get_dsi (int /*<<< orphan*/ ) ; 
 struct msm_dsi* dsi_mgr_get_other_dsi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsi_mgr_is_cmd_mode (struct msm_dsi*) ; 
 struct drm_panel* msm_dsi_host_get_panel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct msm_kms*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int msm_dsi_manager_panel_init(struct drm_connector *conn, u8 id)
{
	struct msm_drm_private *priv = conn->dev->dev_private;
	struct msm_kms *kms = priv->kms;
	struct msm_dsi *msm_dsi = dsi_mgr_get_dsi(id);
	struct msm_dsi *other_dsi = dsi_mgr_get_other_dsi(id);
	struct msm_dsi *master_dsi, *slave_dsi;
	struct drm_panel *panel;

	if (IS_DUAL_DSI() && !IS_MASTER_DSI_LINK(id)) {
		master_dsi = other_dsi;
		slave_dsi = msm_dsi;
	} else {
		master_dsi = msm_dsi;
		slave_dsi = other_dsi;
	}

	/*
	 * There is only 1 panel in the global panel list for dual DSI mode.
	 * Therefore slave dsi should get the drm_panel instance from master
	 * dsi.
	 */
	panel = msm_dsi_host_get_panel(master_dsi->host);
	if (IS_ERR(panel)) {
		DRM_ERROR("Could not find panel for %u (%ld)\n", msm_dsi->id,
			  PTR_ERR(panel));
		return PTR_ERR(panel);
	}

	if (!panel || !IS_DUAL_DSI())
		goto out;

	drm_object_attach_property(&conn->base,
				   conn->dev->mode_config.tile_property, 0);

	/*
	 * Set split display info to kms once dual DSI panel is connected to
	 * both hosts.
	 */
	if (other_dsi && other_dsi->panel && kms->funcs->set_split_display) {
		kms->funcs->set_split_display(kms, master_dsi->encoder,
					      slave_dsi->encoder,
					      dsi_mgr_is_cmd_mode(msm_dsi));
	}

out:
	msm_dsi->panel = panel;
	return 0;
}
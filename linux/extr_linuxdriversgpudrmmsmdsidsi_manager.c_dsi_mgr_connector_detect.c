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
struct msm_kms {TYPE_3__* funcs; } ;
struct msm_dsi {int device_flags; void* panel; int /*<<< orphan*/  host; } ;
struct msm_drm_private {struct msm_kms* kms; } ;
struct drm_encoder {int dummy; } ;
struct drm_connector {TYPE_2__* dev; int /*<<< orphan*/  base; } ;
typedef  enum drm_connector_status { ____Placeholder_drm_connector_status } drm_connector_status ;
struct TYPE_6__ {int /*<<< orphan*/  (* set_split_display ) (struct msm_kms*,struct drm_encoder*,struct drm_encoder*,int) ;int /*<<< orphan*/  (* set_encoder_mode ) (struct msm_kms*,struct drm_encoder*,int) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  tile_property; } ;
struct TYPE_5__ {TYPE_1__ mode_config; struct msm_drm_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int) ; 
 int DSI_ENCODER_MASTER ; 
 int DSI_ENCODER_SLAVE ; 
 scalar_t__ IS_DUAL_DSI () ; 
 int /*<<< orphan*/  IS_MASTER_DSI_LINK (int) ; 
 int MIPI_DSI_MODE_VIDEO ; 
 int connector_status_connected ; 
 int connector_status_disconnected ; 
 int /*<<< orphan*/  drm_object_attach_property (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dsi_mgr_connector_get_id (struct drm_connector*) ; 
 struct msm_dsi* dsi_mgr_get_dsi (int) ; 
 struct msm_dsi* dsi_mgr_get_other_dsi (int) ; 
 struct drm_encoder* msm_dsi_get_encoder (struct msm_dsi*) ; 
 void* msm_dsi_host_get_panel (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  stub1 (struct msm_kms*,struct drm_encoder*,int) ; 
 int /*<<< orphan*/  stub2 (struct msm_kms*,struct drm_encoder*,struct drm_encoder*,int) ; 

__attribute__((used)) static enum drm_connector_status dsi_mgr_connector_detect(
		struct drm_connector *connector, bool force)
{
	int id = dsi_mgr_connector_get_id(connector);
	struct msm_dsi *msm_dsi = dsi_mgr_get_dsi(id);
	struct msm_dsi *other_dsi = dsi_mgr_get_other_dsi(id);
	struct msm_drm_private *priv = connector->dev->dev_private;
	struct msm_kms *kms = priv->kms;

	DBG("id=%d", id);
	if (!msm_dsi->panel) {
		msm_dsi->panel = msm_dsi_host_get_panel(msm_dsi->host,
						&msm_dsi->device_flags);

		/* There is only 1 panel in the global panel list
		 * for dual DSI mode. Therefore slave dsi should get
		 * the drm_panel instance from master dsi, and
		 * keep using the panel flags got from the current DSI link.
		 */
		if (!msm_dsi->panel && IS_DUAL_DSI() &&
			!IS_MASTER_DSI_LINK(id) && other_dsi)
			msm_dsi->panel = msm_dsi_host_get_panel(
					other_dsi->host, NULL);


		if (msm_dsi->panel && kms->funcs->set_encoder_mode) {
			bool cmd_mode = !(msm_dsi->device_flags &
					  MIPI_DSI_MODE_VIDEO);
			struct drm_encoder *encoder =
					msm_dsi_get_encoder(msm_dsi);

			kms->funcs->set_encoder_mode(kms, encoder, cmd_mode);
		}

		if (msm_dsi->panel && IS_DUAL_DSI())
			drm_object_attach_property(&connector->base,
				connector->dev->mode_config.tile_property, 0);

		/* Set split display info to kms once dual DSI panel is
		 * connected to both hosts.
		 */
		if (msm_dsi->panel && IS_DUAL_DSI() &&
			other_dsi && other_dsi->panel) {
			bool cmd_mode = !(msm_dsi->device_flags &
						MIPI_DSI_MODE_VIDEO);
			struct drm_encoder *encoder = msm_dsi_get_encoder(
					dsi_mgr_get_dsi(DSI_ENCODER_MASTER));
			struct drm_encoder *slave_enc = msm_dsi_get_encoder(
					dsi_mgr_get_dsi(DSI_ENCODER_SLAVE));

			if (kms->funcs->set_split_display)
				kms->funcs->set_split_display(kms, encoder,
							slave_enc, cmd_mode);
			else
				pr_err("mdp does not support dual DSI\n");
		}
	}

	return msm_dsi->panel ? connector_status_connected :
		connector_status_disconnected;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct msm_kms {TYPE_1__* funcs; } ;
struct msm_dsi {struct drm_device* dev; } ;
struct msm_drm_private {struct msm_kms* kms; } ;
struct drm_encoder {int dummy; } ;
struct drm_device {struct msm_drm_private* dev_private; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_encoder_mode ) (struct msm_kms*,struct drm_encoder*,int) ;} ;

/* Variables and functions */
 int MIPI_DSI_MODE_VIDEO ; 
 struct msm_dsi* dsi_mgr_get_dsi (int) ; 
 struct drm_encoder* msm_dsi_get_encoder (struct msm_dsi*) ; 
 int /*<<< orphan*/  stub1 (struct msm_kms*,struct drm_encoder*,int) ; 

void msm_dsi_manager_attach_dsi_device(int id, u32 device_flags)
{
	struct msm_dsi *msm_dsi = dsi_mgr_get_dsi(id);
	struct drm_device *dev = msm_dsi->dev;
	struct msm_drm_private *priv;
	struct msm_kms *kms;
	struct drm_encoder *encoder;
	bool cmd_mode;

	/*
	 * drm_device pointer is assigned to msm_dsi only in the modeset_init
	 * path. If mipi_dsi_attach() happens in DSI driver's probe path
	 * (generally the case when we're connected to a drm_panel of the type
	 * mipi_dsi_device), this would be NULL. In such cases, try to set the
	 * encoder mode in the DSI connector's detect() op.
	 */
	if (!dev)
		return;

	priv = dev->dev_private;
	kms = priv->kms;
	encoder = msm_dsi_get_encoder(msm_dsi);
	cmd_mode = !(device_flags &
				 MIPI_DSI_MODE_VIDEO);

	if (encoder && kms->funcs->set_encoder_mode)
		kms->funcs->set_encoder_mode(kms, encoder, cmd_mode);
}
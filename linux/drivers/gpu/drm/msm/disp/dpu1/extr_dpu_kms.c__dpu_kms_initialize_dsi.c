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
struct msm_drm_private {scalar_t__* dsi; int /*<<< orphan*/  num_encoders; struct drm_encoder** encoders; } ;
struct drm_encoder {int dummy; } ;
struct drm_device {int dummy; } ;
struct dpu_kms {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 
 int /*<<< orphan*/  DPU_ERROR (char*,...) ; 
 int /*<<< orphan*/  DRM_MODE_ENCODER_DSI ; 
 scalar_t__ IS_ERR (struct drm_encoder*) ; 
 int PTR_ERR (struct drm_encoder*) ; 
 struct drm_encoder* dpu_encoder_init (struct drm_device*,int /*<<< orphan*/ ) ; 
 int msm_dsi_modeset_init (scalar_t__,struct drm_device*,struct drm_encoder*) ; 

__attribute__((used)) static int _dpu_kms_initialize_dsi(struct drm_device *dev,
				    struct msm_drm_private *priv,
				    struct dpu_kms *dpu_kms)
{
	struct drm_encoder *encoder = NULL;
	int i, rc = 0;

	if (!(priv->dsi[0] || priv->dsi[1]))
		return rc;

	/*TODO: Support two independent DSI connectors */
	encoder = dpu_encoder_init(dev, DRM_MODE_ENCODER_DSI);
	if (IS_ERR(encoder)) {
		DPU_ERROR("encoder init failed for dsi display\n");
		return PTR_ERR(encoder);
	}

	priv->encoders[priv->num_encoders++] = encoder;

	for (i = 0; i < ARRAY_SIZE(priv->dsi); i++) {
		if (!priv->dsi[i])
			continue;

		rc = msm_dsi_modeset_init(priv->dsi[i], dev, encoder);
		if (rc) {
			DPU_ERROR("modeset_init failed for dsi[%d], rc = %d\n",
				i, rc);
			break;
		}
	}

	return rc;
}
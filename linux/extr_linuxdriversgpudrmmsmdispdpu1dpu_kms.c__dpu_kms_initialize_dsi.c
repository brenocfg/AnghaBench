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
struct msm_drm_private {int /*<<< orphan*/ * dsi; int /*<<< orphan*/  num_encoders; struct drm_encoder** encoders; } ;
struct drm_encoder {int dummy; } ;
struct drm_device {int dummy; } ;
struct dpu_kms {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DPU_DEBUG (char*,int) ; 
 int /*<<< orphan*/  DPU_ERROR (char*,...) ; 
 int /*<<< orphan*/  DRM_MODE_ENCODER_DSI ; 
 scalar_t__ IS_ERR_OR_NULL (struct drm_encoder*) ; 
 struct drm_encoder* dpu_encoder_init (struct drm_device*,int /*<<< orphan*/ ) ; 
 int msm_dsi_modeset_init (int /*<<< orphan*/ ,struct drm_device*,struct drm_encoder*) ; 

__attribute__((used)) static void _dpu_kms_initialize_dsi(struct drm_device *dev,
				    struct msm_drm_private *priv,
				    struct dpu_kms *dpu_kms)
{
	struct drm_encoder *encoder = NULL;
	int i, rc;

	/*TODO: Support two independent DSI connectors */
	encoder = dpu_encoder_init(dev, DRM_MODE_ENCODER_DSI);
	if (IS_ERR_OR_NULL(encoder)) {
		DPU_ERROR("encoder init failed for dsi display\n");
		return;
	}

	priv->encoders[priv->num_encoders++] = encoder;

	for (i = 0; i < ARRAY_SIZE(priv->dsi); i++) {
		if (!priv->dsi[i]) {
			DPU_DEBUG("invalid msm_dsi for ctrl %d\n", i);
			return;
		}

		rc = msm_dsi_modeset_init(priv->dsi[i], dev, encoder);
		if (rc) {
			DPU_ERROR("modeset_init failed for dsi[%d], rc = %d\n",
				i, rc);
			continue;
		}
	}
}
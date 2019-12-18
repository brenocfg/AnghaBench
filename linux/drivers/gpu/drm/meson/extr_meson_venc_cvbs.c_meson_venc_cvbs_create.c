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
struct drm_connector {int interlace_allowed; } ;
struct drm_encoder {int /*<<< orphan*/  possible_crtcs; } ;
struct meson_venc_cvbs {struct drm_connector connector; struct drm_encoder encoder; struct meson_drm* priv; } ;
struct meson_drm {int /*<<< orphan*/  dev; struct drm_device* drm; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_Composite ; 
 int /*<<< orphan*/  DRM_MODE_ENCODER_TVDAC ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 struct meson_venc_cvbs* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_connector_attach_encoder (struct drm_connector*,struct drm_encoder*) ; 
 int /*<<< orphan*/  drm_connector_helper_add (struct drm_connector*,int /*<<< orphan*/ *) ; 
 int drm_connector_init (struct drm_device*,struct drm_connector*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_encoder_helper_add (struct drm_encoder*,int /*<<< orphan*/ *) ; 
 int drm_encoder_init (struct drm_device*,struct drm_encoder*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  meson_cvbs_connector_funcs ; 
 int /*<<< orphan*/  meson_cvbs_connector_helper_funcs ; 
 int /*<<< orphan*/  meson_venc_cvbs_connector_is_available (struct meson_drm*) ; 
 int /*<<< orphan*/  meson_venc_cvbs_encoder_funcs ; 
 int /*<<< orphan*/  meson_venc_cvbs_encoder_helper_funcs ; 

int meson_venc_cvbs_create(struct meson_drm *priv)
{
	struct drm_device *drm = priv->drm;
	struct meson_venc_cvbs *meson_venc_cvbs;
	struct drm_connector *connector;
	struct drm_encoder *encoder;
	int ret;

	if (!meson_venc_cvbs_connector_is_available(priv)) {
		dev_info(drm->dev, "CVBS Output connector not available\n");
		return 0;
	}

	meson_venc_cvbs = devm_kzalloc(priv->dev, sizeof(*meson_venc_cvbs),
				       GFP_KERNEL);
	if (!meson_venc_cvbs)
		return -ENOMEM;

	meson_venc_cvbs->priv = priv;
	encoder = &meson_venc_cvbs->encoder;
	connector = &meson_venc_cvbs->connector;

	/* Connector */

	drm_connector_helper_add(connector,
				 &meson_cvbs_connector_helper_funcs);

	ret = drm_connector_init(drm, connector, &meson_cvbs_connector_funcs,
				 DRM_MODE_CONNECTOR_Composite);
	if (ret) {
		dev_err(priv->dev, "Failed to init CVBS connector\n");
		return ret;
	}

	connector->interlace_allowed = 1;

	/* Encoder */

	drm_encoder_helper_add(encoder, &meson_venc_cvbs_encoder_helper_funcs);

	ret = drm_encoder_init(drm, encoder, &meson_venc_cvbs_encoder_funcs,
			       DRM_MODE_ENCODER_TVDAC, "meson_venc_cvbs");
	if (ret) {
		dev_err(priv->dev, "Failed to init CVBS encoder\n");
		return ret;
	}

	encoder->possible_crtcs = BIT(0);

	drm_connector_attach_encoder(connector, encoder);

	return 0;
}
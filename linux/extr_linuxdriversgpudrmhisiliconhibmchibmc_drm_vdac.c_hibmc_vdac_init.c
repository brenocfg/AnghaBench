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
struct hibmc_drm_private {struct drm_device* dev; } ;
struct drm_encoder {int possible_crtcs; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int /*<<< orphan*/  DRM_MODE_ENCODER_DAC ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct drm_connector*) ; 
 int PTR_ERR (struct drm_connector*) ; 
 struct drm_encoder* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_connector_attach_encoder (struct drm_connector*,struct drm_encoder*) ; 
 int /*<<< orphan*/  drm_encoder_helper_add (struct drm_encoder*,int /*<<< orphan*/ *) ; 
 int drm_encoder_init (struct drm_device*,struct drm_encoder*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct drm_connector* hibmc_connector_init (struct hibmc_drm_private*) ; 
 int /*<<< orphan*/  hibmc_encoder_funcs ; 
 int /*<<< orphan*/  hibmc_encoder_helper_funcs ; 

int hibmc_vdac_init(struct hibmc_drm_private *priv)
{
	struct drm_device *dev = priv->dev;
	struct drm_encoder *encoder;
	struct drm_connector *connector;
	int ret;

	connector = hibmc_connector_init(priv);
	if (IS_ERR(connector)) {
		DRM_ERROR("failed to create connector: %ld\n",
			  PTR_ERR(connector));
		return PTR_ERR(connector);
	}

	encoder = devm_kzalloc(dev->dev, sizeof(*encoder), GFP_KERNEL);
	if (!encoder) {
		DRM_ERROR("failed to alloc memory when init encoder\n");
		return -ENOMEM;
	}

	encoder->possible_crtcs = 0x1;
	ret = drm_encoder_init(dev, encoder, &hibmc_encoder_funcs,
			       DRM_MODE_ENCODER_DAC, NULL);
	if (ret) {
		DRM_ERROR("failed to init encoder: %d\n", ret);
		return ret;
	}

	drm_encoder_helper_add(encoder, &hibmc_encoder_helper_funcs);
	drm_connector_attach_encoder(connector, encoder);

	return 0;
}
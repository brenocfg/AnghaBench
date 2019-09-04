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
struct drm_encoder {int possible_crtcs; scalar_t__ possible_clones; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;
struct drm_connector {int dummy; } ;
struct device_node {int dummy; } ;
struct arcpgu_drm_connector {struct drm_connector connector; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_VIRTUAL ; 
 int /*<<< orphan*/  DRM_MODE_ENCODER_VIRTUAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  arcpgu_drm_connector_funcs ; 
 int /*<<< orphan*/  arcpgu_drm_connector_helper_funcs ; 
 int /*<<< orphan*/  arcpgu_drm_encoder_funcs ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 void* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int drm_connector_attach_encoder (struct drm_connector*,struct drm_encoder*) ; 
 int /*<<< orphan*/  drm_connector_cleanup (struct drm_connector*) ; 
 int /*<<< orphan*/  drm_connector_helper_add (struct drm_connector*,int /*<<< orphan*/ *) ; 
 int drm_connector_init (struct drm_device*,struct drm_connector*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_connector_unregister (struct drm_connector*) ; 
 int /*<<< orphan*/  drm_encoder_cleanup (struct drm_encoder*) ; 
 int drm_encoder_init (struct drm_device*,struct drm_encoder*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int arcpgu_drm_sim_init(struct drm_device *drm, struct device_node *np)
{
	struct arcpgu_drm_connector *arcpgu_connector;
	struct drm_encoder *encoder;
	struct drm_connector *connector;
	int ret;

	encoder = devm_kzalloc(drm->dev, sizeof(*encoder), GFP_KERNEL);
	if (encoder == NULL)
		return -ENOMEM;

	encoder->possible_crtcs = 1;
	encoder->possible_clones = 0;

	ret = drm_encoder_init(drm, encoder, &arcpgu_drm_encoder_funcs,
			       DRM_MODE_ENCODER_VIRTUAL, NULL);
	if (ret)
		return ret;

	arcpgu_connector = devm_kzalloc(drm->dev, sizeof(*arcpgu_connector),
					GFP_KERNEL);
	if (!arcpgu_connector) {
		ret = -ENOMEM;
		goto error_encoder_cleanup;
	}

	connector = &arcpgu_connector->connector;
	drm_connector_helper_add(connector, &arcpgu_drm_connector_helper_funcs);

	ret = drm_connector_init(drm, connector, &arcpgu_drm_connector_funcs,
			DRM_MODE_CONNECTOR_VIRTUAL);
	if (ret < 0) {
		dev_err(drm->dev, "failed to initialize drm connector\n");
		goto error_encoder_cleanup;
	}

	ret = drm_connector_attach_encoder(connector, encoder);
	if (ret < 0) {
		dev_err(drm->dev, "could not attach connector to encoder\n");
		drm_connector_unregister(connector);
		goto error_connector_cleanup;
	}

	return 0;

error_connector_cleanup:
	drm_connector_cleanup(connector);

error_encoder_cleanup:
	drm_encoder_cleanup(encoder);
	return ret;
}
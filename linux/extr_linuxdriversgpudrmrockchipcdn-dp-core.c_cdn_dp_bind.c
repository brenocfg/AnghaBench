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
struct drm_encoder {int /*<<< orphan*/  possible_crtcs; } ;
struct drm_device {int dummy; } ;
struct drm_connector {int /*<<< orphan*/  dpms; int /*<<< orphan*/  polled; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct TYPE_2__ {int /*<<< orphan*/  notifier_call; } ;
struct cdn_dp_port {TYPE_1__ event_nb; int /*<<< orphan*/  extcon; } ;
struct cdn_dp_device {int connected; int active; int active_port; int fw_loaded; int ports; int /*<<< orphan*/  event_work; int /*<<< orphan*/  dev; struct cdn_dp_port** port; struct drm_connector connector; struct drm_encoder encoder; struct drm_device* drm_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_CONNECTOR_POLL_HPD ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (struct device*,char*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_DisplayPort ; 
 int /*<<< orphan*/  DRM_MODE_DPMS_OFF ; 
 int /*<<< orphan*/  DRM_MODE_ENCODER_TMDS ; 
 int /*<<< orphan*/  EXTCON_DISP_DP ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdn_dp_atomic_connector_funcs ; 
 int /*<<< orphan*/  cdn_dp_connector_helper_funcs ; 
 int /*<<< orphan*/  cdn_dp_encoder_funcs ; 
 int /*<<< orphan*/  cdn_dp_encoder_helper_funcs ; 
 int cdn_dp_parse_dt (struct cdn_dp_device*) ; 
 int /*<<< orphan*/  cdn_dp_pd_event ; 
 int /*<<< orphan*/  cdn_dp_pd_event_work ; 
 struct cdn_dp_device* dev_get_drvdata (struct device*) ; 
 int devm_extcon_register_notifier (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int drm_connector_attach_encoder (struct drm_connector*,struct drm_encoder*) ; 
 int /*<<< orphan*/  drm_connector_cleanup (struct drm_connector*) ; 
 int /*<<< orphan*/  drm_connector_helper_add (struct drm_connector*,int /*<<< orphan*/ *) ; 
 int drm_connector_init (struct drm_device*,struct drm_connector*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_encoder_cleanup (struct drm_encoder*) ; 
 int /*<<< orphan*/  drm_encoder_helper_add (struct drm_encoder*,int /*<<< orphan*/ *) ; 
 int drm_encoder_init (struct drm_device*,struct drm_encoder*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_of_find_possible_crtcs (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cdn_dp_bind(struct device *dev, struct device *master, void *data)
{
	struct cdn_dp_device *dp = dev_get_drvdata(dev);
	struct drm_encoder *encoder;
	struct drm_connector *connector;
	struct cdn_dp_port *port;
	struct drm_device *drm_dev = data;
	int ret, i;

	ret = cdn_dp_parse_dt(dp);
	if (ret < 0)
		return ret;

	dp->drm_dev = drm_dev;
	dp->connected = false;
	dp->active = false;
	dp->active_port = -1;
	dp->fw_loaded = false;

	INIT_WORK(&dp->event_work, cdn_dp_pd_event_work);

	encoder = &dp->encoder;

	encoder->possible_crtcs = drm_of_find_possible_crtcs(drm_dev,
							     dev->of_node);
	DRM_DEBUG_KMS("possible_crtcs = 0x%x\n", encoder->possible_crtcs);

	ret = drm_encoder_init(drm_dev, encoder, &cdn_dp_encoder_funcs,
			       DRM_MODE_ENCODER_TMDS, NULL);
	if (ret) {
		DRM_ERROR("failed to initialize encoder with drm\n");
		return ret;
	}

	drm_encoder_helper_add(encoder, &cdn_dp_encoder_helper_funcs);

	connector = &dp->connector;
	connector->polled = DRM_CONNECTOR_POLL_HPD;
	connector->dpms = DRM_MODE_DPMS_OFF;

	ret = drm_connector_init(drm_dev, connector,
				 &cdn_dp_atomic_connector_funcs,
				 DRM_MODE_CONNECTOR_DisplayPort);
	if (ret) {
		DRM_ERROR("failed to initialize connector with drm\n");
		goto err_free_encoder;
	}

	drm_connector_helper_add(connector, &cdn_dp_connector_helper_funcs);

	ret = drm_connector_attach_encoder(connector, encoder);
	if (ret) {
		DRM_ERROR("failed to attach connector and encoder\n");
		goto err_free_connector;
	}

	for (i = 0; i < dp->ports; i++) {
		port = dp->port[i];

		port->event_nb.notifier_call = cdn_dp_pd_event;
		ret = devm_extcon_register_notifier(dp->dev, port->extcon,
						    EXTCON_DISP_DP,
						    &port->event_nb);
		if (ret) {
			DRM_DEV_ERROR(dev,
				      "register EXTCON_DISP_DP notifier err\n");
			goto err_free_connector;
		}
	}

	pm_runtime_enable(dev);

	schedule_work(&dp->event_work);

	return 0;

err_free_connector:
	drm_connector_cleanup(connector);
err_free_encoder:
	drm_encoder_cleanup(encoder);
	return ret;
}
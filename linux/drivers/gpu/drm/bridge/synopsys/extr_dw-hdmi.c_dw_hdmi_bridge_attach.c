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
struct drm_connector {int interlace_allowed; int /*<<< orphan*/  polled; } ;
struct dw_hdmi {int /*<<< orphan*/  cec_notifier_mutex; struct cec_notifier* cec_notifier; int /*<<< orphan*/  dev; int /*<<< orphan*/  ddc; struct drm_connector connector; } ;
struct drm_encoder {int dummy; } ;
struct drm_bridge {int /*<<< orphan*/  dev; struct drm_encoder* encoder; struct dw_hdmi* driver_private; } ;
struct cec_notifier {int dummy; } ;
struct cec_connector_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_CONNECTOR_POLL_HPD ; 
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_HDMIA ; 
 int ENOMEM ; 
 int /*<<< orphan*/  cec_fill_conn_info_from_drm (struct cec_connector_info*,struct drm_connector*) ; 
 struct cec_notifier* cec_notifier_conn_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct cec_connector_info*) ; 
 int /*<<< orphan*/  drm_connector_attach_encoder (struct drm_connector*,struct drm_encoder*) ; 
 int /*<<< orphan*/  drm_connector_helper_add (struct drm_connector*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_connector_init_with_ddc (int /*<<< orphan*/ ,struct drm_connector*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dw_hdmi_connector_funcs ; 
 int /*<<< orphan*/  dw_hdmi_connector_helper_funcs ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dw_hdmi_bridge_attach(struct drm_bridge *bridge)
{
	struct dw_hdmi *hdmi = bridge->driver_private;
	struct drm_encoder *encoder = bridge->encoder;
	struct drm_connector *connector = &hdmi->connector;
	struct cec_connector_info conn_info;
	struct cec_notifier *notifier;

	connector->interlace_allowed = 1;
	connector->polled = DRM_CONNECTOR_POLL_HPD;

	drm_connector_helper_add(connector, &dw_hdmi_connector_helper_funcs);

	drm_connector_init_with_ddc(bridge->dev, connector,
				    &dw_hdmi_connector_funcs,
				    DRM_MODE_CONNECTOR_HDMIA,
				    hdmi->ddc);

	drm_connector_attach_encoder(connector, encoder);

	cec_fill_conn_info_from_drm(&conn_info, connector);

	notifier = cec_notifier_conn_register(hdmi->dev, NULL, &conn_info);
	if (!notifier)
		return -ENOMEM;

	mutex_lock(&hdmi->cec_notifier_mutex);
	hdmi->cec_notifier = notifier;
	mutex_unlock(&hdmi->cec_notifier_mutex);

	return 0;
}
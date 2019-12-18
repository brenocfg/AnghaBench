#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int interlace_allowed; int doublescan_allowed; int /*<<< orphan*/  polled; } ;
struct mtk_hdmi {int /*<<< orphan*/  dev; int /*<<< orphan*/  cec_dev; scalar_t__ next_bridge; TYPE_1__ conn; } ;
struct drm_bridge {TYPE_4__* encoder; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_CONNECTOR_POLL_HPD ; 
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_HDMIA ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int drm_bridge_attach (TYPE_4__*,scalar_t__,struct drm_bridge*) ; 
 int drm_connector_attach_encoder (TYPE_1__*,TYPE_4__*) ; 
 int /*<<< orphan*/  drm_connector_helper_add (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int drm_connector_init (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct mtk_hdmi* hdmi_ctx_from_bridge (struct drm_bridge*) ; 
 int /*<<< orphan*/  mtk_cec_set_hpd_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_hdmi_connector_funcs ; 
 int /*<<< orphan*/  mtk_hdmi_connector_helper_funcs ; 
 int /*<<< orphan*/  mtk_hdmi_hpd_event ; 

__attribute__((used)) static int mtk_hdmi_bridge_attach(struct drm_bridge *bridge)
{
	struct mtk_hdmi *hdmi = hdmi_ctx_from_bridge(bridge);
	int ret;

	ret = drm_connector_init(bridge->encoder->dev, &hdmi->conn,
				 &mtk_hdmi_connector_funcs,
				 DRM_MODE_CONNECTOR_HDMIA);
	if (ret) {
		dev_err(hdmi->dev, "Failed to initialize connector: %d\n", ret);
		return ret;
	}
	drm_connector_helper_add(&hdmi->conn, &mtk_hdmi_connector_helper_funcs);

	hdmi->conn.polled = DRM_CONNECTOR_POLL_HPD;
	hdmi->conn.interlace_allowed = true;
	hdmi->conn.doublescan_allowed = false;

	ret = drm_connector_attach_encoder(&hdmi->conn,
						bridge->encoder);
	if (ret) {
		dev_err(hdmi->dev,
			"Failed to attach connector to encoder: %d\n", ret);
		return ret;
	}

	if (hdmi->next_bridge) {
		ret = drm_bridge_attach(bridge->encoder, hdmi->next_bridge,
					bridge);
		if (ret) {
			dev_err(hdmi->dev,
				"Failed to attach external bridge: %d\n", ret);
			return ret;
		}
	}

	mtk_cec_set_hpd_event(hdmi->cec_dev, mtk_hdmi_hpd_event, hdmi->dev);

	return 0;
}
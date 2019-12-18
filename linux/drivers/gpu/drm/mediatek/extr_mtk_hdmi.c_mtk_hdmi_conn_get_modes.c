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
struct mtk_hdmi {int dvi_mode; int /*<<< orphan*/  ddc_adpt; } ;
struct edid {int dummy; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int drm_add_edid_modes (struct drm_connector*,struct edid*) ; 
 int /*<<< orphan*/  drm_connector_update_edid_property (struct drm_connector*,struct edid*) ; 
 int /*<<< orphan*/  drm_detect_monitor_audio (struct edid*) ; 
 struct edid* drm_get_edid (struct drm_connector*,int /*<<< orphan*/ ) ; 
 struct mtk_hdmi* hdmi_ctx_from_conn (struct drm_connector*) ; 
 int /*<<< orphan*/  kfree (struct edid*) ; 

__attribute__((used)) static int mtk_hdmi_conn_get_modes(struct drm_connector *conn)
{
	struct mtk_hdmi *hdmi = hdmi_ctx_from_conn(conn);
	struct edid *edid;
	int ret;

	if (!hdmi->ddc_adpt)
		return -ENODEV;

	edid = drm_get_edid(conn, hdmi->ddc_adpt);
	if (!edid)
		return -ENODEV;

	hdmi->dvi_mode = !drm_detect_monitor_audio(edid);

	drm_connector_update_edid_property(conn, edid);

	ret = drm_add_edid_modes(conn, edid);
	kfree(edid);
	return ret;
}
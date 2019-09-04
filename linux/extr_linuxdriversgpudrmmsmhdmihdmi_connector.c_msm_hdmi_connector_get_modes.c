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
typedef  int uint32_t ;
struct hdmi_connector {struct hdmi* hdmi; } ;
struct hdmi {int /*<<< orphan*/  hdmi_mode; int /*<<< orphan*/  i2c; } ;
struct edid {int dummy; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 int HDMI_CTRL_ENABLE ; 
 int /*<<< orphan*/  REG_HDMI_CTRL ; 
 int drm_add_edid_modes (struct drm_connector*,struct edid*) ; 
 int /*<<< orphan*/  drm_connector_update_edid_property (struct drm_connector*,struct edid*) ; 
 int /*<<< orphan*/  drm_detect_hdmi_monitor (struct edid*) ; 
 struct edid* drm_get_edid (struct drm_connector*,int /*<<< orphan*/ ) ; 
 int hdmi_read (struct hdmi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdmi_write (struct hdmi*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree (struct edid*) ; 
 struct hdmi_connector* to_hdmi_connector (struct drm_connector*) ; 

__attribute__((used)) static int msm_hdmi_connector_get_modes(struct drm_connector *connector)
{
	struct hdmi_connector *hdmi_connector = to_hdmi_connector(connector);
	struct hdmi *hdmi = hdmi_connector->hdmi;
	struct edid *edid;
	uint32_t hdmi_ctrl;
	int ret = 0;

	hdmi_ctrl = hdmi_read(hdmi, REG_HDMI_CTRL);
	hdmi_write(hdmi, REG_HDMI_CTRL, hdmi_ctrl | HDMI_CTRL_ENABLE);

	edid = drm_get_edid(connector, hdmi->i2c);

	hdmi_write(hdmi, REG_HDMI_CTRL, hdmi_ctrl);

	hdmi->hdmi_mode = drm_detect_hdmi_monitor(edid);
	drm_connector_update_edid_property(connector, edid);

	if (edid) {
		ret = drm_add_edid_modes(connector, edid);
		kfree(edid);
	}

	return ret;
}
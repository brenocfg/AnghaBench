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
struct drm_connector {int polled; scalar_t__ doublescan_allowed; scalar_t__ interlace_allowed; } ;
struct hdmi_connector {struct drm_connector base; int /*<<< orphan*/  hpd_work; struct hdmi* hdmi; } ;
struct hdmi {int /*<<< orphan*/  encoder; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DRM_CONNECTOR_POLL_CONNECT ; 
 int DRM_CONNECTOR_POLL_DISCONNECT ; 
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_HDMIA ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct drm_connector* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_connector_attach_encoder (struct drm_connector*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_connector_helper_add (struct drm_connector*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_connector_init (int /*<<< orphan*/ ,struct drm_connector*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdmi_connector_funcs ; 
 struct hdmi_connector* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msm_hdmi_connector_helper_funcs ; 
 int /*<<< orphan*/  msm_hdmi_hotplug_work ; 

struct drm_connector *msm_hdmi_connector_init(struct hdmi *hdmi)
{
	struct drm_connector *connector = NULL;
	struct hdmi_connector *hdmi_connector;

	hdmi_connector = kzalloc(sizeof(*hdmi_connector), GFP_KERNEL);
	if (!hdmi_connector)
		return ERR_PTR(-ENOMEM);

	hdmi_connector->hdmi = hdmi;
	INIT_WORK(&hdmi_connector->hpd_work, msm_hdmi_hotplug_work);

	connector = &hdmi_connector->base;

	drm_connector_init(hdmi->dev, connector, &hdmi_connector_funcs,
			DRM_MODE_CONNECTOR_HDMIA);
	drm_connector_helper_add(connector, &msm_hdmi_connector_helper_funcs);

	connector->polled = DRM_CONNECTOR_POLL_CONNECT |
			DRM_CONNECTOR_POLL_DISCONNECT;

	connector->interlace_allowed = 0;
	connector->doublescan_allowed = 0;

	drm_connector_attach_encoder(connector, hdmi->encoder);

	return connector;
}
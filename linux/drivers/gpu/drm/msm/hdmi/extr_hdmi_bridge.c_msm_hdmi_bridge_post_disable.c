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
struct hdmi_phy {int dummy; } ;
struct hdmi_bridge {struct hdmi* hdmi; } ;
struct hdmi {int power_on; scalar_t__ hdmi_mode; scalar_t__ hdcp_ctrl; struct hdmi_phy* phy; } ;
struct drm_bridge {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
 int /*<<< orphan*/  msm_hdmi_audio_update (struct hdmi*) ; 
 int /*<<< orphan*/  msm_hdmi_hdcp_off (scalar_t__) ; 
 int /*<<< orphan*/  msm_hdmi_phy_powerdown (struct hdmi_phy*) ; 
 int /*<<< orphan*/  msm_hdmi_phy_resource_disable (struct hdmi_phy*) ; 
 int /*<<< orphan*/  msm_hdmi_set_mode (struct hdmi*,int) ; 
 int /*<<< orphan*/  power_off (struct drm_bridge*) ; 
 struct hdmi_bridge* to_hdmi_bridge (struct drm_bridge*) ; 

__attribute__((used)) static void msm_hdmi_bridge_post_disable(struct drm_bridge *bridge)
{
	struct hdmi_bridge *hdmi_bridge = to_hdmi_bridge(bridge);
	struct hdmi *hdmi = hdmi_bridge->hdmi;
	struct hdmi_phy *phy = hdmi->phy;

	if (hdmi->hdcp_ctrl)
		msm_hdmi_hdcp_off(hdmi->hdcp_ctrl);

	DBG("power down");
	msm_hdmi_set_mode(hdmi, false);

	msm_hdmi_phy_powerdown(phy);

	if (hdmi->power_on) {
		power_off(bridge);
		hdmi->power_on = false;
		if (hdmi->hdmi_mode)
			msm_hdmi_audio_update(hdmi);
		msm_hdmi_phy_resource_disable(phy);
	}
}
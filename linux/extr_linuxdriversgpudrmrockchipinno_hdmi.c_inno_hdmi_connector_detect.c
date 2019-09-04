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
struct inno_hdmi {int dummy; } ;
struct drm_connector {int dummy; } ;
typedef  enum drm_connector_status { ____Placeholder_drm_connector_status } drm_connector_status ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_STATUS ; 
 int connector_status_connected ; 
 int connector_status_disconnected ; 
 int hdmi_readb (struct inno_hdmi*,int /*<<< orphan*/ ) ; 
 int m_HOTPLUG ; 
 struct inno_hdmi* to_inno_hdmi (struct drm_connector*) ; 

__attribute__((used)) static enum drm_connector_status
inno_hdmi_connector_detect(struct drm_connector *connector, bool force)
{
	struct inno_hdmi *hdmi = to_inno_hdmi(connector);

	return (hdmi_readb(hdmi, HDMI_STATUS) & m_HOTPLUG) ?
		connector_status_connected : connector_status_disconnected;
}
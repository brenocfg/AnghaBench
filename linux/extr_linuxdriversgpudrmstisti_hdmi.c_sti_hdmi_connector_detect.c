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
struct sti_hdmi_connector {struct sti_hdmi* hdmi; } ;
struct sti_hdmi {int /*<<< orphan*/  notifier; scalar_t__ hpd; } ;
struct drm_connector {int dummy; } ;
typedef  enum drm_connector_status { ____Placeholder_drm_connector_status } drm_connector_status ;

/* Variables and functions */
 int /*<<< orphan*/  CEC_PHYS_ADDR_INVALID ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 int /*<<< orphan*/  cec_notifier_set_phys_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int connector_status_connected ; 
 int connector_status_disconnected ; 
 struct sti_hdmi_connector* to_sti_hdmi_connector (struct drm_connector*) ; 

__attribute__((used)) static enum drm_connector_status
sti_hdmi_connector_detect(struct drm_connector *connector, bool force)
{
	struct sti_hdmi_connector *hdmi_connector
		= to_sti_hdmi_connector(connector);
	struct sti_hdmi *hdmi = hdmi_connector->hdmi;

	DRM_DEBUG_DRIVER("\n");

	if (hdmi->hpd) {
		DRM_DEBUG_DRIVER("hdmi cable connected\n");
		return connector_status_connected;
	}

	DRM_DEBUG_DRIVER("hdmi cable disconnected\n");
	cec_notifier_set_phys_addr(hdmi->notifier, CEC_PHYS_ADDR_INVALID);
	return connector_status_disconnected;
}
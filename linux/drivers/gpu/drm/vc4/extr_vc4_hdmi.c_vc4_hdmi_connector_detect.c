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
struct vc4_dev {TYPE_1__* hdmi; } ;
struct drm_device {int dummy; } ;
struct drm_connector {struct drm_device* dev; } ;
typedef  enum drm_connector_status { ____Placeholder_drm_connector_status } drm_connector_status ;
struct TYPE_2__ {int hpd_active_low; int /*<<< orphan*/  cec_adap; int /*<<< orphan*/  ddc; scalar_t__ hpd_gpio; } ;

/* Variables and functions */
 int HDMI_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VC4_HDMI_HOTPLUG ; 
 int VC4_HDMI_HOTPLUG_CONNECTED ; 
 int /*<<< orphan*/  cec_phys_addr_invalidate (int /*<<< orphan*/ ) ; 
 int connector_status_connected ; 
 int connector_status_disconnected ; 
 scalar_t__ drm_probe_ddc (int /*<<< orphan*/ ) ; 
 int gpio_get_value_cansleep (scalar_t__) ; 
 struct vc4_dev* to_vc4_dev (struct drm_device*) ; 

__attribute__((used)) static enum drm_connector_status
vc4_hdmi_connector_detect(struct drm_connector *connector, bool force)
{
	struct drm_device *dev = connector->dev;
	struct vc4_dev *vc4 = to_vc4_dev(dev);

	if (vc4->hdmi->hpd_gpio) {
		if (gpio_get_value_cansleep(vc4->hdmi->hpd_gpio) ^
		    vc4->hdmi->hpd_active_low)
			return connector_status_connected;
		cec_phys_addr_invalidate(vc4->hdmi->cec_adap);
		return connector_status_disconnected;
	}

	if (drm_probe_ddc(vc4->hdmi->ddc))
		return connector_status_connected;

	if (HDMI_READ(VC4_HDMI_HOTPLUG) & VC4_HDMI_HOTPLUG_CONNECTED)
		return connector_status_connected;
	cec_phys_addr_invalidate(vc4->hdmi->cec_adap);
	return connector_status_disconnected;
}
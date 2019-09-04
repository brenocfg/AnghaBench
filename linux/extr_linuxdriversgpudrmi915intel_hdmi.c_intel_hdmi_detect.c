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
struct intel_hdmi {int /*<<< orphan*/  cec_notifier; } ;
struct drm_i915_private {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;
struct drm_connector {int /*<<< orphan*/  name; TYPE_1__ base; int /*<<< orphan*/  dev; } ;
typedef  enum drm_connector_status { ____Placeholder_drm_connector_status } drm_connector_status ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  POWER_DOMAIN_GMBUS ; 
 int /*<<< orphan*/  cec_notifier_phys_addr_invalidate (int /*<<< orphan*/ ) ; 
 int connector_status_connected ; 
 int connector_status_disconnected ; 
 struct intel_hdmi* intel_attached_hdmi (struct drm_connector*) ; 
 int /*<<< orphan*/  intel_display_power_get (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_display_power_put (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 scalar_t__ intel_hdmi_set_edid (struct drm_connector*) ; 
 int /*<<< orphan*/  intel_hdmi_unset_edid (struct drm_connector*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum drm_connector_status
intel_hdmi_detect(struct drm_connector *connector, bool force)
{
	enum drm_connector_status status;
	struct drm_i915_private *dev_priv = to_i915(connector->dev);
	struct intel_hdmi *intel_hdmi = intel_attached_hdmi(connector);

	DRM_DEBUG_KMS("[CONNECTOR:%d:%s]\n",
		      connector->base.id, connector->name);

	intel_display_power_get(dev_priv, POWER_DOMAIN_GMBUS);

	intel_hdmi_unset_edid(connector);

	if (intel_hdmi_set_edid(connector))
		status = connector_status_connected;
	else
		status = connector_status_disconnected;

	intel_display_power_put(dev_priv, POWER_DOMAIN_GMBUS);

	if (status != connector_status_connected)
		cec_notifier_phys_addr_invalidate(intel_hdmi->cec_notifier);

	return status;
}
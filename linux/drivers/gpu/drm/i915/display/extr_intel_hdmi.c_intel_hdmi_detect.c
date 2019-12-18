#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct intel_hdmi {int /*<<< orphan*/  cec_notifier; } ;
struct intel_encoder {int dummy; } ;
struct drm_i915_private {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  id; } ;
struct drm_connector {int /*<<< orphan*/  name; TYPE_1__ base; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  intel_wakeref_t ;
typedef  enum drm_connector_status { ____Placeholder_drm_connector_status } drm_connector_status ;
struct TYPE_4__ {struct intel_encoder base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  POWER_DOMAIN_GMBUS ; 
 int /*<<< orphan*/  cec_notifier_phys_addr_invalidate (int /*<<< orphan*/ ) ; 
 int connector_status_connected ; 
 int connector_status_disconnected ; 
 TYPE_2__* hdmi_to_dig_port (struct intel_hdmi*) ; 
 struct intel_hdmi* intel_attached_hdmi (struct drm_connector*) ; 
 int /*<<< orphan*/  intel_digital_port_connected (struct intel_encoder*) ; 
 int /*<<< orphan*/  intel_display_power_flush_work (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_display_power_get (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_display_power_put (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ intel_hdmi_set_edid (struct drm_connector*) ; 
 int /*<<< orphan*/  intel_hdmi_unset_edid (struct drm_connector*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum drm_connector_status
intel_hdmi_detect(struct drm_connector *connector, bool force)
{
	enum drm_connector_status status = connector_status_disconnected;
	struct drm_i915_private *dev_priv = to_i915(connector->dev);
	struct intel_hdmi *intel_hdmi = intel_attached_hdmi(connector);
	struct intel_encoder *encoder = &hdmi_to_dig_port(intel_hdmi)->base;
	intel_wakeref_t wakeref;

	DRM_DEBUG_KMS("[CONNECTOR:%d:%s]\n",
		      connector->base.id, connector->name);

	wakeref = intel_display_power_get(dev_priv, POWER_DOMAIN_GMBUS);

	if (INTEL_GEN(dev_priv) >= 11 &&
	    !intel_digital_port_connected(encoder))
		goto out;

	intel_hdmi_unset_edid(connector);

	if (intel_hdmi_set_edid(connector))
		status = connector_status_connected;

out:
	intel_display_power_put(dev_priv, POWER_DOMAIN_GMBUS, wakeref);

	if (status != connector_status_connected)
		cec_notifier_phys_addr_invalidate(intel_hdmi->cec_notifier);

	/*
	 * Make sure the refs for power wells enabled during detect are
	 * dropped to avoid a new detect cycle triggered by HPD polling.
	 */
	intel_display_power_flush_work(dev_priv);

	return status;
}
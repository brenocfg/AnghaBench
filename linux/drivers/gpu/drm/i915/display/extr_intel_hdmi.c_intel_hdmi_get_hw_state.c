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
struct intel_hdmi {int /*<<< orphan*/  hdmi_reg; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct intel_encoder {int /*<<< orphan*/  power_domain; TYPE_1__ base; } ;
struct drm_i915_private {int dummy; } ;
typedef  int /*<<< orphan*/  intel_wakeref_t ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 struct intel_hdmi* enc_to_intel_hdmi (TYPE_1__*) ; 
 int /*<<< orphan*/  intel_display_power_get_if_enabled (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_display_power_put (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int intel_sdvo_port_enabled (struct drm_i915_private*,int /*<<< orphan*/ ,int*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool intel_hdmi_get_hw_state(struct intel_encoder *encoder,
				    enum pipe *pipe)
{
	struct drm_i915_private *dev_priv = to_i915(encoder->base.dev);
	struct intel_hdmi *intel_hdmi = enc_to_intel_hdmi(&encoder->base);
	intel_wakeref_t wakeref;
	bool ret;

	wakeref = intel_display_power_get_if_enabled(dev_priv,
						     encoder->power_domain);
	if (!wakeref)
		return false;

	ret = intel_sdvo_port_enabled(dev_priv, intel_hdmi->hdmi_reg, pipe);

	intel_display_power_put(dev_priv, encoder->power_domain, wakeref);

	return ret;
}
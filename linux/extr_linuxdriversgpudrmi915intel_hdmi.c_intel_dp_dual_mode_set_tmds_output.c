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
struct TYPE_2__ {scalar_t__ type; } ;
struct intel_hdmi {TYPE_1__ dp_dual_mode; int /*<<< orphan*/  ddc_bus; } ;
struct i2c_adapter {int dummy; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,char*) ; 
 scalar_t__ DRM_DP_DUAL_MODE_TYPE2_DVI ; 
 int /*<<< orphan*/  drm_dp_dual_mode_set_tmds_output (scalar_t__,struct i2c_adapter*,int) ; 
 struct i2c_adapter* intel_gmbus_get_adapter (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_hdmi_to_dev (struct intel_hdmi*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

void intel_dp_dual_mode_set_tmds_output(struct intel_hdmi *hdmi, bool enable)
{
	struct drm_i915_private *dev_priv = to_i915(intel_hdmi_to_dev(hdmi));
	struct i2c_adapter *adapter =
		intel_gmbus_get_adapter(dev_priv, hdmi->ddc_bus);

	if (hdmi->dp_dual_mode.type < DRM_DP_DUAL_MODE_TYPE2_DVI)
		return;

	DRM_DEBUG_KMS("%s DP dual mode adaptor TMDS output\n",
		      enable ? "Enabling" : "Disabling");

	drm_dp_dual_mode_set_tmds_output(hdmi->dp_dual_mode.type,
					 adapter, enable);
}